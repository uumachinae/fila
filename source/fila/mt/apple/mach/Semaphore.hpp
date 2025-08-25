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
#ifndef _FILA_MT_APPLE_MACH_SEMAPHORE_HPP
#define _FILA_MT_APPLE_MACH_SEMAPHORE_HPP

#include "fila/mt/Semaphore.hpp"
#include "fila/base/Created.hpp"
#include "fila/base/Attached.hpp"
#include "crono/io/Logger.hpp"

#include <mach/task.h>
#include <mach/mach.h>
#include <mach/semaphore.h>

namespace fila {
namespace mt {
namespace apple {
namespace mach {

typedef semaphore_t* SemaphoreTAttachedT;
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

class _EXPORT_CLASS SemaphoreT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SemaphoreT(semaphore_t* attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    SemaphoreT(semaphore_t* attachedTo): Extends(attachedTo) {
    }
    SemaphoreT(size_t initiallyReleased) {
        if (!(this->Create(initiallyReleased))) {
            CreateException e(CreateFailed);
            throw (e);
        }
    }
    SemaphoreT() {
        if (!(this->Create())) {
            CreateException e(CreateFailed);
            throw (e);
        }
    }
    virtual ~SemaphoreT() {
        if (!(this->Destroyed())) {
            CreateException e(DestroyFailed);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(size_t initiallyReleased) {
        semaphore_t* detached = 0;
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
        semaphore_t* detached = 0;
        if ((detached = this->Detach())) {
            if ((DestroyDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual semaphore_t* CreateAttached(size_t initiallyReleased) {
        semaphore_t* detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(m_semaphore, initiallyReleased))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual semaphore_t* CreateDetached
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
    virtual bool DestroyDetached(semaphore_t* semaphore) const {
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
    virtual bool Acquire() {
        if (AcquireSuccess == (UntimedAcquire())) {
            return true;
        }
        return false;
    }
    virtual bool Release() {
        semaphore_t* semaphore = 0;
        if ((semaphore = this->m_attachedTo)) {
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
    virtual AcquireStatus TryAcquire() {
        return TimedAcquire(0);
    }
    virtual AcquireStatus TimedAcquire(mseconds_t milliseconds) {
        if (0 > (milliseconds)) {
            return UntimedAcquire();
        } else {
            semaphore_t* semaphore = 0;
            if ((semaphore = this->m_attachedTo)) {
                int err = 0;
                mach_timespec_t waitTime;
                waitTime.tv_sec = mseconds_seconds(milliseconds);
                waitTime.tv_nsec = mseconds_nseconds(milliseconds);

                CRONO_LOG_TRACE("semaphore_timedwait(*semaphore, waitTime)...");
                if (KERN_SUCCESS == (err = semaphore_timedwait(*semaphore, waitTime))) {
                    return AcquireSuccess;
                } else {
                    if (KERN_OPERATION_TIMED_OUT == (err)) {
                        CRONO_LOG_TRACE("...failed err = KERN_OPERATION_TIMED_OUT on semaphore_timedwait(*semaphore, waitTime)");
                        return AcquireBusy;
                    } else {
                        if (KERN_ABORTED == (err)) {
                            CRONO_LOG_ERROR("...failed err = KERN_ABORTED on semaphore_timedwait(*semaphore, waitTime)");
                            return AcquireInterrupted;
                        } else {
                            CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_timedwait(*semaphore, waitTime)");
                        }
                    }
                }
            }
        }
        return AcquireFailed;
    }
    virtual AcquireStatus UntimedAcquire() {
        semaphore_t* semaphore = 0;
        if ((semaphore = this->m_attachedTo)) {
            int err = 0;

            CRONO_LOG_DEBUG("semaphore_wait(*semaphore)...");
            if (KERN_SUCCESS == (err = semaphore_wait(*semaphore))) {
                return AcquireSuccess;
            } else {
                if (KERN_OPERATION_TIMED_OUT == (err)) {
                    CRONO_LOG_ERROR("...failed err = KERN_OPERATION_TIMED_OUT on semaphore_wait(*semaphore)");
                    return AcquireBusy;
                } else {
                    if (KERN_ABORTED == (err)) {
                        CRONO_LOG_ERROR("...failed err = KERN_ABORTED on semaphore_wait(*semaphore)");
                        return AcquireInterrupted;
                    } else {
                        CRONO_LOG_ERROR("...failed err = " << err << " on semaphore_wait(*semaphore)");
                    }
                }
            }
        }
        return AcquireFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    semaphore_t m_semaphore;
};
typedef SemaphoreT<> Semaphore;

} // namespace mach
} // namespace apple 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_APPLE_MACH_SEMAPHORE_HPP 
