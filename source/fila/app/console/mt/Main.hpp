///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2025 $organization$
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
///   Date: 8/16/2025
///////////////////////////////////////////////////////////////////////
#ifndef FILA_APP_CONSOLE_MT_MAIN_HPP
#define FILA_APP_CONSOLE_MT_MAIN_HPP

#include "fila/app/console/mt/MainOpt.hpp"

namespace fila {
namespace app {
namespace console {
namespace mt {

///////////////////////////////////////////////////////////////////////
/// class Maint
///////////////////////////////////////////////////////////////////////
template <class TExtends = ::fila::app::console::mt::MainOpt, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS Maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef Maint Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    Maint() {
    }
    virtual ~Maint() {
    }
private:
    Maint(const Maint& copy): Extends(copy) {
    }
public:

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*m_run)(int argc, char_t**argv, char_t** env);
    virtual int Run(int argc, char_t**argv, char_t** env) {
        int err = 0;
        ///SetMutexRun(argc, argv, env);
        if ((m_run)) {
            LOG_DEBUG("(this->*m_run)(argc, argv, env)...");
            err = (this->*m_run)(argc, argv, env);
            LOG_DEBUG("..." << err << " = (this->*m_run)(argc, argv, env)");
        } else {
            LOG_DEBUG("...Extends::Run(argc, argv, env)");
            err = Extends::Run(argc, argv, env);
            LOG_DEBUG("..." << err << " = Extends::Run(argc, argv, env)");

            LOG_DEBUG("Extends::Usage(argc, argv, env)...");
            Extends::Usage(argc, argv, env);
            LOG_DEBUG("...Extends::Usage(argc, argv, env)");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:

}; /// class Maint
typedef Maint<> Main;

} /// namespace mt 
} /// namespace console 
} /// namespace app 
} /// namespace fila 

#endif /// ndef FILA_APP_CONSOLE_MT_MAIN_HPP 
