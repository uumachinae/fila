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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/15/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_MT_THREAD_MAIN_HPP
#define XOS_APP_CONSOLE_MT_THREAD_MAIN_HPP

#include "xos/app/console/mt/thread/main_opt.hpp"
#include "xos/app/console/mt/thread/array.hpp"
#include "xos/mt/thread.hpp"

namespace xos {
namespace app {
namespace console {
namespace mt {
namespace thread {

/// class maint
template 
<class TRan = ran, 
 class TExtends = xos::app::console::mt::thread::main_opt, 
 class TImplements = typename TExtends::implements>

class exported maint: virtual public TRan, virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef maint derives;

    typedef typename extends::char_t char_t;
    typedef typename extends::end_char_t end_char_t;
    enum { end_char = extends::end_char };
    typedef typename extends::string_t string_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;
    typedef typename extends::file_t file_t;

    /// constructor / destructor
    maint(): locked_(0) {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename extends::in_reader_t in_reader_t;
    typedef typename extends::out_writer_t out_writer_t;
    typedef typename extends::err_writer_t err_writer_t;

    /// run
    virtual pointer_t run(pointer_t parameter) {
        pointer_t result = 0;
        mseconds_t mseconds = 0;
        bool untimed = this->infinite_sleep(mseconds);
        this->outlln(__LOCATION__, "...parameter = ", pointer_to_string(result).chars(), "...", NULL);
        if (!untimed) {
            useconds_t useconds = mseconds_useconds(mseconds);
            this->outlln(__LOCATION__, "usleep(useconds = ", unsigned_to_string(useconds).chars(), ")...", NULL);
            usleep(useconds);
            this->outlln(__LOCATION__, "...usleep(useconds)", unsigned_to_string(useconds).chars(), NULL);
        }
        return result;
    }

    /// run
    int run(::xos::joined& joined) {
        int err = 0;
        mseconds_t timeout = 0;
        bool untimed = this->infinite_timeout(timeout);
        this->outlln(__LOCATION__, "try {...", NULL);
        for (unsigned tried = 0, tries = 1; tries; --tries, ++tried) {
            try {
                if (untimed) {
                    this->outlln(__LOCATION__, "::xos::join join(joined)...", NULL);
                    ::xos::join join(joined);
                    this->outlln(__LOCATION__, "...::xos::join join(joined)", NULL);
                } else {
                    if (0 < timeout) {
                        this->outlln(__LOCATION__, "::xos::join join(joined, timeout = ", unsigned_to_string(timeout).chars(), ")...", NULL);
                        ::xos::join join(joined, timeout);
                        this->outlln(__LOCATION__, "...::xos::join join(joined, timeout = ", unsigned_to_string(timeout).chars(), ")", NULL);
                    } else {
                        this->outlln(__LOCATION__, "::xos::try_join try_join(joined)...", NULL);
                        ::xos::try_join try_join(joined);
                        this->outlln(__LOCATION__, "...::xos::try_join try_join(joined)", NULL);
                    }
                }
                this->outlln(__LOCATION__, "...} try", NULL);
            } catch (const join_exception& e) {
                join_status status = e.status();
                this->outlln(__LOCATION__, "...catch (const join_exception& e.status = \"", join_status_to_chars(status), "\")", NULL);
                if (!((untimed) || (tried) || ((join_busy != status) && (join_timeout != status)))) {
                    ++tries;
                    untimed = true;
                    continue;
                }
                err = 1;
            } catch (const exception& e) {
                this->outlln(__LOCATION__, "...catch (const exception& e.status = \"", e.status_to_chars(), "\")", NULL);
                err = 1;
            } catch (...) {
                this->outlln(__LOCATION__, "...catch (...)", NULL);
                err = 1;
            }
        }
        return err;
    }
    
    /// run
    template <class TMutex, class TThread>
    int run() {
        int err = 0;
        mseconds_t timeout = 0;
        size_t nthreads = this->threads();
        bool untimed = this->infinite_timeout(timeout);
        if ((1 < nthreads)) {
            this->outlln(__LOCATION__, "try {...", NULL);
            try {
                this->outlln(__LOCATION__, "TMutex mutex...", NULL);
                TMutex mutex;
                locked_ = &mutex;
                this->outlln(__LOCATION__, "TThread thread...", NULL);
                thread::arrayt<TThread> threads(nthreads, *this);
                err = run(threads);
                this->outlln(__LOCATION__, "...} try", NULL);
            } catch (const exception& e) {
                this->outlln(__LOCATION__, "...catch (const exception& e.status = \"", e.status_to_chars(), "\")", NULL);
                err = 1;
            } catch (...) {
                this->outlln(__LOCATION__, "...catch (...)", NULL);
                err = 1;
            }
        } else {
            this->outlln(__LOCATION__, "try {...", NULL);
            try {
                this->outlln(__LOCATION__, "TMutex mutex...", NULL);
                TMutex mutex;
                locked_ = &mutex;
                this->outlln(__LOCATION__, "TThread thread...", NULL);
                TThread thread(*this);
                err = run(thread);
                this->outlln(__LOCATION__, "...} try", NULL);
            } catch (const exception& e) {
                this->outlln(__LOCATION__, "...catch (const exception& e.status = \"", e.status_to_chars(), "\")", NULL);
                err = 1;
            } catch (...) {
                this->outlln(__LOCATION__, "...catch (...)", NULL);
                err = 1;
            }
        }
        locked_ = 0;
        return err;
    }

    /// out...
    virtual ssize_t outllnv(const char_t *what, va_list va) {
        ssize_t count = 0;
        try {
            xos::lock lock(*this);
            count = extends::outllnv(what, va);
        } catch (...) {
            count = -1;
        }
        return count;
    }
    
    /// lock / unlock
    virtual bool lock() {
        if ((locked_)) {
            return locked_->lock();
        }
        return true;
    }
    virtual bool unlock() {
        if ((locked_)) {
            return locked_->unlock();
        }
        return true;
    }

protected:
    xos::locked* locked_;
}; /// class maint
typedef maint<> main;

} /// namespace thread
} /// namespace mt
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// ndef XOS_APP_CONSOLE_MT_THREAD_MAIN_HPP
