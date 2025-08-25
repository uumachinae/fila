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
#ifndef _FILA_OS_POSIX_DLLIBRARY_HPP
#define _FILA_OS_POSIX_DLLIBRARY_HPP

#include "fila/os/DLLibrary.hpp"
#include "fila/base/Opened.hpp"
#include "fila/base/Attached.hpp"
#include "crono/io/Logger.hpp"

#include <dlfcn.h>

namespace fila {
namespace os {
namespace posix {

typedef void* DLLibraryTAttachedT;
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
    DLLibraryT(void* attachedTo = 0, bool isOpen = false)
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
        void* detached = 0;
        if ((detached = OpenAttached(fileName, resolve, global))) {
            this->SetIsOpen();
            return true;
        }
        return false;
    }
    virtual bool Close() {
        void* detached = 0;
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
        void* detached = 0;
        if ((detached = this->AttachedTo())) {
            void* address = 0;
            CRONO_LOG_DEBUG("dlsym(detached, symbol = \"" << symbol << "\")...");
            if ((address = dlsym(detached, symbol))) {
                return address;
            } else {
                CRONO_LOG_ERROR("...failed 0 = dlsym(detached, symbol = \"" << symbol << "\")");
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* OpenAttached
    (const char* fileName, bool resolve = true, bool global = false) {
        void* detached = 0;
        if ((detached = OpenDetached(fileName, resolve, global))) {
            this->Attach(detached);
            return detached;
        }
        return 0;
    }
    virtual void* OpenDetached
    (const char* fileName, bool resolve = true, bool global = false) const {
        if ((fileName)) {
            String name;

            if ((fileName = this->FileName(name, fileName))) {
                void* detached = 0;
                int mode = ((resolve)?(RTLD_NOW):(RTLD_LAZY))
                           | ((global)?(RTLD_GLOBAL):(RTLD_LOCAL));

                CRONO_LOG_DEBUG("dlopen(fileName = \"" << fileName << "\", mode)...");
                if ((detached = dlopen(fileName, mode))) {
                    return detached;
                } else {
                    char *err = dlerror();
                    CRONO_LOG_ERROR("...failed err = \"" << err << "\" on dlopen(fileName = \"" << fileName << "\", mode)");
                }
            }
        }
        return 0;
    }
    virtual bool CloseDetached(void* detached) const {
        if ((detached)) {
            int err = 0;

            CRONO_LOG_DEBUG("dlclose(detached)...");
            if ((err = dlclose(detached))) {
                char *err = dlerror();
                CRONO_LOG_DEBUG("...failed err = \"" << err << "\" on dlclose(detached)");
            } else {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef DLLibraryT<> DLLibrary;

} // namespace posix
} // namespace os 
} // namespace fila 

#endif // _FILA_OS_POSIX_DLLIBRARY_HPP 
