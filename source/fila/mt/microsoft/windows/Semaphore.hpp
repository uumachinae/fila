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
#ifndef _FILA_MT_MICROSOFT_WINDOWS_SEMAPHORE_HPP
#define _FILA_MT_MICROSOFT_WINDOWS_SEMAPHORE_HPP

#include "fila/mt/Semaphore.hpp"
#include "fila/base/Created.hpp"
#include "fila/base/Attached.hpp"
#include "crono/io/Logger.hpp"

namespace fila {
namespace mt {
namespace microsoft {
namespace windows {

typedef HANDLE SemaphoreTAttachedT;
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
    SemaphoreT(HANDLE attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    SemaphoreT(HANDLE attachedTo): Extends(attachedTo) {
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
    virtual bool Create(size_t initiallyReleased, size_t maximumReleased) {
        HANDLE detached = 0;
        if ((detached = CreateAttached(initiallyReleased, maximumReleased))) {
            this->SetIsCreated();
            return detached;
        }
        return false;
    }
    virtual bool Create(size_t initiallyReleased) {
        return Create(initiallyReleased, 0);
    }
    virtual bool Create() {
        return Create(0);
    }
    virtual bool Destroy() {
        HANDLE detached = 0;
        if ((detached = this->Detach())) {
            if ((DestroyDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HANDLE CreateAttached(size_t initiallyReleased, size_t maximumReleased) {
        HANDLE detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(initiallyReleased, maximumReleased))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual HANDLE CreateDetached(size_t initiallyReleased, size_t maximumReleased) const {
        LONG lInitialCount = ((LONG)initiallyReleased);
        LONG lMaximumCount = ((LONG)(maximumReleased)?(maximumReleased):(((ULONG)-1)>>1));
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        LPCTSTR lpName = 0;
        HANDLE detached = 0;

        CRONO_LOG_DEBUG("CreateSemaphore(lpSecurityAttributes, lInitialCount, lMaximumCount, lpName)...");
        if ((detached = CreateSemaphore(lpSecurityAttributes, lInitialCount, lMaximumCount, lpName))) {
            return detached;
        } else {
            DWORD dwError = GetLastError();
            CRONO_LOG_ERROR("...failed dwError = " << dwError << " on CreateSemaphore(lpSecurityAttributes, lInitialCount, lMaximumCount, lpName)");
        }
        return 0;
    }
    virtual bool DestroyDetached(HANDLE detached) const {
        if ((detached)) {
            CRONO_LOG_DEBUG("CloseHandle(detached)...");
            if ((CloseHandle(detached))) {
                return true;
            } else {
                DWORD dwError = GetLastError();
                CRONO_LOG_ERROR("...failed dwError = " << dwError << " on CloseHandle(detached)");
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
        if (0 < (Release(1))) {
            return true;
        }
        return false;
    }
    virtual ssize_t Release(size_t count) {
        HANDLE detached = 0;
        if ((detached = this->m_attachedTo)) {
            LONG lReleaseCount = ((LONG)count);
            LONG lPreviousCount = 0;

            CRONO_LOG_DEBUG("ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount)...");
            if ((ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount))) {
                count = lPreviousCount + lReleaseCount;
                CRONO_LOG_DEBUG("...count = " << count << " on ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount)");
                return count;
            } else {
                DWORD dwError = GetLastError();
                CRONO_LOG_ERROR("...failed dwError = " << dwError << " on ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount)");
            }
        }
        return -1;
    }
    virtual AcquireStatus TryAcquire() {
        return TimedAcquire(0);
    }
    virtual AcquireStatus TimedAcquire(mseconds_t milliseconds) {
        if (0 > (milliseconds)) {
            return UntimedAcquire();
        } else {
            HANDLE detached = 0;
            if ((detached = this->m_attachedTo)) {
                DWORD dwMilliseconds = (DWORD)(milliseconds);
                DWORD dwResult = 0;
                CRONO_LOG_TRACE("WaitForSingleObject(detached, dwMilliseconds)...");
                if (WAIT_OBJECT_0 != (dwResult = WaitForSingleObject(detached, dwMilliseconds))) {
                    switch(dwResult) {
                    case WAIT_TIMEOUT:
                        CRONO_LOG_TRACE("...WAIT_TIMEOUT dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                        return AcquireBusy;
                    case WAIT_ABANDONED:
                        CRONO_LOG_ERROR("...WAIT_ABANDONED dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                        return AcquireInterrupted;
                    default:
                        CRONO_LOG_ERROR("...failed dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                        return AcquireFailed;
                    }
                } else {
                    CRONO_LOG_DEBUG("...WaitForSingleObject(detached, dwMilliseconds)");
                    return AcquireSuccess;
                }
            }
        }
        return AcquireFailed;
    }
    virtual AcquireStatus UntimedAcquire() {
        HANDLE detached = 0;
        if ((detached = this->m_attachedTo)) {
            DWORD dwMilliseconds = INFINITE;
            DWORD dwResult = 0;

            CRONO_LOG_DEBUG("WaitForSingleObject(detached, dwMilliseconds)...");
            if (WAIT_OBJECT_0 != (dwResult = WaitForSingleObject(detached, dwMilliseconds))) {
                switch(dwResult) {
                case WAIT_TIMEOUT:
                    CRONO_LOG_ERROR("...WAIT_TIMEOUT dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                    return AcquireBusy;
                case WAIT_ABANDONED:
                    CRONO_LOG_ERROR("...WAIT_ABANDONED dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                    return AcquireInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                    return AcquireFailed;
                }
            } else {
                CRONO_LOG_DEBUG("...WaitForSingleObject(detached, dwMilliseconds)");
                return AcquireSuccess;
            }
        }
        return AcquireFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef SemaphoreT<> Semaphore;

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_MICROSOFT_WINDOWS_SEMAPHORE_HPP 
