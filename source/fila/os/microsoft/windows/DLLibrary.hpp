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
///   File: DLLibrary.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_OS_MICROSOFT_WINDOWS_DLLIBRARY_HPP
#define _FILA_OS_MICROSOFT_WINDOWS_DLLIBRARY_HPP

#include "fila/os/DLLibrary.hpp"
#include "fila/base/Opened.hpp"
#include "fila/base/Attached.hpp"
#include "crono/io/Logger.hpp"

#if !defined(WINDOWS)
extern "C" {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
HMODULE WINAPI LoadLibrary(_In_ LPCTSTR lpFileName);
BOOL WINAPI FreeLibrary(_In_ HMODULE hModule);
FARPROC WINAPI GetProcAddress(_In_ HMODULE hModule, _In_ LPCSTR  lpProcName);
}
#endif // !defined(WINDOWS)

namespace fila {
namespace os {
namespace microsoft {
namespace windows {

typedef HMODULE DLLibraryTAttachedT;
typedef ::patrona::OpenerT<fila::os::DLLibrary> DLLibraryTAttacherImplements;
typedef ::patrona::AttacherT<DLLibraryTAttachedT, int, 0, DLLibraryTAttacherImplements> DLLibraryTAttacher;
typedef ::patrona::AttachedT<DLLibraryTAttachedT, int, 0, DLLibraryTAttacher> DLLibraryTAttached;
typedef ::patrona::OpenedT<DLLibraryTAttachedT, int, 0, DLLibraryTAttacher, DLLibraryTAttached> DLLibraryTOpened;
typedef DLLibraryTAttacher DLLibraryTImplements;
typedef DLLibraryTOpened DLLibraryTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = DLLibraryTImplements, class TExtends = DLLibraryTExtends>

class _EXPORT_CLASS DLLibraryT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLLibraryT(HMODULE attachedTo = 0, bool isOpen = false)
    : Extends(attachedTo, isOpen) {
    }
    virtual ~DLLibraryT() {
        if (!(this->Closed())) {
            OpenException e(CloseFailed);
            CRONO_LOG_ERROR("throw (e = CloseFailed)...")
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open
    (const char* fileName, bool resolve = true, bool global = false) {
        HMODULE detached = 0;
        if ((detached = OpenAttached(fileName, resolve, global))) {
            this->SetIsOpen();
            return true;
        }
        return false;
    }
    virtual bool Close() {
        HMODULE detached = 0;
        if ((detached = this->Detach())) {
            if ((CloseDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* GetAddress(const char* symbol) const {
        HMODULE hModule = 0;

        if ((hModule = this->AttachedTo())) {
            String procName(symbol);
            LPCSTR lpProcName = 0;

            if ((lpProcName = procName.has_chars())) {
                void* address = 0;

                CRONO_LOG_DEBUG("GetProcAddress(hModule, lpProcName = \"" << symbol << "\")...");
                if ((address = GetProcAddress(hModule, lpProcName))) {
                    return address;
                } else {
                    CRONO_LOG_ERROR("...failed 0 = GetProcAddress(hModule, lpProcName = \"" << symbol << "\")");
                }
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HMODULE OpenAttached
    (const char* fileName, bool resolve = true, bool global = false) {
        HMODULE detached = 0;
        if ((detached = OpenDetached(fileName, resolve, global))) {
            this->Attach(detached);
            return detached;
        }
        return 0;
    }
    virtual HMODULE OpenDetached
    (const char* fileName, bool resolve = true, bool global = false) const {
        if ((fileName)) {
            String name;

            if ((fileName = this->FileName(name, fileName))) {
                TString tFileName(fileName);
                LPCTSTR lpFileName = 0;

                if ((lpFileName = tFileName.has_chars())) {
                    HMODULE detached = 0;

                    CRONO_LOG_DEBUG("LoadLibrary(lpFileName = \"" << fileName << "\")...")
                    if ((detached = LoadLibrary(lpFileName))) {
                        return detached;
                    } else {
                        CRONO_LOG_ERROR("...failed 0 on LoadLibrary(lpFileName = \"" << fileName << "\")")
                    }
                }
            }
        }
        return 0;
    }
    virtual bool CloseDetached(HMODULE detached) const {
        if ((detached)) {

            CRONO_LOG_DEBUG("FreeLibrary(detached)...");
            if ((FreeLibrary(detached))) {
                return true;
            } else {
                CRONO_LOG_ERROR("...failed on FreeLibrary(detached)");
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef DLLibraryT<> DLLibrary;

} // namespace windows
} // namespace microsoft 
} // namespace os 
} // namespace fila 

#endif // _FILA_OS_MICROSOFT_WINDOWS_DLLIBRARY_HPP 
