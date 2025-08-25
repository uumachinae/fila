///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: Mutex.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_MT_POSIX_MUTEX_HPP
#define _FILA_MT_POSIX_MUTEX_HPP

#include "fila/mt/Mutex.hpp"
#include "fila/base/Created.hpp"
#include "fila/base/Attached.hpp"
#include "crono/io/Logger.hpp"

#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
#define PTHREAD_MUTEX_HAS_TIMEDLOCK
#endif // !defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace fila {
namespace mt {
namespace posix {

typedef pthread_mutex_t* MutexTAttachedT;
typedef ::patrona::CreatorT<mt::Mutex> MutexTAttacherImplements;
typedef ::patrona::AttacherT<MutexTAttachedT, int, 0, MutexTAttacherImplements> MutexTAttacher;
typedef ::patrona::AttachedT<MutexTAttachedT, int, 0, MutexTAttacher> MutexTAttached;
typedef ::patrona::CreatedT<MutexTAttachedT, int, 0, MutexTAttacher, MutexTAttached> MutexTCreated;
typedef MutexTAttacher MutexTImplements;
typedef MutexTCreated MutexTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MutexT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = MutexTImplements, class TExtends = MutexTExtends>

class _EXPORT_CLASS MutexT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MutexT(pthread_mutex_t* attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    MutexT(pthread_mutex_t* attachedTo): Extends(attachedTo) {
    }
    MutexT(bool initallyLocked) {
        if (!(this->Create(initallyLocked))) {
            CreateException e(CreateFailed);
            throw (e);
        }
    }
    MutexT() {
        if (!(this->Create())) {
            CreateException e(CreateFailed);
            throw (e);
        }
    }
    virtual ~MutexT() {
        if (!(this->Destroyed())) {
            CreateException e(DestroyFailed);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(bool initallyLocked) {
        if (!(initallyLocked)) {
            return this->Create();
        }
        return false;
    }
    virtual bool Create() {
        pthread_mutex_t* detached = 0;
        if ((detached = CreateAttached())) {
            this->SetIsCreated();
            return detached;
        }
        return false;
    }
    virtual bool Destroy() {
        pthread_mutex_t* detached = 0;
        if ((detached = this->Detach())) {
            if ((DestroyDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_mutex_t* CreateAttached() {
        pthread_mutex_t* detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(m_mutexattr, m_mutex))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual pthread_mutex_t* CreateDetached
    (pthread_mutexattr_t& mutexattr, pthread_mutex_t& mutex) const {
        int err = 0;

        CRONO_LOG_DEBUG("pthread_mutexattr_init(&mutexattr)...");
        if (!(err = pthread_mutexattr_init(&mutexattr))) {

            CRONO_LOG_DEBUG("pthread_mutex_init(&mutex, &mutexattr)...");
            if (!(err = pthread_mutex_init(&mutex, &mutexattr))) {

                CRONO_LOG_DEBUG("pthread_mutexattr_destroy(&mutexattr)...");
                if ((err = pthread_mutexattr_destroy(&mutexattr))) {
                    if ((err = pthread_mutex_destroy(&mutex))) {
                    }
                    return 0;
                }
                return &mutex;
            }
            if ((err = pthread_mutexattr_destroy(&mutexattr))) {
            }
        }
        return 0;
    }
    virtual bool DestroyDetached(pthread_mutex_t* mutex) const {
        if ((mutex)) {
            int err = 0;
            CRONO_LOG_DEBUG("pthread_mutex_destroy(mutex)...");
            if (!(err = pthread_mutex_destroy(mutex))) {
                return true;
            } else {
                if ((EINVAL != (err))) {
                    if ((EBUSY != (err))) {
                        CRONO_LOG_ERROR("...((0 != (" << err << ")))");
                    } else {
                        CRONO_LOG_ERROR("...((EBUSY == (" << err << ")))");
                    }
                } else {
                    CRONO_LOG_ERROR("...((EINVAL == (" << err << ")))");
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = this->m_attachedTo)) {
            CRONO_LOG_DEBUG("pthread_mutex_lock(mutex)...")
            if (!(err = pthread_mutex_lock(mutex))) {
                return true;
            } else {
            }
        }
        return false;
    }
    virtual bool Unlock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = this->m_attachedTo)) {
            CRONO_LOG_DEBUG("pthread_mutex_unlock(mutex)...")
            if (!(err = pthread_mutex_unlock(mutex))) {
                return true;
            } else {
            }
        }
        return false;
    }
    virtual LockStatus TryLock() {
        pthread_mutex_t* mutex = 0;
        if ((mutex = this->m_attachedTo)) {
            int err = 0;
            CRONO_LOG_TRACE("pthread_mutex_trylock(mutex)...");
            if ((err =  pthread_mutex_trylock(mutex))) {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_mutex_trylock(mutex)...")
                    return LockBusy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = "<< err << " on pthread_mutex_trylock(mutex)...")
                    return LockInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = "<< err << " on pthread_mutex_trylock(mutex)...")
                    return LockFailed;
                }
            } else {
                return LockSuccess;
            }
        }
        return LockFailed;
    }
    virtual LockStatus TimedLock(mseconds_t milliseconds) {
        if (0 < (milliseconds)) {
#if defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            pthread_mutex_t* mutex = 0;
            if ((mutex = this->m_attachedTo)) {
                int err = 0;
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  mseconds_seconds(milliseconds);
                untilTime.tv_nsec +=  mseconds_nseconds(milliseconds);

                if ((err = pthread_mutex_timedlock(mutex, &untilTime))) {
                    switch(err) {
                    case ETIMEDOUT:
                        return LockBusy;
                    case EINTR:
                        return LockInterrupted;
                    default:
                        return LockFailed;
                    }
                } else {
                    return LockSuccess;
                }
            }
#else // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            return LockInvalid;
#endif // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
        } else {
            if (0 > (milliseconds)) {
                return UntimedLock();
            } else {
                return TryLock();
            }
        }
        return LockFailed;
    }
    virtual LockStatus UntimedLock() {
        pthread_mutex_t* mutex = 0;
        if ((mutex = this->m_attachedTo)) {
            int err = 0;
            CRONO_LOG_DEBUG("pthread_mutex_lock(mutex)...")
            if ((err =  pthread_mutex_lock(mutex))) {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_ERROR("...ETIMEDOUT err = "<< err << " on pthread_mutex_lock(mutex)...")
                    return LockBusy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = "<< err << " on pthread_mutex_lock(mutex)...")
                    return LockInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = "<< err << " on pthread_mutex_lock(mutex)...")
                    return LockFailed;
                }
            } else {
                return LockSuccess;
            }
        }
        return LockFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    pthread_mutexattr_t m_mutexattr;
    pthread_mutex_t m_mutex;
};
typedef MutexT<> Mutex;

} // namespace posix 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_POSIX_MUTEX_HPP 
