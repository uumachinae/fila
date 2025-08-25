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
///   File: Semaphore.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_MT_POSIX_SEMAPHORE_HPP
#define _FILA_MT_POSIX_SEMAPHORE_HPP

#include "fila/mt/Semaphore.hpp"
#include "fila/base/Created.hpp"
#include "fila/base/Attached.hpp"
#include "crono/io/Logger.hpp"

#include <semaphore.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#define SEM_HAS_TIMEDWAIT
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

#define SEMAPHORE_PROCESS_PRIVATE 0
#define SEMAPHORE_PROCESS_SHARED  1

namespace fila {
namespace mt {
namespace posix {

typedef sem_t* SemaphoreTAttachedT;
typedef ::patrona::CreatorT<mt::Semaphore> SemaphoreTAttacherImplements;
typedef ::patrona::AttacherT<SemaphoreTAttachedT, int, 0, SemaphoreTAttacherImplements> SemaphoreTAttacher;
typedef ::patrona::AttachedT<SemaphoreTAttachedT, int, 0, SemaphoreTAttacher> SemaphoreTAttached;
typedef ::patrona::CreatedT<SemaphoreTAttachedT, int, 0, SemaphoreTAttacher, SemaphoreTAttached> SemaphoreTCreated;
typedef SemaphoreTAttacher SemaphoreTImplements;
typedef SemaphoreTCreated SemaphoreTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: SemaphoreT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = SemaphoreTImplements, class TExtends = SemaphoreTExtends>
class _EXPORT_CLASS SemaphoreT: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SemaphoreT(sem_t* attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    SemaphoreT(sem_t* attachedTo): Extends(attachedTo) {
    }
    SemaphoreT(size_t initiallyReleased) {
        if (!(this->Create(initiallyReleased))) {
            CreateException e(CreateFailed);
            CRONO_LOG_ERROR("throw (e = CreateException(CreateFailed))...");
            throw (e);
        }
    }
    SemaphoreT() {
        if (!(this->Create())) {
            CreateException e(CreateFailed);
            CRONO_LOG_ERROR("throw (e = CreateException(CreateFailed))...");
            throw (e);
        }
    }
    virtual ~SemaphoreT() {
        if (!(this->Destroyed())) {
            CRONO_LOG_ERROR("throw (e = CreateException(DestroyFailed))...");
            CreateException e(DestroyFailed);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(size_t initiallyReleased) {
        sem_t* detached = 0;
        if ((detached = CreateAttached(initiallyReleased))) {
            this->SetIsCreated();
            return detached;
        }
        return false;
    }
    virtual bool Create() {
        return Create(0);
    }
    virtual bool Destroy() {
        sem_t* detached = 0;
        if ((detached = this->Detach())) {
            if ((DestroyDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual sem_t* CreateAttached(size_t initiallyReleased) {
        sem_t* detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(m_sem, initiallyReleased))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual sem_t* CreateDetached
    (sem_t& sem, size_t initiallyReleased) const {
        int pshared = SEMAPHORE_PROCESS_PRIVATE;
        int err = 0;
        CRONO_LOG_DEBUG("sem_init(&sem, pshared, initiallyReleased)...");
        if ((!(err = sem_init(&sem, pshared, initiallyReleased)))) {
            return &sem;
        } else {
            CRONO_LOG_ERROR("...failed err = " << err << " on sem_init(&sem, pshared, initiallyReleased)");
        }
        return 0;
    }
    virtual bool DestroyDetached(sem_t* sem) const {
        if ((sem)) {
            int err = 0;
            CRONO_LOG_DEBUG("sem_destroy(sem)...");
            if (!(err = sem_destroy(sem))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on sem_destroy(sem)");
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Acquire() {
        if (AcquireSuccess == (UntimedAcquire())) {
            return true;
        }
        return false;
    }
    virtual bool Release() {
        sem_t* sem = 0;
        if ((sem = this->m_attachedTo)) {
            int err = 0;
            CRONO_LOG_DEBUG("sem_post(sem)...");
            if (!(err = sem_post(sem))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on sem_post(sem)");
            }
        }
        return false;
    }
    virtual AcquireStatus TryAcquire() {
        sem_t* sem = 0;
        if ((sem = this->m_attachedTo)) {
            int err = 0;

            CRONO_LOG_TRACE("sem_trywait(sem)...");
            if (!(err = sem_trywait(sem))) {
                CRONO_LOG_DEBUG("...sem_trywait(sem)");
                return AcquireSuccess;
            } else {
                switch (err = errno) {
                case ETIMEDOUT:
                    CRONO_LOG_TRACE("...ETIMEDOUT err = " << err << " on sem_trywait(sem)");
                    return AcquireBusy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = " << err << " on sem_trywait(sem)");
                    return AcquireInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = " << err << " on sem_trywait(sem)");
                }
            }
        }
        return AcquireFailed;
    }
    virtual AcquireStatus TimedAcquire(mseconds_t milliseconds) {
        if (0 > (milliseconds)) {
            return UntimedAcquire();
        } else {
#if defined(SEM_HAS_TIMEDWAIT)
            sem_t* sem = 0;
            if ((sem = this->m_attachedTo)) {
                int err = 0;
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  mseconds_seconds(milliseconds);
                untilTime.tv_nsec +=  mseconds_nseconds(milliseconds);

                CRONO_LOG_TRACE("sem_timedwait(sem, &untilTime)...");
                if (!(err = sem_timedwait(sem, &untilTime))) {
                    CRONO_LOG_DEBUG("...sem_timedwait(sem, &untilTime)");
                    return AcquireSuccess;
                } else {
                    switch (err = errno) {
                    case ETIMEDOUT:
                        CRONO_LOG_TRACE("...ETIMEDOUT err = " << err << " on sem_timedwait(sem, &untilTime)");
                        return AcquireBusy;
                    case EINTR:
                        CRONO_LOG_ERROR("...EINTR err = " << err << " on sem_timedwait(sem, &untilTime)");
                        return AcquireInterrupted;
                    default:
                        CRONO_LOG_ERROR("...failed err = " << err << " on sem_timedwait(sem, &untilTime)");
                    }
                }
            }
#else // defined(SEM_HAS_TIMEDWAIT)
            CRONO_LOG_ERROR("...return AcquireInvalid");
            return AcquireInvalid;
#endif // defined(SEM_HAS_TIMEDWAIT)
        }
        return AcquireFailed;
    }
    virtual AcquireStatus UntimedAcquire() {
        sem_t* sem = 0;
        if ((sem = this->m_attachedTo)) {
            int err = 0;

            CRONO_LOG_DEBUG("sem_wait(sem)...");
            if (!(err = sem_wait(sem))) {
                CRONO_LOG_DEBUG("...sem_wait(sem)");
                return AcquireSuccess;
            } else {
                switch (err = errno) {
                case ETIMEDOUT:
                    CRONO_LOG_ERROR("...ETIMEDOUT err = " << err << " on sem_wait(sem)");
                    return AcquireBusy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = " << err << " on sem_wait(sem)");
                    return AcquireInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = " << err << " on sem_wait(sem)");
                }
            }
        }
        return AcquireFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    sem_t m_sem;
};
typedef SemaphoreT<> Semaphore;

} // namespace posix 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_POSIX_SEMAPHORE_HPP 
