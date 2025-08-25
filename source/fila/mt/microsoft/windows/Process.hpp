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
#ifndef _FILA_MT_MICROSOFT_WINDOWS_PROCESS_HPP
#define _FILA_MT_MICROSOFT_WINDOWS_PROCESS_HPP

#include "fila/mt/Process.hpp"
#include "crono/io/Logger.hpp"

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct _STARTUPINFOA {
  DWORD  cb;
  LPSTR lpReserved;
  LPSTR lpDesktop;
  LPSTR lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct _STARTUPINFOW {
  DWORD  cb;
  LPWSTR lpReserved;
  LPWSTR lpDesktop;
  LPWSTR lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CREATE_BREAKAWAY_FROM_JOB = 0x01000000,
    CREATE_DEFAULT_ERROR_MODE = 0x04000000,
    CREATE_NEW_CONSOLE = 0x00000010,
    CREATE_NEW_PROCESS_GROUP = 0x00000200,
    CREATE_NO_WINDOW = 0x08000000,
    CREATE_PROTECTED_PROCESS = 0x00040000,
    CREATE_PRESERVE_CODE_AUTHZ_LEVEL = 0x02000000,
    CREATE_SEPARATE_WOW_VDM = 0x00000800,
    CREATE_SHARED_WOW_VDM = 0x00001000,
    CREATE_SUSPENDED = 0x00000004,
    CREATE_UNICODE_ENVIRONMENT = 0x00000400,
    DEBUG_ONLY_THIS_PROCESS = 0x00000002,
    DEBUG_PROCESS = 0x00000001,
    DETACHED_PROCESS = 0x00000008,
    EXTENDED_STARTUPINFO_PRESENT = 0x00080000,
    INHERIT_PARENT_AFFINITY = 0x00010000
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    STARTF_FORCEONFEEDBACK = 0x00000040,
    STARTF_FORCEOFFFEEDBACK = 0x00000080,
    STARTF_PREVENTPINNING = 0x00002000,
    STARTF_RUNFULLSCREEN = 0x00000020,
    STARTF_TITLEISAPPID = 0x00001000,
    STARTF_TITLEISLINKNAME = 0x00000800,
    STARTF_UNTRUSTEDSOURCE = 0x00008000,
    STARTF_USECOUNTCHARS = 0x00000008,
    STARTF_USEFILLATTRIBUTE = 0x00000010,
    STARTF_USEHOTKEY = 0x00000200,
    STARTF_USEPOSITION = 0x00000004,
    STARTF_USESHOWWINDOW = 0x00000001,
    STARTF_USESIZE = 0x00000002,
    STARTF_USESTDHANDLES = 0x00000100
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
BOOL WINAPI CreateProcessA(
  _In_opt_    LPCSTR                lpApplicationName,
  _Inout_opt_ LPSTR                 lpCommandLine,
  _In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_        BOOL                  bInheritHandles,
  _In_        DWORD                 dwCreationFlags,
  _In_opt_    LPVOID                lpEnvironment,
  _In_opt_    LPCSTR                lpCurrentDirectory,
  _In_        LPSTARTUPINFOA        lpStartupInfo,
  _Out_       LPPROCESS_INFORMATION lpProcessInformation
);
BOOL WINAPI CreateProcessW(
  _In_opt_    LPCWSTR               lpApplicationName,
  _Inout_opt_ LPWSTR                lpCommandLine,
  _In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_        BOOL                  bInheritHandles,
  _In_        DWORD                 dwCreationFlags,
  _In_opt_    LPVOID                lpEnvironment,
  _In_opt_    LPCWSTR               lpCurrentDirectory,
  _In_        LPSTARTUPINFOW        lpStartupInfo,
  _Out_       LPPROCESS_INFORMATION lpProcessInformation
);
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    WAIT_FAILED = -1,
    WAIT_OBJECT_0 = 0x00000000,
    WAIT_ABANDONED = 0x00000080,
    WAIT_TIMEOUT = 0x00000102
};
DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
);
BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
);
DWORD GetLastError();
#endif // !defined(WINDOWS)

namespace fila {
namespace mt {
namespace microsoft {
namespace windows {

typedef LPPROCESS_INFORMATION ProcessAttachedT;
typedef mt::ProcessTImplements ProcessTAttacherImplements;
typedef ::patrona::AttacherT<ProcessAttachedT, int, 0, ProcessTAttacherImplements> ProcessTAttacher;
typedef ::patrona::AttachedT<ProcessAttachedT, int, 0, ProcessTAttacher> ProcessTAttached;
typedef ::patrona::CreatedT<ProcessAttachedT, int, 0, ProcessTAttacher, ProcessTAttached> ProcessTCreated;
typedef ::patrona::ForkedT<ProcessTAttacherImplements, ProcessTCreated> ProcessTForked;
typedef ProcessTAttacherImplements ProcessTImplements;
typedef ProcessTForked ProcessTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ProcessT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = ProcessTImplements, class TExtends = ProcessTExtends>

class _EXPORT_CLASS ProcessT: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ProcessT() {
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
     HANDLE* fdup, HANDLE** pdup, bool isDetached = false) {
        LPPROCESS_INFORMATION detached = 0;
        if (0 != (detached = this->CreateAttached
            (path, argv, env, fdup, pdup, isDetached))) {
            this->SetIsCreated();
            this->SetIsForked();
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        if ((this->Joined())) {
            LPPROCESS_INFORMATION detached = 0;
            if ((detached = this->Detach())) {
                if ((DestroyDetached(*detached))) {
                    return true;
                }
            }
            return false;
        }
        this->Detach();
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual LPPROCESS_INFORMATION CreateAttached
    (const char* path, char** argv, char** env,
     HANDLE* fdup, HANDLE** pdup, bool isDetached = false) {
        LPPROCESS_INFORMATION detached = 0;
        if ((this->Destroyed())) {
            if (0 <= (detached = CreateDetached
                (m_processInformation, path, argv, env, fdup, pdup, isDetached))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual LPPROCESS_INFORMATION CreateDetached
    (PROCESS_INFORMATION& p,
     const char* path, char** argv, char** env,
     HANDLE* fdup, HANDLE** pdup, bool isDetached = false) const {
        if ((path)) {
            ApplicationNameA applicationName(path);
            CommandLineA commandLine(argv);
            EnvironmentA environment(env);
            StartupInfoA startupInfo(0);
            ProcessInformation processInformation(0);

            LPCSTR lpApplicationName = applicationName.has_chars();
            LPSTR lpCommandLine = commandLine.has_elements();
            LPSECURITY_ATTRIBUTES lpProcessAttributes = 0;
            LPSECURITY_ATTRIBUTES lpThreadAttributes = 0;
            BOOL bInheritHandles = FALSE;
            DWORD dwCreationFlags = ((isDetached)?(DETACHED_PROCESS):(0));
            LPVOID lpEnvironment = environment.has_elements();
            LPCSTR lpCurrentDirectory = 0;
            LPSTARTUPINFOA lpStartupInfo = &startupInfo.wrapped();
            LPPROCESS_INFORMATION lpProcessInformation = &processInformation.wrapped();

            if ((UseStdHandles(lpStartupInfo, fdup))) {
                bInheritHandles = TRUE;
            }
            if ((UseStdHandles(lpStartupInfo, pdup))) {
                bInheritHandles = TRUE;
            }

            CRONO_LOG_DEBUG
            ("CreateProcessA(lpApplicationName = \"" << lpApplicationName
             << "\", lpCommandLine = \"" << lpCommandLine << "\",...)...");
            if ((CreateProcessA
                (lpApplicationName, lpCommandLine,
                 lpProcessAttributes,lpThreadAttributes, bInheritHandles, dwCreationFlags,
                 lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))) {
                processInformation >> p;
                return &p;
            } else {
                CRONO_LOG_ERROR
                ("...failed GetLastError() = " << GetLastError()
                 << " on CreateProcessA(lpApplicationName = \"" << lpApplicationName
                 << "\", lpCommandLine = \"" << lpCommandLine << "\",...)");
            }
        }
        return 0;
    }
    virtual bool DestroyDetached(PROCESS_INFORMATION& p) const {
        HANDLE hProcess = 0, hThread = 0;
        bool success = true;

        if ((hThread = p.hThread)) {
            if (!(CloseHandle(hThread))) {
                success = false;
            }
        } else {
            success = false;
        }
        if ((hProcess = p.hProcess)) {
            if (!(CloseHandle(hProcess))) {
                success = false;
            }
        } else {
            success = false;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Join() {
        LPPROCESS_INFORMATION p = 0;
        if (0 != (p = this->AttachedTo())) {
            if ((JoinDetached(p))) {
                this->SetIsForked(false);
                return true;
            }
        }
        this->SetIsForked(false);
        return false;
    }
    virtual JoinStatus TryJoin() {
        LPPROCESS_INFORMATION p = 0;
        if (0 != (p = this->AttachedTo())) {
            JoinStatus status = TryJoinDetached(p);
            if (status != (JoinBusy)) {
                this->SetIsForked(false);
            }
            return status;
        }
        return JoinFailed;
    }
    virtual JoinStatus TimedJoin(mseconds_t milliseconds) {
        LPPROCESS_INFORMATION p = 0;
        if (0 != (p = this->AttachedTo())) {
            JoinStatus status = TimedJoinDetached(p, milliseconds);
            if (status != (JoinBusy)) {
                this->SetIsForked(false);
            }
            return status;
        }
        return JoinFailed;
    }
    virtual JoinStatus UntimedJoin() {
        LPPROCESS_INFORMATION p = 0;
        if (0 != (p = this->AttachedTo())) {
            this->SetIsForked(false);
            return UntimedJoinDetached(p);
        }
        this->SetIsForked(false);
        return JoinFailed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool JoinDetached(LPPROCESS_INFORMATION p) const {
        if (JoinSuccess == (UntimedJoinDetached(p))) {
            return true;
        }
        return false;
    }
    virtual JoinStatus UntimedJoinDetached(LPPROCESS_INFORMATION p) const {
        return TimedJoinDetached(p, -1);
    }
    virtual JoinStatus TryJoinDetached(LPPROCESS_INFORMATION p) const {
        return TimedJoinDetached(p, 0);
    }
    virtual JoinStatus TimedJoinDetached
    (LPPROCESS_INFORMATION p, mseconds_t milliseconds) const {
        HANDLE handle = 0;
        if ((0 != (p)) && (0 != (handle = p->hProcess))) {
            DWORD dwWaitMilliSeconds = (0<=milliseconds)?(milliseconds):(INFINITE),
                  dwResult = 0;

            if ((milliseconds >= 100) || (milliseconds == INFINITE)) {
                CRONO_LOG_DEBUG("WaitForSingleObject(..., dwWaitMilliSeconds = " << dwWaitMilliSeconds << ")");
            }
            dwResult = WaitForSingleObject(handle, dwWaitMilliSeconds);
            switch (dwResult) {
            case WAIT_OBJECT_0:
                if ((milliseconds >= 100) || (milliseconds == INFINITE)) {
                    CRONO_LOG_DEBUG("...WaitForSingleObject(..., dwWaitMilliSeconds = " << dwWaitMilliSeconds << ")");
                }
                return JoinSuccess;
                break;
            case WAIT_TIMEOUT:
                if ((milliseconds >= 100) || (milliseconds == INFINITE)) {
                    CRONO_LOG_DEBUG("...WAIT_TIMEOUT on WaitForSingleObject(..., dwWaitMilliSeconds = " << dwWaitMilliSeconds << ")");
                }
                return JoinBusy;
                break;
            case WAIT_ABANDONED:
                CRONO_LOG_ERROR("...WAIT_ABANDONED on WaitForSingleObject(..., dwWaitMilliSeconds = " << dwWaitMilliSeconds << ")");
                return JoinInterrupted;
                break;
            default:
                CRONO_LOG_ERROR("...failed on WaitForSingleObject(..., dwWaitMilliSeconds = " << dwWaitMilliSeconds << ")");
                break;
            }
        }
        return JoinInvalid;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BOOL UseStdHandles(LPSTARTUPINFOA lpStartupInfo, HANDLE* fdup) const {
        BOOL bInheritHandles = FALSE;
        if ((fdup)) {
            HANDLE fd = 0;
            for (int i = 0; (i < 3) && (fd = fdup[i]); ++i) {
                bInheritHandles = TRUE;
                lpStartupInfo->dwFlags |= STARTF_USESTDHANDLES;
                switch(i) {
                case 0:
                    lpStartupInfo->hStdInput = fd;
                    break;
                case 1:
                    lpStartupInfo->hStdOutput = fd;
                    break;
                case 2:
                    lpStartupInfo->hStdError = fd;
                    break;
                }
            }
        }
        return bInheritHandles;
    }
    virtual BOOL UseStdHandles(LPSTARTUPINFOA lpStartupInfo, HANDLE** pdup) const {
        BOOL bInheritHandles = FALSE;
        if ((pdup)) {
            HANDLE* p = 0;
            HANDLE fd = 0;
            for (int i = 0; (i < 3) && (p = pdup[i]); ++i) {
                if ((fd = p[(i)?(1):(0)])) {
                    bInheritHandles = TRUE;
                    lpStartupInfo->dwFlags |= STARTF_USESTDHANDLES;
                    switch(i) {
                    case 0:
                        lpStartupInfo->hStdInput = fd;
                        break;
                    case 1:
                        lpStartupInfo->hStdOutput = fd;
                        break;
                    case 2:
                        lpStartupInfo->hStdError = fd;
                        break;
                    }
                }
            }
        }
        return bInheritHandles;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef nadir::wrappedt<PROCESS_INFORMATION> ProcessInformation;
    typedef nadir::wrappedt<STARTUPINFOA> StartupInfoWrappedA;
    class _EXPORT_CLASS StartupInfoA: public StartupInfoWrappedA {
    public:
        typedef StartupInfoWrappedA Extends;
        StartupInfoA(initialized_t initialized): Extends(initialized) {
            wrapped().cb = sizeof(STARTUPINFOA);
        }
    };
    typedef String ApplicationNameA;
    class _EXPORT_CLASS CommandLineA: public CharArray {
    public:
        CommandLineA(char** argv) {
            char null = 0;
            const char* arg = 0;
            if ((arg = *(argv++))) {
                this->append(arg);
                while ((arg = *(argv++))) {
                    this->append(" ");
                    this->append(arg);
                }
            }
            this->append(&null, 1);
        }
    };
    class _EXPORT_CLASS EnvironmentA: public CharArray {
    public:
        EnvironmentA(char** argv) {
            char null = 0;
            const char* arg = 0;
            if ((arg = *(argv++))) {
                do {
                    this->append(arg);
                    this->append(&null, 1);
                } while ((arg = *(argv++)));
            } else {
                this->append(&null, 1);
            }
            this->append(&null, 1);
        }
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    PROCESS_INFORMATION m_processInformation;
};
typedef ProcessT<> Process;

} // namespace windows 
} // namespace microsoft 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_MICROSOFT_WINDOWS_PROCESS_HPP 
