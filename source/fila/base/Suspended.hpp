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
///   File: Suspended.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_SUSPENDED_HPP
#define _FILA_BASE_SUSPENDED_HPP

#include "fila/base/Base.hpp"

namespace fila {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum SuspendStatus {
    ResumeSuccess,
    SuspendSuccess = ResumeSuccess,

    SuspendFailed,
    SuspendBusy,
    SuspendInterrupted,
    SuspendInvalid,

    ResumeFailed,
    ResumeBusy,
    ResumeInterrupted,
    ResumeInvalid
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* SuspendStatusToChars(SuspendStatus status) {
    switch (status) {
    case SuspendSuccess: return "SuspendSuccess";
    case SuspendFailed: return "SuspendFailed";
    case SuspendBusy: return "SuspendBusy";
    case SuspendInterrupted: return "SuspendInterrupted";
    case SuspendInvalid: return "SuspendInvalid";

    case ResumeFailed: return "ResumeFailed";
    case ResumeBusy: return "ResumeBusy";
    case ResumeInterrupted: return "ResumeInterrupted";
    case ResumeInvalid: return "ResumeInvalid";
    }
    return "Unknown";
}

typedef ImplementBase SuspendExceptionImplements;
typedef Base SuspendExceptionExtends;
///////////////////////////////////////////////////////////////////////
///  Class: SuspendExceptionT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = SuspendExceptionImplements,
 class TExtends = SuspendExceptionExtends>

class _EXPORT_CLASS SuspendExceptionT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SuspendExceptionT(SuspendStatus status): m_status(status) {}
    virtual ~SuspendExceptionT() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual SuspendStatus Status() const {
        return m_status;
    }
    virtual String StatusToString() const {
        String to(StatusToChars());
        return to;
    }
    virtual const char* StatusToChars() const {
        return SuspendStatusToChars(Status());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    SuspendStatus m_status;
};
typedef SuspendExceptionT<> SuspendException;

typedef ImplementBase SuspendedTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: SuspendedT
///////////////////////////////////////////////////////////////////////
template
<class TSuspendException = SuspendException,
 class TImplements = SuspendedTImplements>

class _EXPORT_CLASS SuspendedT: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TSuspendException SuspendException;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Suspend() { return false; }
    virtual SuspendStatus TrySuspend() { return SuspendFailed; }
    virtual SuspendStatus TimedSuspend(mseconds_t milliseconds) { return SuspendFailed; }
    virtual SuspendStatus UntimedSuspend() { return SuspendFailed; }
    virtual bool Resume() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef SuspendedT<> Suspended;

} // namespace fila 

#endif // _FILA_BASE_SUSPENDED_HPP 
        

