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
#ifndef _FILA_MT_MICROSOFT_WINDOWS_MUTEX_HPP
#define _FILA_MT_MICROSOFT_WINDOWS_MUTEX_HPP

#include "fila/mt/Mutex.hpp"
#include "fila/base/Created.hpp"
#include "fila/base/Base.hpp"
#include "crono/io/Logger.hpp"

namespace fila {
namespace mt {
namespace microsoft {
namespace windows {

typedef HANDLE MutexTAttachedT;
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
    MutexT(HANDLE attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    MutexT(HANDLE attachedTo): Extends(attachedTo) {
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
    virtual bool Create() {
        return Create(false);
    }
    virtual bool Create(bool initallyLocked) {
        HANDLE detached = 0;
        if ((detached = CreateAttached(initallyLocked))) {
            this->SetIsCreated();
            return detached;
        }
        return false;
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
    virtual HANDLE CreateAttached(bool initallyLocked) {
        HANDLE detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(initallyLocked))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual HANDLE CreateDetached(bool initallyLocked) const {
        BOOL bInitialOwner = (initallyLocked)?(TRUE):(FALSE);
        LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL;
        LPCTSTR lpName = NULL;
        HANDLE detached = 0;
        CRONO_LOG_DEBUG("CreateMutex(lpMutexAttributes, bInitialOwner, lpName)...");
        if ((detached = CreateMutex(lpMutexAttributes, bInitialOwner, lpName))) {
            return detached;
        } else {
            DWORD dwError = GetLastError();
            CRONO_LOG_ERROR("...failed dwError = " << dwError << " on CreateMutex(lpMutexAttributes, bInitialOwner, lpName)");
        }
        return 0;
    }
    virtual bool DestroyDetached(HANDLE detached) const {
        if ((detached)) {
            CRONO_LOG_DEBUG("CloseHandle(detached)...");
            if ((CloseHandle(detached))) {
                return true;
            } else {
                DWORD dwError  = GetLastError();
                CRONO_LOG_ERROR("...failed dwError = " << dwError << " on CloseHandle(detached)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() {
        if (LockSuccess == (UntimedLock())) {
            return true;
        }
        return false;
    }
    virtual bool Unlock() {
        HANDLE detached = 0;
        if ((detached = this->m_attachedTo)) {
            DWORD dwMilliseconds = INFINITE;
            DWORD dwResult = 0;
            CRONO_LOG_DEBUG("ReleaseMutex(detached)...");
            if ((ReleaseMutex(detached))) {
                return true;
            } else {
                DWORD dwError  = GetLastError();
                CRONO_LOG_ERROR("...failed dwError = " << dwError << " on ReleaseMutex(detached)");
            }
        }
        return false;
    }
    virtual LockStatus TryLock() {
        return TimedLock(0);
    }
    virtual LockStatus TimedLock(mseconds_t milliseconds) {
            if (0 > (milliseconds)) {
                return UntimedLock();
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
                            return LockBusy;
                        case WAIT_ABANDONED:
                            CRONO_LOG_ERROR("...WAIT_ABANDONED dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                            return LockInterrupted;
                        default:
                            CRONO_LOG_ERROR("...failed dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                            return LockFailed;
                        }
                    } else {
                        CRONO_LOG_DEBUG("...WaitForSingleObject(detached, dwMilliseconds)");
                        return LockSuccess;
                    }
                }
            }
        return LockFailed;
    }
    virtual LockStatus UntimedLock() {
        HANDLE detached = 0;
        if ((detached = this->m_attachedTo)) {
            DWORD dwMilliseconds = INFINITE;
            DWORD dwResult = 0;
            CRONO_LOG_DEBUG("WaitForSingleObject(detached, dwMilliseconds)...");
            if (WAIT_OBJECT_0 != (dwResult = WaitForSingleObject(detached, dwMilliseconds))) {
                switch(dwResult) {
                case WAIT_TIMEOUT:
                    CRONO_LOG_ERROR("...WAIT_TIMEOUT dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                    return LockBusy;
                case WAIT_ABANDONED:
                    CRONO_LOG_ERROR("...WAIT_ABANDONED dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                    return LockInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed dwResult = " << dwResult << " on WaitForSingleObject(detached, dwMilliseconds)...");
                    return LockFailed;
                }
            } else {
                CRONO_LOG_DEBUG("...WaitForSingleObject(detached, dwMilliseconds)");
                return LockSuccess;
            }
        }
        return LockFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
};
typedef MutexT<> Mutex;

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_MICROSOFT_WINDOWS_MUTEX_HPP 
