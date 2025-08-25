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
///   File: Process.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_MT_POSIX_PROCESS_HPP
#define _FILA_MT_POSIX_PROCESS_HPP

#include "fila/mt/Process.hpp"
#include "crono/io/Logger.hpp"
#include "thirdparty/gnu/glibc/posix/execvpe.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

namespace fila {
namespace mt {
namespace posix {

typedef pid_t ProcessTAttachedT;
typedef mt::ProcessTImplements ProcessTAttacherImplements;
typedef ::patrona::AttacherT<ProcessTAttachedT, int, -1, ProcessTAttacherImplements> ProcessTAttacher;
typedef ::patrona::AttachedT<ProcessTAttachedT, int, -1, ProcessTAttacher> ProcessTAttached;
typedef ::patrona::CreatedT<ProcessTAttachedT, int, -1, ProcessTAttacher, ProcessTAttached> ProcessTCreated;
typedef ProcessTAttacherImplements ProcessTImplements;
typedef ProcessTCreated ProcessTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ProcessT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ProcessTImplements, class TExtends = ProcessTExtends>

class _EXPORT_CLASS ProcessT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ProcessT(): m_isForked(false) {
    }
    virtual ~ProcessT() {
        if (!(this->Destroyed())) {
            CreateException e(DestroyFailed);
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const char* path, char** argv, char** env,
     int* fdup, int** pdup, bool isDetached = false) {
        pid_t detached = -1;

        if (0 <= (detached = this->CreateAttached
            (path, argv, env, fdup, pdup, isDetached))) {
            this->SetIsCreated();
            return m_isForked = true;
        }
        return false;
    }
    virtual bool Destroy() {
        if ((this->Joined())) {
            this->Detach();
            return true;
        }
        this->Detach();
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pid_t CreateAttached
    (const char* path, char** argv, char** env,
     int* fdup, int** pdup, bool isDetached = false) {
        pid_t detached = -1;

        if ((this->Destroyed())) {

            if (0 <= (detached = CreateDetached
                (path, argv, env, fdup, pdup, isDetached))) {
                this->Attach(detached);
                return detached;
            }
        }
        return -1;
    }
    virtual pid_t CreateDetached
    (const char* path, char** argv, char** env,
     int* fdup, int** pdup, bool isDetached = false) const {
        pid_t pid = (pid_t)(-1);

        CRONO_LOG_DEBUG("::fork()...");
        if (0 < (pid = ::fork())) {
            CRONO_LOG_DEBUG("...pid = " << pid << " on ::fork()");
        } else {
            if (0 > (pid)) {
                CRONO_LOG_ERROR("...failed errno = " << errno << " on ::fork()");
            } else {
                int err = 1;

                CRONO_LOG_DEBUG("chlid process...");
                this->ExecDetached(path, argv, env, fdup, pdup, isDetached);
                CRONO_LOG_DEBUG("...chlid process exit(err = " << err << ")...");
                exit(err);
            }
        }
        return pid;
    }
    virtual bool ExecDetached
    (const char* path, char** argv, char** env,
     int* fdup, int** pdup, bool isDetached = false) const {
        if ((path) && (argv)) {
            int err = 0;

            if ((fdup)) {
                int fd = 0;
                for (int i = 0; (i < 3) && (fd = fdup[i]); ++i) {
                    CRONO_LOG_DEBUG("dup2(" << fd << ", " << i << ")...");
                    if (0 > (err = dup2(fd, i))) {
                        CRONO_LOG_ERROR("failed " << errno << " on dup2(" << fd << ", " << i << ")");
                        return false;
                    } else {
                        CRONO_LOG_DEBUG("close(fd = " << fd << ")...");
                        close(fd);
                    }
                }
            }

            if ((pdup)) {
                int* p = 0;
                for (int i = 0; (i < 3) && (p = pdup[i]); ++i) {
                    int fd = p[(i)?(1):(0)];
                    CRONO_LOG_DEBUG("dup2(" << fd << ", " << i << ")...");
                    if (0 > (err = dup2(fd, i))) {
                        CRONO_LOG_ERROR("failed " << errno << " on dup2(" << fd << ", " << i << ")");
                        return false;
                    } else {
                        CRONO_LOG_DEBUG("close(p[0] = " << p[0] << ")...");
                        close(p[0]);
                        CRONO_LOG_DEBUG("close(p[1] = " << p[1] << ")...");
                        close(p[1]);
                    }
                }
            }

            if ((env)) {
                CRONO_LOG_DEBUG("execvpe(\"" << path << "\", ...)...");
                if ((err = execvpe(path, argv, env))) {
                    CRONO_LOG_ERROR("...failed " << errno << " on execvpe(\"" << path << "\",...)");
                }
            } else {
                CRONO_LOG_DEBUG("execvp(\"" << path << "\", ...)...");
                if ((err = execvp(path, argv))) {
                    CRONO_LOG_ERROR("...failed " << errno << " on execvp(\"" << path << "\",...)");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((m_isForked)) {
            return Join();
        }
        return true;
    }
    virtual bool Join() {
        pid_t pid = -1;
        m_isForked = false;
        if (0 <= (pid = this->AttachedTo())) {
            if ((JoinDetached(pid))) {
                return true;
            }
        }
        return false;
    }
    virtual JoinStatus TryJoin() {
        pid_t pid = -1;
        if (0 <= (pid = this->AttachedTo())) {
            JoinStatus status = TryJoinDetached(pid);
            if (status != (JoinBusy)) {
                m_isForked = false;
            }
            return status;
        }
        return JoinFailed;
    }
    virtual JoinStatus TimedJoin(mseconds_t milliseconds) {
        pid_t pid = -1;
        if (0 <= (pid = this->AttachedTo())) {
            JoinStatus status = TimedJoinDetached(pid, milliseconds);
            if (status != (JoinBusy)) {
                m_isForked = false;
            }
            return status;
        }
        return JoinFailed;
    }
    virtual JoinStatus UntimedJoin() {
        pid_t pid = -1;
        m_isForked = false;
        if (0 <= (pid = this->AttachedTo())) {
            return UntimedJoinDetached(pid);
        }
        return JoinFailed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool JoinDetached(pid_t pid) const {
        if (JoinSuccess == (UntimedJoinDetached(pid))) {
            return true;
        }
        return false;
    }
    virtual JoinStatus UntimedJoinDetached(pid_t pid) const {
        if (0 <= (pid)) {
            int status = 0, options = 0;

            CRONO_LOG_DEBUG("waitpid(" << pid << ",...)...");
            if (!(pid != waitpid(pid, &status, options))) {
                CRONO_LOG_DEBUG("...waitpid(" << pid << ",...)");
                return JoinSuccess;
            } else {
                CRONO_LOG_ERROR("...failed errno = " << errno << " on waitpid(" << pid << ",...)");
            }
        }
        return JoinFailed;
    }
    virtual JoinStatus TryJoinDetached(pid_t pid) const {
        if (0 <= (pid)) {
            int status = 0, options = WNOHANG;

            CRONO_LOG_DEBUG("waitpid(" << pid << ",...)...");
            if (!(pid != waitpid(pid, &status, options))) {
                CRONO_LOG_DEBUG("...waitpid(" << pid << ",...)");
                return JoinSuccess;
            } else {
                if (EBUSY != (errno)) {
                    CRONO_LOG_ERROR("...failed errno = " << errno << " on waitpid(" << pid << ",...)");
                } else {
                    CRONO_LOG_ERROR("...busy errno = " << errno << " on waitpid(" << pid << ",...)");
                    return JoinBusy;
                }
            }
        }
        return JoinFailed;
    }
    virtual JoinStatus TimedJoinDetached(pid_t pid, mseconds_t milliseconds) const {
        if (0 > (milliseconds)) {
            return UntimedJoinDetached(pid);
        } else {
            if (0 < (milliseconds)) {
                CRONO_LOG_ERROR("...failed timed_waitpid(..., " << milliseconds << ") unavailable");
            } else {
                return TryJoinDetached(pid);
            }
        }
        return JoinInvalid;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool to = true) {
        m_isForked = to;
        return m_isForked;
    }
    virtual bool IsForked() const {
        return m_isForked;
    }
    virtual bool SetIsJoined(bool to = true) {
        m_isForked = !to;
        return !m_isForked;
    }
    virtual bool IsJoined() const {
        return !m_isForked;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isForked;
};
typedef ProcessT<> Process;

} // namespace posix 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_POSIX_PROCESS_HPP 
