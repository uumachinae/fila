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
#ifndef FILA_APP_CONSOLE_MUTEX_MAIN_HPP
#define FILA_APP_CONSOLE_MUTEX_MAIN_HPP

#include "fila/app/console/mutex/MainOpt.hpp"
#include "fila/mt/os/Mutex.hpp"

namespace fila {
namespace app {
namespace console {
namespace mutex {

///////////////////////////////////////////////////////////////////////
/// class Maint
///////////////////////////////////////////////////////////////////////
template <class TExtends = ::fila::app::console::mutex::MainOpt, class TImplements = typename TExtends::Implements>
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
        SetMutexRun(argc, argv, env);
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
    virtual int MutexRun(int argc, char_t **argv, char_t **env) {
        int err = 0;
        const char_t *arg = 0;
        signed_t milliSeconds = -1;
        
        if ((argc > (optind)) && (arg = argv[optind]) && (arg[0])) {
            unsigned value = Chars::ToSigned(arg);
            if (0 <= (value)) {
                milliSeconds = value;
            }
        } else {
        }
        this->OutLn("Try {...");
        this->OutFlush();
        try {
            mt::os::Mutex mutex;
            this->OutL("if ((0 <= (milliSeconds = ", SignedToString(milliSeconds).Chars(), "))) {...", "\n", NULL);
            this->OutFlush();
            if ((0 <= (milliSeconds))) {
                this->OutL("Locker lock(mutex, milliSeconds = ", SignedToString(milliSeconds).Chars(), ")...", "\n", NULL);
                this->OutFlush();
                Locker lock(mutex, milliSeconds);
                this->OutL("...Locker lock(mutex, milliSeconds = ", SignedToString(milliSeconds).Chars(), ")", "\n", NULL);
                this->OutFlush();
            } else {
                this->OutLn("...} else {...");
                this->OutLn("Locker lock(mutex)...");
                this->OutFlush();
                Locker lock(mutex);
                this->OutLn("...Locker lock(mutex)");
                this->OutFlush();
            }
            this->OutLn("...} if");
            this->OutFlush();
        } catch (const LockException& e) {
            LOG_ERROR("...caught (const LockException& e = \"" << e.StatusToChars() << "\")");
        } catch (const CreateException e) {
            LOG_ERROR("...caught (const CreateException& e = \"" << e.StatusToChars() << "\")");
        }
        this->OutLn("...} Try");
        this->OutFlush();
        return err;
    }
    virtual int SetMutexRun(int argc, char_t **argv, char_t **env) {
        int err = 0;
        m_run = &Derives::MutexRun;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class Maint
typedef Maint<> Main;

} /// namespace mutex 
} /// namespace console 
} /// namespace app 
} /// namespace fila 

#endif /// ndef FILA_APP_CONSOLE_MUTEX_MAIN_HPP 
