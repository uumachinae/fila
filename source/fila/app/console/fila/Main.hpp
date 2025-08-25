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
#ifndef _FILA_APP_CONSOLE_FILA_MAIN_HPP
#define _FILA_APP_CONSOLE_FILA_MAIN_HPP

#include "fila/app/console/fila/MainOpt.hpp"
#include "fila/mt/os/Process.hpp"
#include "fila/mt/os/Thread.hpp"
#include "fila/mt/os/Semaphore.hpp"
#include "fila/mt/os/Mutex.hpp"
#include "fila/mt/os/Sleep.hpp"
#include "fila/os/os/DLLibrary.hpp"
#include "fila/base/Argv.hpp"

namespace fila {
namespace app {
namespace console {
namespace fila {

typedef MainOpt::Implements MainImplements;
typedef MainOpt MainExtends;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplements, public MainExtends {
public:
    typedef MainImplements Implements;
    typedef MainExtends Extends;
    typedef Main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main(): m_run(0) {
    }
    virtual ~Main() {
    }
private:
    Main(const Main& copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*m_run)(int argc, char_t**argv, char_t** env);
    virtual int Run(int argc, char_t**argv, char_t** env) {
        int err = 0;
        if ((m_run)) {
            LOG_DEBUG("(this->*m_run)(argc, argv, env)...");
            err = (this->*m_run)(argc, argv, env);
            LOG_DEBUG("..." << err << " = (this->*m_run)(argc, argv, env)");
        } else {
            LOG_DEBUG("...Extends::Run(argc, argv, env)");
            err = Extends::Run(argc, argv, env);
            LOG_DEBUG("..." << err << " = Extends::Run(argc, argv, env)");

            LOG_DEBUG("Usage(argc, argv, env)...");
            Usage(argc, argv, env);
            LOG_DEBUG("...Usage(argc, argv, env)");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int LibraryRun(int argc, char_t **argv, char_t **env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ProcessRun(int argc, char_t **argv, char_t **env) {
        const char* exeName = "fila";
        int err = 0;
        if ((argc > (optind)) && (argv[optind]) && (argv[optind][0])) {
            exeName = argv[optind];
        }
        try {
            ::fila::Argv argv(&exeName, 1);
            ::fila::mt::os::Process p;
            p.Create(exeName, argv.Elements(), env, 0, 0);
        } catch (const CreateException& e) {
            LOG_ERROR("...caught const CreateException& e = \"" << e.StatusToChars() << "\"");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ThreadRun(int argc, char_t **argv, char_t **env) {
        class Thread: public mt::os::Thread {
        public:
            Thread(Main& main, mt::os::Mutex& mutex, mt::os::Semaphore& sem, const seconds_t& start, const seconds_t& seconds)
            : m_main(main), m_mutex(mutex), m_sem(sem), m_start(start), m_seconds(seconds) {
            }
            virtual void Run() {
                time_t tm = 0;
                seconds_t finish = ::time(&tm);
                for (seconds_t seconds = m_seconds; seconds > 0; --seconds) {
                    LOG_DEBUG("mt::os::SleepSeconds(1)...");
                    mt::os::SleepSeconds(1);
                    LOG_DEBUG("...mt::os::SleepSeconds(1)");
                    finish = ::time(NULL);
                    try {
                        Locker lock(m_mutex);
                        m_main.OutL("...", UnsignedToString(finish-m_start).Chars(), " seconds...\n", NULL);
                        m_main.OutFlush();
                    } catch (const LockException& e) {
                        LOG_ERROR("...caught const LockException& e = \"" << e.StatusToChars() << "\"");
                    }
                }
                LOG_DEBUG("m_sem.Release()...");
                m_sem.Release();
            }
            Main& m_main;
            mt::os::Mutex& m_mutex;
            mt::os::Semaphore& m_sem;
            const seconds_t &m_start, &m_seconds;
        }; /// class Thread

        seconds_t start = 0, finish = 0, threadSeconds = 3;
        const char_t *arg = 0;
        int err = 0;
        time_t tm = 0;

        if ((argc > (optind)) && (arg = argv[optind]) && (arg[0])) {
            unsigned value = Chars::ToUnsigned(arg);
            if (0 < (value)) {
                threadSeconds = value;
            }
        }
        start = ::time(&tm);
        OutLn("Start...");
        OutFlush();
        try {
            mt::os::Semaphore sem;
            mt::os::Mutex mutex;
            Thread thread(*this, mutex, sem, start, threadSeconds);
            Acquirer acquire(sem);
            Locker lock(mutex);

            finish = ::time(&tm);
            OutL("...Finished in ", UnsignedToString(finish-start).Chars(), " seconds\n", NULL);
            OutFlush();
        } catch (const AcquireException& e) {
            LOG_ERROR("...caught const AcquireException& e = \"" << e.StatusToChars() << "\"");
        } catch (const LockException& e) {
            LOG_ERROR("...caught const LockException& e = \"" << e.StatusToChars() << "\"");
        } catch (const CreateException& e) {
            LOG_ERROR("...caught const CreateException& e = \"" << e.StatusToChars() << "\"");
        }
        return err;
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
}; /// class _EXPORT_CLASS Main

} /// namespace fila
} /// namespace console
} /// namespace app
} /// namespace fila

#endif ///ndef _FILA_APP_CONSOLE_FILA_MAIN_HPP
