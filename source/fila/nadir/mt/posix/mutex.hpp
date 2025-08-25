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
///   File: mutex.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_NADIR_MT_POSIX_MUTEX_HPP
#define _FILA_NADIR_MT_POSIX_MUTEX_HPP

#include "fila/nadir/mt/mutex.hpp"
#include "crono/nadir/io/logger.hpp"

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
#define PTHREAD_MUTEX_HAS_TIMEDLOCK
#endif // !defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace fila {
namespace mt {
namespace posix {

typedef pthread_mutexattr_t mutexattr_t;
typedef pthread_mutex_t mutex_t;
typedef mutex_t* mutex_attached_t;

typedef mt::mutex mutex_creator;
typedef nadir::attachert<mutex_attached_t, int, 0, mutex_creator> mutex_attacher;
typedef nadir::attachedt<mutex_attached_t, int, 0, mutex_attacher, base> mutex_attached;
typedef nadir::createdt<mutex_attached_t, int, 0, mutex_attacher, mutex_attached> mutex_created;
typedef mutex_attacher mutext_implements;
typedef mutex_created mutext_extends;
///////////////////////////////////////////////////////////////////////
///  Class: mutext
///////////////////////////////////////////////////////////////////////
template
<class TImplements = mutext_implements, class TExtends = mutext_extends>

class _EXPORT_CLASS mutext: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    mutext(pthread_mutex_t* attached, bool isCreated)
    : Extends(attached, isCreated) {
    }
    mutext(pthread_mutex_t* attached): Extends(attached) {
    }
    mutext(bool initally_locked) {
        if (!(this->create(initally_locked))) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    mutext(mutext& copy): Extends(copy.attached_to()) {
    }
    mutext() {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    virtual ~mutext() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(bool initally_locked) {
        if (!(initally_locked)) {
            return this->create();
        }
        return false;
    }
    virtual bool create() {
        pthread_mutex_t* detached = 0;
        if ((detached = create_attached())) {
            this->set_is_created();
            return detached;
        }
        return false;
    }
    virtual bool destroy() {
        pthread_mutex_t* detached = 0;
        if ((detached = this->detach())) {
            if ((destroy_detached(detached))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_mutex_t* create_attached() {
        pthread_mutex_t* detached = 0;
        if ((this->destroyed())) {
            if ((detached = create_detached(mutexattr_, mutex_))) {
                this->attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual pthread_mutex_t* create_detached
    (pthread_mutexattr_t& mutexattr, pthread_mutex_t& mutex) const {
        int err = 0;

        CRONO_LOG_DEBUG("pthread_mutexattr_init(&mutexattr)...");
        if (!(err = pthread_mutexattr_init(&mutexattr))) {

            CRONO_LOG_DEBUG("pthread_mutex_init(&mutex, &mutexattr)...");
            if (!(err = pthread_mutex_init(&mutex, &mutexattr))) {

                CRONO_LOG_DEBUG("pthread_mutexattr_destroy(&mutexattr)...");
                if ((err = pthread_mutexattr_destroy(&mutexattr))) {
                    CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutexattr_destroy(&mutexattr)");

                    CRONO_LOG_DEBUG("pthread_mutex_destroy(mutex)...");
                    if ((err = pthread_mutex_destroy(&mutex))) {
                        CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutex_destroy(mutex)");
                    }
                    return 0;
                }
                return &mutex;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutex_init(&mutex, &mutexattr)");
            }
            CRONO_LOG_DEBUG("pthread_mutexattr_destroy(&mutexattr)...");
            if ((err = pthread_mutexattr_destroy(&mutexattr))) {
                CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutexattr_destroy(&mutexattr)");
            }
        } else {
            CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutexattr_init(&mutexattr)");
        }
        return 0;
    }
    virtual bool destroy_detached(pthread_mutex_t* mutex) const {
        if ((mutex)) {
            int err = 0;

            CRONO_LOG_DEBUG("pthread_mutex_destroy(mutex)...");
            if (!(err = pthread_mutex_destroy(mutex))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutex_destroy(mutex)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool lock() {
        if (lock_success == (untimed_lock())) {
            return true;
        }
        return false;
    }
    virtual bool unlock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = this->attached_to())) {

            CRONO_LOG_TRACE("pthread_mutex_unlock(mutex)...");
            if (!(err = pthread_mutex_unlock(mutex))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed err " << err << " = on pthread_mutex_unlock(mutex)");
            }
        }
        return false;
    }
    virtual lock_status try_lock() {
        pthread_mutex_t* mutex = 0;
        if ((mutex = this->attached_to())) {
            int err = 0;

            CRONO_LOG_TRACE("pthread_mutex_trylock(mutex)...");
            if ((err =  pthread_mutex_trylock(mutex))) {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_TRACE("...ETIMEDOUT err = " << err << " on pthread_mutex_trylock(mutex)");
                    return lock_busy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = " << err << " on pthread_mutex_trylock(mutex)");
                    return lock_interrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutex_trylock(mutex)");
                    return lock_failed;
                }
            } else {
                return lock_success;
            }
        }
        return lock_failed;
    }
    virtual lock_status timed_lock(mseconds_t milliseconds) {
        if (0 < (milliseconds)) {
#if defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            pthread_mutex_t* mutex = 0;
            if ((mutex = this->attached_to())) {
                int err = 0;
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  mseconds_seconds(milliseconds);
                untilTime.tv_nsec +=  mseconds_nseconds(milliseconds);

                CRONO_LOG_TRACE("pthread_mutex_timedlock(mutex, &untilTime)...");
                if ((err = pthread_mutex_timedlock(mutex, &untilTime))) {
                    switch(err) {
                    case ETIMEDOUT:
                        CRONO_LOG_TRACE("...ETIMEDOUT err = " << err << " on pthread_mutex_timedlock(mutex, &untilTime)");
                        return lock_busy;
                    case EINTR:
                        CRONO_LOG_ERROR("...EINTR err = " << err << " on pthread_mutex_timedlock(mutex, &untilTime)");
                        return lock_interrupted;
                    default:
                        CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutex_timedlock(mutex, &untilTime)");
                        return lock_failed;
                    }
                } else {
                    return lock_success;
                }
            }
#else // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            return lock_invalid;
#endif // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
        } else {
            if (0 > (milliseconds)) {
                return untimed_lock();
            } else {
                return try_lock();
            }
        }
        return lock_failed;
    }
    virtual lock_status untimed_lock() {
        pthread_mutex_t* mutex = 0;
        if ((mutex = this->attached_to())) {
            int err = 0;

            CRONO_LOG_TRACE("pthread_mutex_lock(mutex)...");
            if ((err =  pthread_mutex_lock(mutex))) {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_ERROR("...ETIMEDOUT err = " << err << " on pthread_mutex_lock(mutex)");
                    return lock_busy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = " << err << " on pthread_mutex_lock(mutex)");
                    return lock_interrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = " << err << " on pthread_mutex_lock(mutex)");
                    return lock_failed;
                }
            } else {
                return lock_success;
            }
        }
        return lock_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    pthread_mutexattr_t mutexattr_;
    pthread_mutex_t mutex_;
};
typedef mutext<> mutex;

} // namespace posix
} // namespace mt 
} // namespace fila 

#endif // _FILA_NADIR_MT_POSIX_MUTEX_HPP 
