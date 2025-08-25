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
///   File: semaphore.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_NADIR_MT_SEMAPHORE_HPP
#define _FILA_NADIR_MT_SEMAPHORE_HPP

#include "fila/nadir/base/base.hpp"

namespace fila {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: semaphore_waitedt
///////////////////////////////////////////////////////////////////////
template
<class TWaitedImplements = waited, class TAcquiredImplements = acquired>

class _EXPORT_CLASS semaphore_waitedt
: virtual public TWaitedImplements, virtual public TAcquiredImplements {
public:
    typedef TWaitedImplements WaitedImplements;
    typedef TAcquiredImplements AcquiredImplements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool wait() {
        if ((this->acquire())) {
            return true;
        }
        return false;
    }
    virtual wait_status try_wait() {
        acquire_status status = acquire_failed;
        switch ((status = this->try_acquire())) {
        case acquire_success: return wait_success;
        case acquire_busy: return wait_busy;
        case acquire_interrupted: return wait_interrupted;
        case acquire_invalid: return wait_invalid;
        }
        return wait_failed;
    }
    virtual wait_status untimed_wait() {
        acquire_status status = acquire_failed;
        switch ((status = this->untimed_acquire())) {
        case acquire_success: return wait_success;
        case acquire_busy: return wait_busy;
        case acquire_interrupted: return wait_interrupted;
        case acquire_invalid: return wait_invalid;
        }
        return wait_failed;
    }
    virtual wait_status timed_wait(mseconds_t milliseconds) {
        acquire_status status = acquire_failed;
        switch ((status = this->timed_acquire(milliseconds))) {
        case acquire_success: return wait_success;
        case acquire_busy: return wait_busy;
        case acquire_interrupted: return wait_interrupted;
        case acquire_invalid: return wait_invalid;
        }
        return wait_failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef semaphore_waitedt<> semaphore_waited;

typedef nadir::creatort<semaphore_waited> semaphoret_implements;
///////////////////////////////////////////////////////////////////////
///  Class: semaphoret
///////////////////////////////////////////////////////////////////////
template <class TImplements = semaphoret_implements>

class _EXPORT_CLASS semaphoret: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef semaphoret<> semaphore;

} // namespace mt 
} // namespace fila 

#endif // _FILA_NADIR_MT_SEMAPHORE_HPP 
