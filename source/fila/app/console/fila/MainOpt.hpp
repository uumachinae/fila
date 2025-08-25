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
///   File: MainOpt.hpp
///
/// Author: $author$
///   Date: 2/25/2019
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_APP_CONSOLE_FILA_MAINOPT_HPP
#define _FILA_APP_CONSOLE_FILA_MAINOPT_HPP

#include "fila/console/lib/fila/version/Main.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPT "dlibrary"
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTARG_RESULT 0
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTARG ""
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTUSE ""
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTVAL_S "d"
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTVAL_C 'd'
#define FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTION \
   {FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPT, \
    FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTARG_REQUIRED, \
    FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTARG_RESULT, \
    FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTVAL_C}, \

#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPT "process"
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTARG_RESULT 0
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTARG ""
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTUSE ""
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTVAL_S "p"
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTVAL_C 'p'
#define FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTION \
   {FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPT, \
    FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTARG_REQUIRED, \
    FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTARG_RESULT, \
    FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTVAL_C}, \

#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPT "thread"
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTARG_RESULT 0
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTARG ""
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTUSE ""
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTVAL_S "t"
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTVAL_C 't'
#define FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTION \
   {FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPT, \
    FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTARG_REQUIRED, \
    FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTARG_RESULT, \
    FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_FILA_MAIN_OPTIONS_CHARS \
   FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTVAL_S \
   FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTVAL_S \
   FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTVAL_S \
   FILA_MAIN_OPTIONS_CHARS

#define FILA_APP_CONSOLE_FILA_MAIN_OPTIONS_OPTIONS \
   FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTION \
   FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTION \
   FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTION \
   FILA_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_FILA_MAIN_ARGS "[path/seconds]"
#define FILA_APP_CONSOLE_FILA_MAIN_ARGV \
"[path] library or executable path", \
"[seconds] thread wait seconds",

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace fila {
namespace app {
namespace console {
namespace fila {

typedef ::fila::console::lib::fila::version::Main::Implements MainOptImplements;
typedef ::fila::console::lib::fila::version::Main MainOptExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainOpt
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainOpt: virtual public MainOptImplements, public MainOptExtends {
public:
    typedef MainOptImplements Implements;
    typedef MainOptExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainOpt() {
    }
    virtual ~MainOpt() {
    }
private:
    MainOpt(const MainOpt& copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLibraryOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int OnProcessOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int OnThreadOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTVAL_C:
            err = OnLibraryOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTVAL_C:
            err = OnProcessOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTVAL_C:
            err = OnThreadOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* OptionUsage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTVAL_C:
            optarg = FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTARG;
            chars = FILA_APP_CONSOLE_FILA_MAIN_LIBRARY_OPTUSE;
            break;
        case FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTVAL_C:
            optarg = FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTARG;
            chars = FILA_APP_CONSOLE_FILA_MAIN_PROCESS_OPTUSE;
            break;
        case FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTVAL_C:
            optarg = FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTARG;
            chars = FILA_APP_CONSOLE_FILA_MAIN_THREAD_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char_t* Options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = FILA_APP_CONSOLE_FILA_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            FILA_APP_CONSOLE_FILA_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* Arguments(const char_t**& argv) {
        static const char_t* _args = FILA_APP_CONSOLE_FILA_MAIN_ARGS;
        static const char_t* _argv[] = {
            FILA_APP_CONSOLE_FILA_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS MainOpt

} /// namespace fila
} /// namespace console
} /// namespace app
} /// namespace fila

#endif /// _FILA_APP_CONSOLE_FILA_MAINOPT_HPP 
