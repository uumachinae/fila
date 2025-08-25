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
#include "fila/os/posix/DLLibraryMain.hpp"
#include "fila/os/DLLibraryMain.cpp"

namespace fila {
namespace os {
namespace posix {

} // namespace posix
} // namespace os
} // namespace fila

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void __attribute__ ((constructor)) _posix_init(void) {
    CRONO_STDERR_LOG_DEBUG("fila::os::_init()...");
    fila::os::_init();
    CRONO_STDERR_LOG_DEBUG("...fila::os::_init()");
}
void __attribute__ ((destructor)) _posix_fini(void) {
    CRONO_STDERR_LOG_DEBUG("fila::os::_fini()...");
    fila::os::_fini();
    CRONO_STDERR_LOG_DEBUG("...fila::os::_fini()");
}
