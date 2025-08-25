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
///   File: DLLibraryExporter.cpp
///
/// Author: $author$
///   Date: 12/26/2018
///////////////////////////////////////////////////////////////////////
#include "fila/app/console/libhello/DLLibraryExporter.hpp"

namespace fila {
namespace app {
namespace console {
namespace libhello {

///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
static Main theMain;

///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryExporter
///////////////////////////////////////////////////////////////////////
static DLLibraryExporter theDLLibraryExporter;

} /// namespace libhello
} /// namespace console
} /// namespace app
} /// namespace fila

_PLATFORM_EXPORT ::fila::app::console::libhello::Main* 
FILA_APP_CONSOLE_LIBHELLO_ACQUIRE(int& err) {
    ::fila::app::console::libhello::Main* main = 0;
    main = &::fila::app::console::libhello::theMain;
    err = 0;
    return main;
}

_PLATFORM_EXPORT int 
FILA_APP_CONSOLE_LIBHELLO_RELEASE(::fila::app::console::libhello::Main* main) {
    int err = 1;
    if ((&::fila::app::console::libhello::theMain == main)) {
        err = 0;
    }
    return err;
}
