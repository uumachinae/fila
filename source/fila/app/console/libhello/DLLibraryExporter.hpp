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
///   File: DLLibraryExporter.hpp
///
/// Author: $author$
///   Date: 12/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_APP_CONSOLE_LIBHELLO_DLLIBRARYEXPORTER_HPP
#define _FILA_APP_CONSOLE_LIBHELLO_DLLIBRARYEXPORTER_HPP

#include "fila/os/os/DLLibrary.hpp"
#include "patrona/console/MainImplement.hpp"

#define FILA_APP_CONSOLE_LIBHELLO_ACQUIRE MainAcquire
#define FILA_APP_CONSOLE_LIBHELLO_ACQUIRE_SYMBOL FILA_OS_DLLIBRARY_SYMBOL(FILA_APP_CONSOLE_LIBHELLO_ACQUIRE)

#define FILA_APP_CONSOLE_LIBHELLO_RELEASE MainRelease
#define FILA_APP_CONSOLE_LIBHELLO_RELEASE_SYMBOL FILA_OS_DLLIBRARY_SYMBOL(FILA_APP_CONSOLE_LIBHELLO_RELEASE)

namespace fila {
namespace app {
namespace console {
namespace libhello {

typedef ::patrona::console::MainImplement MainImplements;
typedef ::fila::Base MainExtends;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplements, public MainExtends {
public:
    typedef MainImplements Implements;
    typedef MainExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {}
    virtual ~Main() {}
private:
    Main(const Main& copy) {}
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char_t**argv, char_t** env) {
        int err = 0;
        this->OutLn("Hello");
        this->OutFlush();
        return err;
    }
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int operator()(int argc, char_t **argv, char_t **env) {
        return Implements::operator()(argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS Main

typedef ImplementBase DLLibraryExporterImplements;
typedef Base DLLibraryExporterExtends;
///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryExporter
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLLibraryExporter
: virtual public DLLibraryExporterImplements, public DLLibraryExporterExtends {
public:
    typedef DLLibraryExporterImplements Implements;
    typedef DLLibraryExporterExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLLibraryExporter() {}
    virtual ~DLLibraryExporter() {}
private:
    DLLibraryExporter(const DLLibraryExporter& copy) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS DLLibraryExporter

} /// namespace libhello
} /// namespace console
} /// namespace app
} /// namespace fila

extern "C" {

typedef _PLATFORM_EXPORT ::fila::app::console::libhello::Main* FMainAcquire(int& err);
typedef _PLATFORM_EXPORT int FMainRelease(::fila::app::console::libhello::Main* main);

_PLATFORM_EXPORT ::fila::app::console::libhello::Main* FILA_APP_CONSOLE_LIBHELLO_ACQUIRE(int& err);
_PLATFORM_EXPORT int FILA_APP_CONSOLE_LIBHELLO_RELEASE(::fila::app::console::libhello::Main* main);

} /// extern "C"

#endif /// ndef _FILA_APP_CONSOLE_LIBHELLO_DLLIBRARYEXPORTER_HPP
