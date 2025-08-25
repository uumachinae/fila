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
///   File: thread.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_NADIR_MT_POSIX_THREAD_HPP
#define _FILA_NADIR_MT_POSIX_THREAD_HPP

#include "fila/nadir/mt/thread.hpp"
#include "crono/nadir/io/logger.hpp"

#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(PTHREAD_HAS_TRYJOIN)
#define PTHREAD_HAS_TRYJOIN
#endif // !defined(PTHREAD_HAS_TRYJOIN)
#if !defined(PTHREAD_HAS_TIMEDJOIN)
#define PTHREAD_HAS_TIMEDJOIN
#endif // !defined(PTHREAD_HAS_TIMEDJOIN)
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace fila {
namespace mt {
namespace posix {

#if !defined(CLOCK_REALTIME)
#define CLOCK_REALTIME 0
#define clockid_t int
inline int clock_gettime(clockid_t clk_id, struct timespec *tp) {
    CRONO_LOG_ERROR("...failed function unavailable on this platform");
    return EINVAL;
}
#endif // !defined(CLOCK_REALTIME)

#if !defined(PTHREAD_HAS_TRYJOIN)
inline int pthread_tryjoin_np(pthread_t thread, void **retval) {
    CRONO_LOG_ERROR("...failed function unavailable on this platform");
    return EINVAL;
}
#endif // !defined(PTHREAD_HAS_TRYJOIN)

#if !defined(PTHREAD_HAS_TIMEDJOIN)
inline int pthread_timedjoin_np
(pthread_t thread, void **retval, const struct timespec *abstime) {
    CRONO_LOG_ERROR("...failed function unavailable on this platform");
    return EINVAL;
}
#endif // !defined(PTHREAD_HAS_TIMEDJOIN)

typedef pthread_attr_t threadattr_t;
typedef pthread_t thread_t;
typedef thread_t* thread_attached_t;

typedef mt::thread thread_creator;
typedef nadir::attachert<thread_attached_t, int, 0, thread_creator> thread_attacher;
typedef nadir::attachedt<thread_attached_t, int, 0, thread_attacher, base> thread_attached;
typedef nadir::createdt<thread_attached_t, int, 0, thread_attacher, thread_attached> thread_created;
typedef thread_attacher threadt_implements;
typedef thread_created threadt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: threadt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = threadt_implements, class TExtends = threadt_extends>

class _EXPORT_CLASS threadt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    threadt(ran& _ran): m_ran(_ran), m_forked(false) {
        if (!(this->create())) {
            create_exception e(create_failed);
            CRONO_LOG_ERROR("...throwing create_exception e(create_failed)...");
            throw (e);
        }
    }
    threadt(): m_ran(*this), m_forked(false) {
        if (!(this->create())) {
            CRONO_LOG_ERROR("...throwing create_exception e(create_failed)...");
            create_exception e(create_failed);
            throw (e);
        }
    }
    virtual ~threadt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            CRONO_LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(bool initiallySuspended) {
        if (!(initiallySuspended)) {
            return this->create();
        }
        return false;
    }
    virtual bool create() {
        pthread_t* detached = 0;
        if ((detached = create_attached())) {
            this->set_is_created();
            return m_forked = true;
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->joined())) {
            this->detach();
            return true;
        }
        return false;
    }
    virtual bool joined() {
        if ((m_forked)) {
            return join();
        }
        return true;
    }
    virtual bool join() {
        pthread_t* thread = 0;
        m_forked = false;
        if ((thread = this->attached_to())) {
            if ((join_detached(thread))) {
                return true;
            }
        }
        return false;
    }
    virtual join_status try_join() {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            join_status status = join_failed;
            if (join_success == (status = try_join_detached(thread))) {
                m_forked = false;
            }
            return status;
        }
        return join_failed;
    }
    virtual join_status timed_join(mseconds_t milliseconds) {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            join_status status = join_failed;
            if (join_success == (status = timed_join_detached(thread, milliseconds))) {
                m_forked = false;
            }
            return status;
        }
        return join_failed;
    }
    virtual join_status untimed_join() {
        pthread_t* thread = 0;
        if ((thread = this->attached_to())) {
            join_status status = untimed_join_detached(thread);
            m_forked = false;
            return status;
        }
        return join_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* create_attached() {
        pthread_t* detached = 0;
        if ((this->destroyed())) {
            if ((detached = create_detached(m_threadattr, m_thread))) {
                this->attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual pthread_t* create_detached
    (pthread_attr_t& threadattr, pthread_t& thread) const {
        int err = 0;

        CRONO_LOG_DEBUG("pthread_attr_init(&threadattr)...");
        if (!(err = pthread_attr_init(&threadattr))) {

            CRONO_LOG_DEBUG("pthread_create(&thread, &threadattr, StartRoutine, ((void*)this))...");
            if (!(err = pthread_create(&thread, &threadattr, start_routine, ((void*)this)))) {

                CRONO_LOG_DEBUG("pthread_attr_destroy(&threadattr)...");
                if ((err = pthread_attr_destroy(&threadattr))) {
                    CRONO_LOG_ERROR("...failed err = " << err << " on pthread_attr_destroy(&threadattr)");
                    join_detached(&thread);
                    return 0;
                }
                return &thread;
            } else {
                CRONO_LOG_ERROR("...failed err = " << err << " on pthread_create(&thread, &threadattr, StartRoutine, ((void*)this))");
            }
            CRONO_LOG_DEBUG("pthread_attr_destroy(&threadattr)...");
            if ((err = pthread_attr_destroy(&threadattr))) {
                CRONO_LOG_ERROR("...failed err = " << err << " on pthread_attr_destroy(&threadattr)");
            }
        } else {
            CRONO_LOG_ERROR("...failed err = " << err << " on pthread_attr_init(&threadattr)");
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool join_detached(pthread_t* thread) const {
        if (join_success == (untimed_join_detached(thread))) {
            return true;
        }
        return false;
    }
    virtual join_status untimed_join_detached(pthread_t* thread) const {
        if ((thread)) {
            void* value = 0;
            int err = 0;
            CRONO_LOG_DEBUG("pthread_join(*thread, &value)...");
            if (!(err = pthread_join(*thread, &value))) {
                CRONO_LOG_DEBUG("...pthread_join(*thread, &value)");
                return join_success;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_ERROR("...ETIMEDOUT err = " << err << " on pthread_join(*thread, &value)");
                    return join_busy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = " << err << " on pthread_join(*thread, &value)");
                    return join_interrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = " << err << " on pthread_join(*thread, &value)");
                }
            }
        }
        return join_failed;
    }
    virtual join_status try_join_detached(pthread_t* thread) const {
        if ((thread)) {
            void* value = 0;
            int err = 0;
            CRONO_LOG_TRACE("pthread_tryjoin_np(*thread, &value)...");
            if (!(err =  pthread_tryjoin_np(*thread, &value))) {
                return join_success;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                    return join_busy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                    return join_interrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                    return join_failed;
                }
            }
        }
        return join_failed;
    }
    virtual join_status timed_join_detached(pthread_t* thread, mseconds_t milliseconds) const {
        if ((thread)) {
            void* value = 0;
            int err = 0;
            struct timespec untilTime;

            if (!(err = clock_gettime(CLOCK_REALTIME, &untilTime))) {
                untilTime.tv_sec +=  mseconds_seconds(milliseconds);
                untilTime.tv_nsec +=  mseconds_nseconds(milliseconds);

                CRONO_LOG_TRACE("pthread_timedjoin_np(*thread, &value, &untilTime)...");
                if (!(err =  pthread_timedjoin_np(*thread, &value, &untilTime))) {
                    return join_success;
                } else {
                    switch(err) {
                    case ETIMEDOUT:
                        CRONO_LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                        return join_busy;
                    case EINTR:
                        CRONO_LOG_ERROR("...EINTR err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                        return join_interrupted;
                    default:
                        CRONO_LOG_ERROR("...failed err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                        return join_failed;
                    }
                }
            }
        }
        return join_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* detach() {
        m_forked = false;
        return Extends::detach();
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void run() {
        CRONO_LOG_DEBUG("...");
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void* start_routine(void* param) {
        void* result = 0;
        threadt* t = 0;
        CRONO_LOG_DEBUG("in...");
        if ((t = ((threadt*)param))) {
            CRONO_LOG_DEBUG("t->m_ran.run()...");
            t->m_ran.run();
            CRONO_LOG_DEBUG("...t->m_ran.run()");
        } else {
            CRONO_LOG_ERROR("...unexpected 0 = ((threadt*)param)");
        }
        CRONO_LOG_DEBUG("...out");
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ran& m_ran;
    bool m_forked;
    pthread_t m_thread;
    pthread_attr_t m_threadattr;
};
typedef threadt<> thread;

} // namespace posix 
} // namespace mt 
} // namespace fila 

#endif // _FILA_NADIR_MT_POSIX_THREAD_HPP 
