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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_APP_CONSOLE_HELLO_MAIN_HPP
#define _FILA_APP_CONSOLE_HELLO_MAIN_HPP

#include "fila/app/console/libhello/DLLibraryExporter.hpp"
#include "fila/console/getopt/Main.hpp"
#include "fila/mt/os/Process.hpp"
#include "fila/mt/os/Thread.hpp"
#include "fila/mt/os/Semaphore.hpp"
#include "fila/mt/os/Mutex.hpp"
#include "fila/mt/os/Sleep.hpp"
#include "fila/os/os/DLLibrary.hpp"
#include "fila/base/Argv.hpp"
#include "fila/base/Base.hpp"
#include "crono/io/Logger.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPT "dlibrary"
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTARG_RESULT 0
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTARG ""
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTUSE ""
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTVAL_S "d"
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTVAL_C 'd'
#define FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTION \
   {FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPT, \
    FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTARG_REQUIRED, \
    FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTARG_RESULT, \
    FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTVAL_C}, \

#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPT "process"
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTARG_RESULT 0
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTARG ""
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTUSE ""
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTVAL_S "p"
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTVAL_C 'p'
#define FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTION \
   {FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPT, \
    FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTARG_REQUIRED, \
    FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTARG_RESULT, \
    FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTVAL_C}, \

#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPT "thread"
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTARG_RESULT 0
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTARG ""
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTUSE ""
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTVAL_S "t"
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTVAL_C 't'
#define FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTION \
   {FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPT, \
    FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTARG_REQUIRED, \
    FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTARG_RESULT, \
    FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_HELLO_MAIN_OPTIONS_CHARS \
   FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTVAL_S \
   FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTVAL_S \
   FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTVAL_S \
   FILA_MAIN_OPTIONS_CHARS

#define FILA_APP_CONSOLE_HELLO_MAIN_OPTIONS_OPTIONS \
   FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTION \
   FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTION \
   FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTION \
   FILA_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define FILA_APP_CONSOLE_HELLO_MAIN_ARGS "[path/seconds]"
#define FILA_APP_CONSOLE_HELLO_MAIN_ARGV \
"[path] library or executable path", \
"[seconds] thread wait seconds",

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace fila {
namespace app {
namespace console {
namespace hello {

typedef fila::console::getopt::Main MainExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: public MainExtends {
public:
    typedef MainExtends Extends;
    typedef Main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main(): m_run(0) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char_t **argv, char_t **env) {
        int err = 0;
        if ((m_run)) {
            err = (this->*m_run)(argc, argv, env);
        } else {
            err = Usage(argc, argv, env);
        }
        return err;
    }
    virtual int LibraryRun(int argc, char_t **argv, char_t **env) {
        int err = 0, err2 = 0;
        const char* libraryName = "hello";
        if ((argc > (optind)) && (argv[optind]) && (argv[optind][0])) {
            libraryName = argv[optind];
        }
        try {
            libhello::Main* main = 0;
            FMainAcquire* acquire = 0;
            FMainRelease* release = 0;
            os::os::DLLibrary dl;

            dl.Open(libraryName);
            CRONO_LOG_DEBUG("dl.GetAddress(\"" << FILA_APP_CONSOLE_LIBHELLO_ACQUIRE_SYMBOL << "\")...");
            if ((acquire = (FMainAcquire*)dl.GetAddress(FILA_APP_CONSOLE_LIBHELLO_ACQUIRE_SYMBOL))) {
                CRONO_LOG_DEBUG("..." << PointerToString((pointer_t)acquire).Chars() << " = dl.GetAddress(\"" << FILA_APP_CONSOLE_LIBHELLO_ACQUIRE_SYMBOL << "\")");

                CRONO_LOG_DEBUG("dl.GetAddress(\"" << FILA_APP_CONSOLE_LIBHELLO_RELEASE_SYMBOL << "\")...");
                if ((release = (FMainRelease*)dl.GetAddress(FILA_APP_CONSOLE_LIBHELLO_RELEASE_SYMBOL))) {
                    CRONO_LOG_DEBUG("..." << PointerToString((pointer_t)release).Chars() << " = dl.GetAddress(\"" << FILA_APP_CONSOLE_LIBHELLO_RELEASE_SYMBOL << "\")");

                    CRONO_LOG_DEBUG("acquire(err2)...");
                    if ((main = acquire(err2))) {
                        CRONO_LOG_DEBUG("...acquire(err2)");

                        (*main)(argc, argv, env);
                        
                        CRONO_LOG_DEBUG("release(main)...");
                        if (!(err2 = release(main))) {
                            CRONO_LOG_DEBUG("...release(main)");
                        } else {
                            CRONO_LOG_DEBUG("...failed " << err << " on release(main)");
                        }
                    } else {
                        CRONO_LOG_ERROR("...failed " << PointerToString(main).Chars() << " on acquire(err2 = " << err2 << ")");
                    }
                } else {
                    CRONO_LOG_ERROR("...failed " << PointerToString((pointer_t)release).Chars() << " = dl.GetAddress(\"" << FILA_APP_CONSOLE_LIBHELLO_RELEASE_SYMBOL << "\")");
                }
            } else {
                CRONO_LOG_ERROR("...failed " << PointerToString((pointer_t)acquire).Chars() << " = dl.GetAddress(\"" << FILA_APP_CONSOLE_LIBHELLO_ACQUIRE_SYMBOL << "\")");
            }
        } catch (const OpenException& e) {
            CRONO_LOG_ERROR("...caught const OpenException& e = \"" << e.StatusToChars() << "\"");
        }
        return err;
    }
    virtual int ProcessRun(int argc, char_t **argv, char_t **env) {
        int err = 0;
        const char* exeName = "hello";
        if ((argc > (optind)) && (argv[optind]) && (argv[optind][0])) {
            exeName = argv[optind];
        }
        try {
            fila::Argv argv(&exeName, 1);
            fila::mt::os::Process p;
            p.Create(exeName, argv.Elements(), env, 0, 0);
        } catch (const CreateException& e) {
            CRONO_LOG_ERROR("...caught const CreateException& e = \"" << e.StatusToChars() << "\"");
        }
        return err;
    }
    virtual int ThreadRun(int argc, char_t **argv, char_t **env) {
        seconds_t start = 0, finish = 0, threadSeconds = 3;
        const char_t *arg = 0;
        if ((argc > (optind)) && (arg = argv[optind]) && (arg[0])) {
            unsigned value = Chars::ToUnsigned(arg);
            if (0 < (value)) {
                threadSeconds = value;
            }
        }
        class Thread: public mt::os::Thread {
        public:
            Thread(Main& main, mt::os::Semaphore& sem, const seconds_t& start, const seconds_t& seconds)
            : m_main(main), m_sem(sem), m_start(start), m_seconds(seconds) {
            }
            virtual void Run() {
                seconds_t finish = ::time(NULL);
                for (seconds_t seconds = m_seconds; seconds > 0; --seconds) {
                    CRONO_LOG_DEBUG("mt::os::SleepSeconds(1)...");
                    mt::os::SleepSeconds(1);
                    CRONO_LOG_DEBUG("...mt::os::SleepSeconds(1)");
                    finish = ::time(NULL);
                    try {
                        m_main.OutL("...", UnsignedToString(finish-m_start).Chars(), " seconds...\n", NULL);
                        m_main.OutFlush();
                    } catch (const LockException& e) {
                        CRONO_LOG_ERROR("...caught const LockException& e = \"" << e.StatusToChars() << "\"");
                    }
                }
                CRONO_LOG_DEBUG("m_sem.Release()...");
                m_sem.Release();
            }
            Main& m_main;
            mt::os::Semaphore& m_sem;
            const seconds_t &m_start, &m_seconds;
        };
        start = ::time(NULL);
        OutLn("Start...");
        OutFlush();
        try {
            mt::os::Semaphore sem;
            mt::os::Mutex mutex;
            Thread thread(*this,sem,start,threadSeconds);
            Acquirer acquire(sem);
            Locker lock(mutex);

            finish = ::time(NULL);
            OutL("...Finished in ", UnsignedToString(finish-start).Chars(), " seconds\n", NULL);
            OutFlush();
        } catch (const AcquireException& e) {
            CRONO_LOG_ERROR("...caught const AcquireException& e = \"" << e.StatusToChars() << "\"");
        } catch (const LockException& e) {
            CRONO_LOG_ERROR("...caught const LockException& e = \"" << e.StatusToChars() << "\"");
        } catch (const CreateException& e) {
            CRONO_LOG_ERROR("...caught const CreateException& e = \"" << e.StatusToChars() << "\"");
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLibraryOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        m_run = &Derives::LibraryRun;
        return err;
    }
    virtual int OnProcessOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        m_run = &Derives::ProcessRun;
        return err;
    }
    virtual int OnThreadOption
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        m_run = &Derives::ThreadRun;
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
        case FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTVAL_C:
            err = OnLibraryOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTVAL_C:
            err = OnProcessOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTVAL_C:
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
        case FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTVAL_C:
            optarg = FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTARG;
            chars = FILA_APP_CONSOLE_HELLO_MAIN_LIBRARY_OPTUSE;
            break;
        case FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTVAL_C:
            optarg = FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTARG;
            chars = FILA_APP_CONSOLE_HELLO_MAIN_PROCESS_OPTUSE;
            break;
        case FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTVAL_C:
            optarg = FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTARG;
            chars = FILA_APP_CONSOLE_HELLO_MAIN_THREAD_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char_t* Options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = FILA_APP_CONSOLE_HELLO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            FILA_APP_CONSOLE_HELLO_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* Arguments(const char_t**& argv) {
        static const char_t* _args = FILA_APP_CONSOLE_HELLO_MAIN_ARGS;
        static const char_t* _argv[] = {
            FILA_APP_CONSOLE_HELLO_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*MRun)(int argc, char_t **argv, char_t **env);
    MRun m_run;
};

} // namespace hello
} // namespace console 
} // namespace app 
} // namespace fila 

#endif // _FILA_APP_CONSOLE_HELLO_MAIN_HPP 
