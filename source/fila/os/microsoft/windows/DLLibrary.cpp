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
///   File: DLLibrary.cpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#include "fila/os/microsoft/windows/DLLibrary.hpp"

#if !defined(WINDOWS)
#include "fila/os/posix/DLLibrary.hpp"
#endif // !defined(WINDOWS)

namespace fila {
namespace os {
namespace microsoft {
namespace windows {

} // namespace windows 
} // namespace microsoft 
} // namespace os 
} // namespace fila 

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
HMODULE WINAPI LoadLibrary(_In_ LPCTSTR lpFileName) {
    if ((lpFileName)) {
        ::fila::String name(lpFileName);
        const char* fileName = 0;
        if ((fileName = name.has_chars())) {
            ::fila::os::posix::DLLibrary dl;
            HMODULE detached = 0;
            if ((detached = dl.OpenDetached(fileName))) {
                return detached;
            }
        }
    }
    return 0;
}
BOOL WINAPI FreeLibrary(_In_ HMODULE hModule) {
    if ((hModule)) {
        ::fila::os::posix::DLLibrary dl;
        if ((dl.CloseDetached(hModule))) {
            return TRUE;
        }
    }
    return FALSE;
}
FARPROC WINAPI GetProcAddress(_In_ HMODULE hModule, _In_ LPCSTR  lpProcName) {
    if ((hModule) && (lpProcName)) {
        ::fila::String procName(lpProcName);
        const char* symbol = 0;
        if ((symbol = procName.chars())) {
            ::fila::os::posix::DLLibrary dl(hModule);
            void* address = 0;
            if ((address = dl.GetAddress(symbol))) {
                return address;
            }
        }
    }
    return 0;
}
#endif // !defined(WINDOWS)
