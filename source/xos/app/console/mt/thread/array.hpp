//////////////////////////////////////////////////////////////////////////
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
///   File: array.hpp
///
/// Author: $author$
///   Date: 12/16/2022
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_APP_CONSOLE_MT_THREAD_ARRAY_HPP
#define XOS_APP_CONSOLE_MT_THREAD_ARRAY_HPP

#include "xos/mt/thread.hpp"

namespace xos {
namespace app {
namespace console {
namespace mt {
namespace thread {

/// class arrayt
template 
<class TThread = xos::mt::thread, class TRan = xos::ran, 
 class TJoined = xos::joined, class TExtends = extend, class TImplements = TJoined>
class exported arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef arrayt derives;

    typedef TThread thread_t;
    typedef TRan ran_t;
    typedef TJoined joined_t;
    typedef uint8_t size_t;
    
    /// enum join_status
    typedef typename joined_t::join_status join_status;
    enum {
        join_success = joined_t::join_success,
        join_failed = joined_t::join_failed,
        join_busy = joined_t::join_busy,
        join_timeout = joined_t::join_timeout,
        join_interrupted = joined_t::join_interrupted
    }; /// enum join_status

    /// constructor / destructor
    arrayt(size_t n, ran_t &r): t_(0), n_(0), is_logged_(true) {
        construct(n, &r);
    }
    arrayt(size_t n): t_(0), n_(0), is_logged_(true) {
        construct(n);
    }
    virtual ~arrayt() {
        destruct();
    }
private:
    arrayt(const arrayt &copy): extends(copy) {
        throw exception(exception_unexpected);
    }

    /// construct / destruct
    void construct(size_t n, ran_t *r = 0) {
        if ((n)) {
            LOGGER_IS_LOGGED_INFO("(t_ = new thread_t*[n_ = " << n << "])...");
            if ((t_ = new thread_t*[n_ = n])) {
                LOGGER_IS_LOGGED_INFO("...(t_ = new thread_t*[n_ = " << n << "])");
                for (n = 0; n < n_; ++n) {
                    LOGGER_IS_LOGGED_INFO("try {...");
                    try {
                        LOGGER_IS_LOGGED_INFO("t_[" << n << "] = (r)?(new thread_t(*r)):(new thread_t())...");
                        t_[n] = (r)?(new thread_t(*r)):(new thread_t());
                        LOGGER_IS_LOGGED_INFO("...t_[" << n << "] = (r)?(new thread_t(*r)):(new thread_t())");
                        LOGGER_IS_LOGGED_INFO("...} try");
                    } catch (...) {
                        LOGGER_IS_LOGGED_INFO("...catch (...)");
                        break;
                    }
                }
            }
        }
    }
    void destruct() {
        joined();
        if ((t_) && (n_)) {
            for (thread_t* t = 0; n_; --n_) {
                LOGGER_IS_LOGGED_INFO("(t = t_[" << n_-1 << "])...");
                if ((t = t_[n_-1])) {
                    LOGGER_IS_LOGGED_INFO("...(t = t_[" << n_-1 << "])");
                    LOGGER_IS_LOGGED_INFO("try {...");
                    try {
                        LOGGER_IS_LOGGED_INFO("delete t ([" << n_-1 << "])...");
                        delete t;
                        LOGGER_IS_LOGGED_INFO("...delete t ([" << n_-1 << "])");
                        LOGGER_IS_LOGGED_INFO("...} try");
                    } catch (...) {
                        LOGGER_IS_LOGGED_INFO("...catch (...)");
                    }
                }
            }
            LOGGER_IS_LOGGED_INFO("try {...");
            try {
                LOGGER_IS_LOGGED_INFO("delete t_...");
                delete t_;
                LOGGER_IS_LOGGED_INFO("...delete t_");
                LOGGER_IS_LOGGED_INFO("...} try");
            } catch (...) {
                LOGGER_IS_LOGGED_INFO("...catch (...)");
            }
        }
    }
public:

    /// join...
    virtual bool joined() {
        if ((t_) && (n_)) {
            bool success = true;
            thread_t* t = 0; size_t n = 0;
            for (n = n_; n; --n) {
                if ((t = t_[n-1])) {
                    if (!(t->joined())) {
                        success = false;
                    }
                } else {
                    success = false;
                }
            }
            return success;
        }
        return false;   
    }
    virtual bool join() {
        return (join_success == untimed_join());
    }
    virtual join_status time_join(mseconds_t milliseconds) {
        if ((t_) && (n_)) {
            join_status status = join_success;
            thread_t* t = 0; size_t n = 0;
            for (n = n_; n; --n) {
                if ((t = t_[n-1])) {
                    if (!(join_success == t->time_join(milliseconds))) {
                        status = join_failed;
                    }
                } else {
                    status = join_failed;
                }
            }
            return status;
        }
        return join_failed;
    }
    virtual join_status timed_join(mseconds_t milliseconds) {
        if ((t_) && (n_)) {
            join_status status = join_success;
            thread_t* t = 0; size_t n = 0;
            for (n = n_; n; --n) {
                if ((t = t_[n-1])) {
                    if (!(join_success == t->timed_join(milliseconds))) {
                        status = join_failed;
                    }
                } else {
                    status = join_failed;
                }
            }
            return status;
        }
        return join_failed;
    }
    virtual join_status untimed_join() {
        if ((t_) && (n_)) {
            join_status status = join_success;
            thread_t* t = 0; size_t n = 0;
            for (n = n_; n; --n) {
                if ((t = t_[n-1])) {
                    if (!(join_success == t->untimed_join())) {
                        status = join_failed;
                    }
                } else {
                    status = join_failed;
                }
            }
            return status;
        }
        return join_failed;
    }
    virtual join_status try_join() {
        if ((t_) && (n_)) {
            join_status status = join_success;
            thread_t* t = 0; size_t n = 0;
            for (n = n_; n; --n) {
                if ((t = t_[n-1])) {
                    if (!(join_success == t->try_join())) {
                        status = join_failed;
                    }
                } else {
                    status = join_failed;
                }
            }
            return status;
        }
        return join_failed;
    }

    ///...logged
    virtual bool& set_is_logged(bool to = true) {
        bool& is_logged = this->is_logged();
        is_logged = to;
        return is_logged;
    }
    virtual bool& is_logged() const {
        return (bool&)is_logged_;
    }
    
protected:
    thread_t** t_;
    size_t n_;
    bool is_logged_;
}; /// class arrayt
typedef arrayt<> array;

} /// namespace thread 
} /// namespace mt 
} /// namespace console 
} /// namespace app 
} /// namespace xos 

#endif /// ndef XOS_APP_CONSOLE_MT_THREAD_ARRAY_HPP
