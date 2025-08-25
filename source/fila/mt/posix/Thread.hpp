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
///   File: Thread.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_MT_POSIX_THREAD_HPP
#define _FILA_MT_POSIX_THREAD_HPP

#include "fila/mt/Thread.hpp"
#include "crono/io/Logger.hpp"

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

typedef pthread_t* ThreadTAttachedT;
typedef ::patrona::CreatorT<mt::Thread> ThreadTAttacherImplements;
typedef ::patrona::AttacherT<ThreadTAttachedT, int, 0, ThreadTAttacherImplements> ThreadTAttacher;
typedef ::patrona::AttachedT<ThreadTAttachedT, int, 0, ThreadTAttacher> ThreadTAttached;
typedef ::patrona::CreatedT<ThreadTAttachedT, int, 0, ThreadTAttacher, ThreadTAttached> ThreadTCreated;
typedef ThreadTAttacherImplements ThreadTImplements;
typedef ThreadTCreated ThreadTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ThreadT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ThreadTImplements, class TExtends = ThreadTExtends>

class _EXPORT_CLASS ThreadT: virtual public TImplements, public TExtends {
private:
    ThreadT(const ThreadT& copy) {
    }
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ThreadT(Ran& ran): m_ran(ran), m_forked(false) {
        if (!(this->Create())) {
            CreateException e(CreateFailed);
            throw (e);
        }
    }
    ThreadT(): m_ran(*this), m_forked(false) {
        if (!(this->Create())) {
            CreateException e(CreateFailed);
            throw (e);
        }
    }
    virtual ~ThreadT() {
        if (!(this->Destroyed())) {
            CreateException e(DestroyFailed);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(bool initiallySuspended) {
        if (!(initiallySuspended)) {
            return this->Create();
        }
        return false;
    }
    virtual bool Create() {
        pthread_t* detached = 0;
        if ((detached = CreateAttached())) {
            this->SetIsCreated();
            return m_forked = true;
        }
        return false;
    }
    virtual bool Destroy() {
        if ((Joined())) {
            this->Detach();
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* CreateAttached() {
        pthread_t* detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(m_threadattr, m_thread))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual pthread_t* CreateDetached
    (pthread_attr_t& threadattr, pthread_t& thread) const {
        int err = 0;

        CRONO_LOG_DEBUG("pthread_attr_init(&threadattr)...");
        if (!(err = pthread_attr_init(&threadattr))) {

            CRONO_LOG_DEBUG("pthread_create(&thread, &threadattr, StartRoutine, ((void*)this))...");
            if (!(err = pthread_create(&thread, &threadattr, StartRoutine, ((void*)this)))) {

                CRONO_LOG_DEBUG("pthread_attr_destroy(&threadattr)...");
                if ((err = pthread_attr_destroy(&threadattr))) {
                    JoinDetached(&thread);
                    return 0;
                }
                return &thread;
            }
            if ((err = pthread_attr_destroy(&threadattr))) {
            }
        }
        return 0;
    }
    virtual bool JoinDetached(pthread_t* thread) const {
        if (JoinSuccess == (UntimedJoinDetached(thread))) {
            return true;
        }
        return false;
    }
    virtual JoinStatus UntimedJoinDetached(pthread_t* thread) const {
        if ((thread)) {
            void* value = 0;
            int err = 0;
            CRONO_LOG_DEBUG("pthread_join(*thread, &value)...");
            if (!(err = pthread_join(*thread, &value))) {
                CRONO_LOG_DEBUG("...pthread_join(*thread, &value)");
                return JoinSuccess;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_ERROR("...ETIMEDOUT err = " << err << " on pthread_join(*thread, &value)");
                    return JoinBusy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = " << err << " on pthread_join(*thread, &value)");
                    return JoinInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = " << err << " on pthread_join(*thread, &value)");
                }
            }
        }
        return JoinFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((m_forked)) {
            return Join();
        }
        return true;
    }
    virtual bool Join() {
        pthread_t* thread = 0;
        m_forked = false;
        if ((thread = this->AttachedTo())) {
            if ((JoinDetached(thread))) {
                return true;
            }
        }
        return false;
    }
    virtual JoinStatus TryJoin() {
#if defined(PTHREAD_HAS_TRYJOIN)
        pthread_t* thread = 0;
        if ((thread = this->AttachedTo())) {
            void* value = 0;
            int err = 0;
            CRONO_LOG_TRACE("pthread_tryjoin_np(*thread, &value)...");
            if (!(err =  pthread_tryjoin_np(*thread, &value))) {
                m_forked = false;
                return JoinSuccess;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    CRONO_LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                    return JoinBusy;
                case EINTR:
                    CRONO_LOG_ERROR("...EINTR err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                    return JoinInterrupted;
                default:
                    CRONO_LOG_ERROR("...failed err = "<< err << " on pthread_tryjoin_np(*thread, &value)");
                    return JoinFailed;
                }
            }
        }
        return JoinFailed;
#else // defined(PTHREAD_HAS_TRYJOIN)
        CRONO_LOG_ERROR("...return JoinInvalid");
        return JoinInvalid;
#endif // defined(PTHREAD_HAS_TRYJOIN)
    }
    virtual JoinStatus TimedJoin(mseconds_t milliseconds) {
        if (0 < (milliseconds)) {
#if defined(PTHREAD_HAS_TIMEDJOIN)
            pthread_t* thread = 0;
            if ((thread = this->AttachedTo())) {
                void* value = 0;
                int err = 0;
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  mseconds_seconds(milliseconds);
                untilTime.tv_nsec +=  mseconds_nseconds(milliseconds);

                CRONO_LOG_TRACE("pthread_timedjoin_np(*thread, &value, &untilTime)...");
                if (!(err =  pthread_timedjoin_np(*thread, &value, &untilTime))) {
                    m_forked = false;
                    return JoinSuccess;
                } else {
                    switch(err) {
                    case ETIMEDOUT:
                        CRONO_LOG_TRACE("...ETIMEDOUT err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                        return JoinBusy;
                    case EINTR:
                        CRONO_LOG_ERROR("...EINTR err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                        return JoinInterrupted;
                    default:
                        CRONO_LOG_ERROR("...failed err = "<< err << " on pthread_timedjoin_np(*thread, &value, &untilTime)");
                        return JoinFailed;
                    }
                }
            }
#else // defined(PTHREAD_HAS_TIMEDJOIN)
            CRONO_LOG_ERROR("...return JoinInvalid");
            return JoinInvalid;
#endif // defined(PTHREAD_HAS_TIMEDJOIN)
        } else {
            if (0 > (milliseconds)) {
                return UntimedJoin();
            } else {
                return TryJoin();
            }
        }
        return JoinFailed;
    }
    virtual JoinStatus UntimedJoin() {
        pthread_t* thread = 0;
        m_forked = false;
        if ((thread = this->AttachedTo())) {
            return UntimedJoinDetached(thread);
        }
        return JoinFailed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* Detach() {
        m_forked = false;
        return Extends::Detach();
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Run() {
        CRONO_LOG_DEBUG("...");
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void* StartRoutine(void* param) {
        void* result = 0;
        ThreadT* t = 0;
        CRONO_LOG_DEBUG("in...");
        if ((t = ((ThreadT*)param))) {
            CRONO_LOG_DEBUG("t->m_ran.Run()...");
            t->m_ran.Run();
            CRONO_LOG_DEBUG("...t->m_ran.Run()");
        } else {
            CRONO_LOG_ERROR("...unexpected 0 = ((ThreadT*)param)");
        }
        CRONO_LOG_DEBUG("...out");
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Ran& m_ran;
    bool m_forked;
    pthread_t m_thread;
    pthread_attr_t m_threadattr;
};
typedef ThreadT<> Thread;

} // namespace posix 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_POSIX_THREAD_HPP 
