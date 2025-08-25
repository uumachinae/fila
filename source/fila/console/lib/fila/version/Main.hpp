///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 2/25/2019
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_CONSOLE_LIB_FILA_VERSION_MAIN_HPP
#define _FILA_CONSOLE_LIB_FILA_VERSION_MAIN_HPP

#include "patrona/console/lib/version/Main.hpp"
#include "fila/lib/fila/Version.hpp"
#include "fila/console/getopt/Main.hpp"

namespace fila {
namespace console {
namespace lib {
namespace fila {
namespace version {

typedef ::fila::lib::fila::Version MainTVersion;

typedef ::patrona::console::lib::version::MainT
<MainTVersion, 
 ::fila::console::getopt::Main::Implements, 
 ::fila::console::getopt::Main> MainTExtends;

typedef MainTExtends::Implements MainTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template <class TImplements = MainTImplements, class TExtends = MainTExtends>
class _EXPORT_CLASS MainT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT() {
    }
    virtual ~MainT() {
    }
private:
    MainT(const MainT& copy) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS MainT
typedef MainT<> Main;

} /// namespace version
} /// namespace fila
} /// namespace lib
} /// namespace console
} /// namespace fila

#endif /// _FILA_CONSOLE_LIB_FILA_VERSION_MAIN_HPP 
