///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2022 $organization$
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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 12/13/2022, 8/13/2025
///////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_MT_MAIN_OPT_HPP
#define XOS_APP_CONSOLE_MT_MAIN_OPT_HPP

#include "xos/app/console/os/main.hpp"

#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPT "threads"
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTARG "[number]"
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTUSE "number of threads"
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTVAL_S "r::"
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTVAL_C 'r'
#define XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTION \
   {XOS_APP_CONSOLE_MT_MAIN_THREADS_OPT, \
    XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTARG_RESULT, \
    XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTVAL_C}, \

#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPT "sleep"
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTARG "[milliseconds]"
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTUSE "sleep time"
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTVAL_S "s::"
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTVAL_C 's'
#define XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTION \
   {XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPT, \
    XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTARG_RESULT, \
    XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTVAL_C}, \

#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPT "timeout"
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTARG "[milliseconds]"
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTUSE "wait timeout"
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTVAL_S "t::"
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTVAL_C 't'
#define XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTION \
   {XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPT, \
    XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTVAL_S \
   XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTVAL_S \
   XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTVAL_S \

#define XOS_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTION \
   XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTION \
   XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTION \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MT_MAIN_MT_OPTIONS_CHARS \
   XOS_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_OPTIONS_CHARS \

#define XOS_APP_CONSOLE_MT_MAIN_MT_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_FRAMEWORK_VERSION_MAIN_OPTIONS_OPTIONS \

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS \
   XOS_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS_EXTEND \
   XOS_APP_CONSOLE_OS_MAIN_OPTIONS_CHARS

#define XOS_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS_EXTEND \
   XOS_APP_CONSOLE_OS_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_MT_MAIN_ARGS 0
#define XOS_APP_CONSOLE_MT_MAIN_ARGV 0,

namespace xos {
namespace app {
namespace console {
namespace mt {

/// class main_optt
template 
<class TExtends = xos::app::console::os::main, 
 class TImplements = typename TExtends::implements>

class exported main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef main_optt derives;

    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t;
    enum { end_char = extends::end_char };
    typedef typename extends::string_t string_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;
    typedef typename extends::file_t file_t;

    /// constructor / destructor
    main_optt(): run_(0) {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt& copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename extends::in_reader_t in_reader_t;
    typedef typename extends::out_writer_t out_writer_t;
    typedef typename extends::err_writer_t err_writer_t;

    /// ...run
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
            err = extends::run(argc, argv, env);
        }
        return err;
    }

    /// ...threads_option...
    virtual int on_get_threads_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_threads_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_threads_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_threads_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_threads_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_threads_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_threads_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_threads_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_threads_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* threads_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTUSE;
        optarg = XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTARG;
        return chars;
    }

    /// ...sleep_option...
    virtual int on_get_sleep_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_sleep_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_sleep_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_sleep_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_sleep_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_sleep_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_sleep_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_sleep_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_sleep_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* sleep_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTUSE;
        optarg = XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTARG;
        return chars;
    }

    /// ...timeout_option...
    virtual int on_get_timeout_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_timeout_option_get
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_timeout_option
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_timeout_option_set
    (const char_t* optarg, int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
        }
        return err;
    }
    virtual int on_timeout_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(err = on_set_timeout_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_timeout_option_set(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        } else {
            if (!(err = on_get_timeout_option(optarg, optind, argc, argv, env))) {
                if (!(err = on_timeout_option_get(optarg, optind, argc, argv, env))) {
                } else {
                }
            } else {
            }
        }
        return err;
    }
    virtual const char_t* timeout_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTUSE;
        optarg = XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTARG;
        return chars;
    }

    /// ...option...
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname,
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {

        case XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTVAL_C:
            err = this->on_threads_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTVAL_C:
            err = this->on_sleep_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTVAL_C:
            err = this->on_timeout_option(optval, optarg, optname, optind, argc, argv, env);
            break;

        default:
            err = extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {

        case XOS_APP_CONSOLE_MT_MAIN_THREADS_OPTVAL_C:
            chars = this->threads_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_MT_MAIN_SLEEP_OPTVAL_C:
            chars = this->sleep_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_MT_MAIN_TIMEOUT_OPTVAL_C:
            chars = this->timeout_option_usage(optarg, longopt);
            break;

        default:
            chars = extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = XOS_APP_CONSOLE_MT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_CONSOLE_MT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    /// ...argument...
    virtual const char_t* arguments(const char_t**& argv) {
        static const char_t* _args = XOS_APP_CONSOLE_MT_MAIN_ARGS;
        static const char_t* _argv[] = {
            XOS_APP_CONSOLE_MT_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }

protected:
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace mt
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// ndef XOS_APP_CONSOLE_MT_MAIN_OPT_HPP
