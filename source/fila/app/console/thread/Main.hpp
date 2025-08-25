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
///   Date: 8/17/2025
///////////////////////////////////////////////////////////////////////
#ifndef FILA_APP_CONSOLE_THREAD_MAIN_HPP
#define FILA_APP_CONSOLE_THREAD_MAIN_HPP

#include "fila/app/console/thread/MainOpt.hpp"
#include "fila/mt/os/Thread.hpp"
#include "fila/mt/os/Semaphore.hpp"
#include "fila/mt/os/Mutex.hpp"
#include "fila/mt/os/Sleep.hpp"

namespace fila {
namespace app {
namespace console {
namespace thread {

///////////////////////////////////////////////////////////////////////
/// class Maint
///////////////////////////////////////////////////////////////////////
template <class TExtends = fila::app::console::thread::MainOpt, class TImplements = typename TExtends::Implements>
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
    Maint(const Maint& copy) {
    }
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*m_run)(int argc, char_t**argv, char_t** env);
    virtual int Run(int argc, char_t**argv, char_t** env) {
        int err = 0;
        SetThreadRun(argc, argv, env);
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
    virtual int ThreadRun(int argc, char_t **argv, char_t **env) {
        ///////////////////////////////////////////////////////////////////////
        /// class Thread
        ///////////////////////////////////////////////////////////////////////
        class Thread: public fila::mt::os::Thread {
        public:
            ///////////////////////////////////////////////////////////////////////
            /// constructor / destructor
            ///////////////////////////////////////////////////////////////////////
            Thread(Maint& main, fila::mt::os::Mutex& mutex, fila::mt::os::Semaphore& sem, const seconds_t& start, const seconds_t& seconds)
            : m_main(main), m_mutex(mutex), m_sem(sem), m_start(start), m_seconds(seconds) {
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            virtual void Run() {
                time_t tm = 0;
                seconds_t finish = ::time(&tm);
                for (seconds_t seconds = m_seconds; seconds > 0; --seconds) {
                    LOG_DEBUG("fila::mt::os::SleepSeconds(1)...");
                    fila::mt::os::SleepSeconds(1);
                    LOG_DEBUG("...fila::mt::os::SleepSeconds(1)");
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
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
        protected:
            Maint& m_main;
            fila::mt::os::Mutex& m_mutex;
            fila::mt::os::Semaphore& m_sem;
            const seconds_t &m_start, &m_seconds;
        }; /// class Thread
        
        seconds_t threadSeconds = 3;
        const char_t *arg = 0;
        int err = 0;

        if ((argc > (optind)) && (arg = argv[optind]) && (arg[0])) {
            unsigned value = Chars::ToUnsigned(arg);
            if (0 < (value)) {
                threadSeconds = value;
            }
        } else {
        }
        this->OutLn("try {...");
        this->OutFlush();
        try {
            time_t tm = 0;
            seconds_t start = ::time(&tm), finish = ::time(&tm);
            fila::mt::os::Semaphore sem;
            fila::mt::os::Mutex mutex;
            this->OutL("Thread thread(*this, mutex, sem, start = ", UnsignedToString(start).Chars(), ", threadSeconds = ", UnsignedToString(threadSeconds).Chars(), ")...\n", NULL);
            this->OutFlush();
            Thread thread(*this, mutex, sem, start, threadSeconds);
            Acquirer acquire(sem);
            Locker lock(mutex);

            finish = ::time(&tm);
            this->OutL("...Finished in ", UnsignedToString(finish-start).Chars(), " seconds\n", NULL);
            this->OutFlush();
        } catch (const AcquireException& e) {
            LOG_ERROR("...caught const AcquireException& e = \"" << e.StatusToChars() << "\"");
        } catch (const LockException& e) {
            LOG_ERROR("...caught const LockException& e = \"" << e.StatusToChars() << "\"");
        } catch (const CreateException& e) {
            LOG_ERROR("...caught const CreateException& e = \"" << e.StatusToChars() << "\"");
        }
        this->OutLn("...} try");
        this->OutFlush();
        return err;
    }
    virtual int SetThreadRun(int argc, char_t **argv, char_t **env) {
        int err = 0;
        m_run = &Derives::ThreadRun;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class Maint
typedef Maint<> Main;

} /// namespace thread 
} /// namespace console 
} /// namespace app 
} /// namespace fila 

#endif /// ndef FILA_APP_CONSOLE_THREAD_MAIN_HPP 
