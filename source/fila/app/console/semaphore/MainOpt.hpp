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
///   File: MainOpt.hpp
///
/// Author: $author$
///   Date: 8/16/2025
///////////////////////////////////////////////////////////////////////
#ifndef FILA_APP_CONSOLE_SEMAPHORE_MAINOPT_HPP
#define FILA_APP_CONSOLE_SEMAPHORE_MAINOPT_HPP

#include "fila/app/console/mt/Main.hpp"

//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_SEMAPHORE_MAIN_OPTIONS_CHARS_EXTEND \

#define FILA_APP_CONSOLE_SEMAPHORE_MAIN_OPTIONS_OPTIONS_EXTEND \

///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_SEMAPHORE_MAIN_OPTIONS_CHARS \
   FILA_APP_CONSOLE_SEMAPHORE_MAIN_OPTIONS_CHARS_EXTEND \
   FILA_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS \

#define FILA_APP_CONSOLE_SEMAPHORE_MAIN_OPTIONS_OPTIONS \
   FILA_APP_CONSOLE_SEMAPHORE_MAIN_OPTIONS_OPTIONS_EXTEND \
   FILA_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS \

///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_SEMAPHORE_MAIN_ARGS 0
#define FILA_APP_CONSOLE_SEMAPHORE_MAIN_ARGV 0,

namespace fila {
namespace app {
namespace console {
namespace semaphore {

///////////////////////////////////////////////////////////////////////
/// class MainOptt
///////////////////////////////////////////////////////////////////////
template <class TExtends = ::fila::app::console::mt::Main, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS MainOptt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef MainOptt Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    MainOptt() {
    }
    virtual ~MainOptt() {
    }
private:
    MainOptt(const MainOptt& copy): Extends(copy) {
    }
public:
protected:
    ///////////////////////////////////////////////////////////////////////
    /// OnOption
    virtual int OnOption
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        default:
            err = Extends::OnOption(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    //////////////////////////////////////////////////////////////////////////
    /// OptionUsage
    virtual const char_t* OptionUsage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        default:
            chars = Extends::OptionUsage(optarg, longopt);
            break;
        }
        return chars;
    }
    //////////////////////////////////////////////////////////////////////////
    /// Options
    virtual const char_t* Options(const struct option*& longopts) {
        static const char_t* chars = FILA_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            FILA_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    //////////////////////////////////////////////////////////////////////////
    /// Arguments
    virtual const char_t* Arguments(const char_t**& argv) {
        static const char_t* _args = FILA_APP_CONSOLE_MT_MAIN_ARGS;
        static const char_t* _argv[] = {
            FILA_APP_CONSOLE_MT_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class MainOptt
typedef MainOptt<> MainOpt;

} /// namespace semaphore 
} /// namespace console 
} /// namespace app 
} /// namespace fila 

#endif /// ndef FILA_APP_CONSOLE_SEMAPHORE_MAINOPT_HPP 
