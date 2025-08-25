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
///   File: DLLibraryMain.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_OS_MICROSOFT_WINDOWS_DLLIBRARYMAIN_HPP
#define _FILA_OS_MICROSOFT_WINDOWS_DLLIBRARYMAIN_HPP

#include "fila/os/DLLibraryMain.hpp"

#if !defined(WINDOWS)
extern "C" {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    DLL_PROCESS_ATTACH,
    DLL_PROCESS_DETACH,
    DLL_THREAD_ATTACH,
    DLL_THREAD_DETACH
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
}
#endif // !defined(WINDOWS)

namespace fila {
namespace os {
namespace microsoft {
namespace windows {

typedef fila::os::DLLibraryMain DLLibraryMainTImplements;
typedef fila::os::DLLibraryMainExtend DLLibraryMainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryMainT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = DLLibraryMainTImplements,
 class TExtends = DLLibraryMainTExtends>

class _EXPORT_CLASS DLLibraryMainT
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLLibraryMainT() {
    }
    virtual ~DLLibraryMainT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef DLLibraryMainT<> DLLibraryMain;

} // namespace windows
} // namespace microsoft 
} // namespace os 
} // namespace fila 

#endif // _FILA_OS_MICROSOFT_WINDOWS_DLLIBRARYMAIN_HPP 
        

