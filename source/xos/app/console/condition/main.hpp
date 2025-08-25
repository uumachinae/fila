///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: main.hpp
///
/// Author: $author$
///   Date: 1/15/2020, 8/12/2025
///////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_CONDITION_MAIN_HPP
#define XOS_APP_CONSOLE_CONDITION_MAIN_HPP

#include "xos/app/console/condition/main_opt.hpp"
#include "xos/mt/apple/osx/condition.hpp"
#include "xos/mt/linux/condition.hpp"
#include "xos/mt/posix/condition.hpp"
#include "xos/mt/os/condition.hpp"
#include "xos/mt/condition.hpp"

namespace xos {
namespace app {
namespace console {
namespace condition {

/// class maint
template 
<class TExtends = main_opt, 
 class TImplements = typename TExtends::implements>

class exported maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef maint derives;

    typedef typename extends::string_t string_t;
    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t;
    enum { end_char = extends::end_char };

    /// constructor / destructor
    maint() {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy) {
    }

protected:
    /// run
    int run(::xos::waited& waited) {
        int err = 0;
        mseconds_t timeout = 0;
        bool untimed = this->infinite_timeout(timeout);

        this->outlln(__LOCATION__, "try {...", NULL);
        try {
            if (untimed) {
                this->outlln(__LOCATION__, "::xos::wait wait(waited)...", NULL);
                ::xos::wait wait(waited);
                this->outlln(__LOCATION__, "...::xos::wait wait(waited)", NULL);
            } else {
                if (timeout) {
                    this->outlln(__LOCATION__, "::xos::wait wait(waited, timeout = ", unsigned_to_string(timeout).chars(), ")...", NULL);
                    ::xos::wait wait(waited, timeout);
                    this->outlln(__LOCATION__, "...::xos::wait wait(waited, timeout = ", unsigned_to_string(timeout).chars(), ")", NULL);
                } else {
                    this->outlln(__LOCATION__, "::xos::try_wait try_wait(waited)...", NULL);
                    ::xos::try_wait try_wait(waited);
                    this->outlln(__LOCATION__, "...::xos::try_wait try_wait(waited)", NULL);
                }
            }
            this->outlln(__LOCATION__, "...} try", NULL);
        } catch (const wait_exception& e) {
            this->outlln(__LOCATION__, "...catch (const wait_exception& e.status = \"", e.status_to_chars(), "\")", NULL);
            err = 1;
        } catch (const exception& e) {
            this->outlln(__LOCATION__, "...catch (const exception& e.status = \"", e.status_to_chars(), "\")", NULL);
            err = 1;
        } catch (...) {
            this->outlln(__LOCATION__, "...catch (...)", NULL);
            err = 1;
        }
        return err;
    }
    template <class TCondition, class TMutex>
    int run() {
        int err = 0;
        mseconds_t sleep = 0, timeout = 0;
        bool unslept = this->infinite_sleep(timeout),
             untimed = this->infinite_timeout(timeout);

        this->outlln(__LOCATION__, "try {...", NULL);
        try {
            bool signaled = false;
            this->outlln(__LOCATION__, "TMutex mutex...", NULL);
            TMutex mutex;
            this->outlln(__LOCATION__, "TCondition condition(mutex, signaled)...", NULL);
            TCondition condition(mutex, signaled);
            if (untimed) {
                if (unslept) {
                    this->outlln(__LOCATION__, "::xos::signal signal(condition)...", NULL);
                    ::xos::signal signal(condition);
                    this->outlln(__LOCATION__, "...::xos::signal signal(condition)", NULL);
                }
            }
            if ((err = run(condition))) {
                if (!untimed) {
                    this->outlln(__LOCATION__, "::xos::signal signal(condition)...", NULL);
                    ::xos::signal signal(condition);
                    this->outlln(__LOCATION__, "...::xos::signal signal(condition)", NULL);
                    err = run(condition);
                }
            }
            this->outlln(__LOCATION__, "...} try", NULL);
        } catch (const exception& e) {
            this->outlln(__LOCATION__, "...catch (const exception& e.status = \"", e.status_to_chars(), "\")", NULL);
            err = 1;
        } catch (...) {
            this->outlln(__LOCATION__, "...catch (...)", NULL);
            err = 1;
        }
        return err;
    }

    /// ...run
    /*/
    virtual int windows_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::microsoft::windows::condition, ::xos::mt::microsoft::windows::mutex >();
    }
    virtual int solaris_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::oracle::solaris::condition, ::xos::mt::oracle::solaris::mutex >();
    }
    virtual int mach_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::mach::condition, ::xos::mt::mach::mutex >();
    }
    /*/
    virtual int osx_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::apple::osx::condition, ::xos::mt::apple::osx::mutex >();
    }
    virtual int linux_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::linux::condition, ::xos::mt::linux::mutex >();
    }
    virtual int posix_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::posix::condition, ::xos::mt::posix::mutex >();
    }
    virtual int os_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::os::condition, ::xos::mt::os::mutex  >();
    }
    virtual int derived_run(int argc, char_t** argv, char_t** env) {
        return this->run< ::xos::mt::derived::condition, ::xos::mt::derived::mutex >();
    }
    virtual int default_run(int argc, char_t** argv, char_t** env) {
        return this->usage(argc, argv, env);
    }
}; /// class maint
typedef maint<> main;

} /// namespace condition
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// ndef XOS_APP_CONSOLE_CONDITION_MAIN_HPP 
