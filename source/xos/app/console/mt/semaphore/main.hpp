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
///   Date: 12/15/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_MT_FILA_MAIN_HPP
#define XOS_APP_CONSOLE_MT_FILA_MAIN_HPP

#include "xos/app/console/mt/semaphore/main_opt.hpp"
#include "xos/mt/semaphore.hpp"

namespace xos {
namespace app {
namespace console {
namespace mt {
namespace semaphore {

/// class maint
template 
<class TExtends = xos::app::console::mt::semaphore::main_opt, 
 class TImplements = typename TExtends::implements>

class exported maint: virtual public TImplements, public TExtends {
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
    maint() {
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
    int run(::xos::acquired& acquired) {
        int err = 0;
        mseconds_t timeout = 0;
        bool untimed = this->infinite_timeout(timeout);

        for (unsigned tries = 1, tried = 0; tried < tries; ++tried) {

            this->outlln(__LOCATION__, "try {...", NULL);
            try {
                if ((untimed)) {
                    this->outlln(__LOCATION__, "acquire acquire(acquired)...", NULL);
                    acquire acquire(acquired);
                    this->outlln(__LOCATION__, "...acquire acquire(acquired)", NULL);
                } else {
                    if ((0 < timeout)) {
                        this->outlln(__LOCATION__, "timed_acquire acquire(acquired timeout = ", unsigned_to_string(timeout).chars(), ")...", NULL);
                        timed_acquire acquire(acquired, timeout);
                        this->outlln(__LOCATION__, "...timed_acquire acquire(acquired timeout = ", unsigned_to_string(timeout).chars(), ")", NULL);
                    } else {
                        this->outlln(__LOCATION__, "try_acquire acquire(acquired,)...", NULL);
                        try_acquire acquire(acquired);
                        this->outlln(__LOCATION__, "...try_acquire acquire(acquired)", NULL);
                    }
                }
                err = 0;
                this->outlln(__LOCATION__, "...} try", NULL);
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
    template <class TSemaphore>
    int run() {
        int err = 0;
        mseconds_t timeout = 0;
        bool untimed = this->infinite_timeout(timeout);

        this->outlln(__LOCATION__, "try {...", NULL);
        try {
            TSemaphore acquired;

            if ((untimed)) {
                ::xos::release release(acquired);
                run(acquired);
            } else {
                run(acquired);
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

protected:
}; /// class maint
typedef maint<> main;

} /// namespace semaphore
} /// namespace mt
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// ndef XOS_APP_CONSOLE_MT_FILA_MAIN_HPP
