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
///   File: semaphore.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_NADIR_MT_APPLE_MACH_SEMAPHORE_HPP
#define _FILA_NADIR_MT_APPLE_MACH_SEMAPHORE_HPP

#include "fila/nadir/mt/semaphore.hpp"
#include "crono/nadir/io/logger.hpp"

#include <mach/task.h>
#include <mach/mach.h>
#include <mach/semaphore.h>

namespace fila {
namespace mt {
namespace apple {
namespace mach {

typedef semaphore_t* semaphore_attached_t;
typedef mt::semaphore semaphore_creator;
typedef nadir::attachert<semaphore_attached_t, int, 0, semaphore_creator> semaphore_attacher;
typedef nadir::attachedt<semaphore_attached_t, int, 0, semaphore_attacher, base> semaphore_attached;
typedef nadir::createdt<semaphore_attached_t, int, 0, semaphore_attacher, semaphore_attached> semaphore_created;
typedef semaphore_creator semaphoret_implements;
typedef semaphore_created semaphoret_extends;
///////////////////////////////////////////////////////////////////////
///  Class: semaphoret
///////////////////////////////////////////////////////////////////////
template
<class TImplements = semaphoret_implements, class TExtends = semaphoret_extends>

class _EXPORT_CLASS semaphoret: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    semaphoret(semaphore_t* attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    semaphoret(semaphore_t* attachedTo): Extends(attachedTo) {
    }
    semaphoret(size_t initiallyReleased) {
        if (!(this->create(initiallyReleased))) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    semaphoret(const semaphoret& copy): Extends(copy.attached_to()) {
    }
    semaphoret() {
        if (!(this->create())) {
            create_exception e(create_failed);
            throw (e);
        }
    }
    virtual ~semaphoret() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(size_t initiallyReleased) {
        semaphore_t* detached = 0;
        if ((detached = create_attached(initiallyReleased))) {
            this->set_is_created();
            return detached;
        }
        return false;
    }
    virtual bool create() {
        return create(0);
    }
    virtual bool destroy() {
        semaphore_t* detached = 0;
        if ((detached = this->detach())) {
            if ((destroy_detached(detached))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual semaphore_t* create_attached(size_t initiallyReleased) {
        semaphore_t* detached = 0;
        if ((this->destroyed())) {
            if ((detached = create_detached(m_semaphore, initiallyReleased))) {
                this->attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual semaphore_t* create_detached
    (semaphore_t& semaphore, size_t initiallyReleased) const {
        int err = 0;
        task_t task = mach_task_self();
        sync_policy_t syncPolicy = SYNC_POLICY_FIFO;

        CRONO_LOG_DEBUG("semaphore_create(task, &semaphore, syncPolicy, initiallyReleased)...");
        if (KERN_SUCCESS == (err = semaphore_create(task, &semaphore, syncPolicy, initiallyReleased))) {
            return &semaphore;
        } else {
            CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_create(task, &semaphore, syncPolicy, initiallyReleased)");
        }
        return 0;
    }
    virtual bool destroy_detached(semaphore_t* semaphore) const {
        if ((semaphore)) {
            int err = 0;
            task_t task = mach_task_self();

            CRONO_LOG_DEBUG("semaphore_destroy(task, *semaphore)...")
            if (KERN_SUCCESS == (err = semaphore_destroy(task, *semaphore))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_destroy(task, *semaphore)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool acquire() {
        if (acquire_success == (untimed_acquire())) {
            return true;
        }
        return false;
    }
    virtual bool release() {
        semaphore_t* semaphore = 0;
        if ((semaphore = this->attached_to())) {
            int err = 0;

            CRONO_LOG_DEBUG("semaphore_signal(*semaphore)...");
            if (KERN_SUCCESS == (err = semaphore_signal(*semaphore))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_signal(*semaphore)");
            }
        }
        return false;
    }
    virtual acquire_status try_acquire() {
        return timed_acquire(0);
    }
    virtual acquire_status timed_acquire(mseconds_t milliseconds) {
        if (0 > (milliseconds)) {
            return untimed_acquire();
        } else {
            semaphore_t* semaphore = 0;
            if ((semaphore = this->attached_to())) {
                int err = 0;
                mach_timespec_t waitTime;
                waitTime.tv_sec = mseconds_seconds(milliseconds);
                waitTime.tv_nsec = mseconds_nseconds(milliseconds);

                CRONO_LOG_TRACE("semaphore_timedwait(*semaphore, waitTime)...");
                if (KERN_SUCCESS == (err = semaphore_timedwait(*semaphore, waitTime))) {
                    return acquire_success;
                } else {
                    if (KERN_OPERATION_TIMED_OUT == (err)) {
                        CRONO_LOG_TRACE("...failed err = KERN_OPERATION_TIMED_OUT on semaphore_timedwait(*semaphore, waitTime)");
                        return acquire_busy;
                    } else {
                        if (KERN_ABORTED == (err)) {
                            CRONO_LOG_ERROR("...failed err = KERN_ABORTED on semaphore_timedwait(*semaphore, waitTime)");
                            return acquire_interrupted;
                        } else {
                            CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_timedwait(*semaphore, waitTime)");
                        }
                    }
                }
            }
        }
        return acquire_failed;
    }
    virtual acquire_status untimed_acquire() {
        semaphore_t* semaphore = 0;
        if ((semaphore = this->attached_to())) {
            int err = 0;

            CRONO_LOG_DEBUG("semaphore_wait(*semaphore)...");
            if (KERN_SUCCESS == (err = semaphore_wait(*semaphore))) {
                return acquire_success;
            } else {
                if (KERN_OPERATION_TIMED_OUT == (err)) {
                    CRONO_LOG_ERROR("...failed err = KERN_OPERATION_TIMED_OUT on semaphore_wait(*semaphore)");
                    return acquire_busy;
                } else {
                    if (KERN_ABORTED == (err)) {
                        CRONO_LOG_ERROR("...failed err = KERN_ABORTED on semaphore_wait(*semaphore)");
                        return acquire_interrupted;
                    } else {
                        CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_wait(*semaphore)");
                    }
                }
            }
        }
        return acquire_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    semaphore_t m_semaphore;
};
typedef semaphoret<> semaphore;

} // namespace mach 
} // namespace apple 
} // namespace mt 
} // namespace fila 

#endif // _FILA_NADIR_MT_APPLE_MACH_SEMAPHORE_HPP 
