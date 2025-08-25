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
///   File: DLLibraryMain.cpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#include "fila/os/microsoft/windows/DLLibraryMain.hpp"
#include "fila/os/DLLibraryMain.cpp"

namespace fila {
namespace os {
namespace microsoft {
namespace windows {

} // namespace windows 
} // namespace microsoft 
} // namespace os 
} // namespace fila 

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch(fdwReason) {
    case DLL_PROCESS_ATTACH:
        // The DLL is being loaded into the virtual address
        // space of the current process as a result of the
        // process starting up or as a result of a call to
        // LoadLibrary. DLLs can use this opportunity to
        // initialize any instance data or to use the TlsAlloc
        // function to allocate a thread local storage (TLS)
        // index.
        CRONO_STDERR_LOG_DEBUG("::fila::os::_init()...");
        ::fila::os::_init();
        break;

    case DLL_PROCESS_DETACH:
        // The DLL is being unloaded from the virtual address
        // space of the calling process as a result of
        // unsuccessfully loading the DLL, termination of the
        // process, or a call to FreeLibrary. The DLL can use
        // this opportunity to call the TlsFree function to
        // free any TLS indices allocated by using TlsAlloc
        // and to free any thread local data.
        CRONO_STDERR_LOG_DEBUG("::fila::os::_fini()...");
        ::fila::os::_fini();
        break;

    case DLL_THREAD_ATTACH:
        // The current process is creating a new thread.
        // When this occurs, the system calls the entry-point
        // function of all DLLs currently attached to the process.
        // The call is made in the context of the new thread.
        // DLLs can use this opportunity to initialize a TLS slot
        // for the thread.
        CRONO_STDERR_LOG_DEBUG("::fila::os::_thread_init()...");
        break;

    case DLL_THREAD_DETACH:
        // A thread is exiting cleanly. If the DLL has stored
        // a pointer to allocated memory in a TLS slot, it
        // should use this opportunity to free the memory.
        // The system calls the entry-point function of all
        // currently loaded DLLs with this value. The call
        // is made in the context of the exiting thread.
        CRONO_STDERR_LOG_DEBUG("::fila::os::_thread_fini()...");
        break;
    }
    return TRUE;
}

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
static HINSTANCE _posix_instance() {
    static DWORD instance = 1;
    return (HINSTANCE)instance;
}
void __attribute__ ((constructor)) _posix_init(void) {
    HINSTANCE hinstDLL = _posix_instance();
    DWORD fdwReason = DLL_PROCESS_ATTACH;
    LPVOID lpvReserved = NULL;
    CRONO_STDERR_LOG_DEBUG("DllMain(hinstDLL, fdwReason, lpvReserved)...");
    DllMain(hinstDLL, fdwReason, lpvReserved);
}
void __attribute__ ((destructor)) _posix_fini(void) {
    HINSTANCE hinstDLL = _posix_instance();
    DWORD fdwReason = DLL_PROCESS_DETACH;
    LPVOID lpvReserved = NULL;
    CRONO_STDERR_LOG_DEBUG("DllMain(hinstDLL, fdwReason, lpvReserved)...");
    DllMain(hinstDLL, fdwReason, lpvReserved);
}
#endif // !defined(WINDOWS)
