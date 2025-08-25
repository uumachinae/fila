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
///   File: base.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_NADIR_BASE_BASE_HPP
#define _FILA_NADIR_BASE_BASE_HPP

#include "crono/nadir/base/base.hpp"
#include "nadir/base/acquired.hpp"
#include "nadir/base/waited.hpp"
#include "nadir/base/joined.hpp"
#include "nadir/base/suspended.hpp"
#include "nadir/base/ran.hpp"

namespace fila {

typedef nadir::implement_base implement_base;
typedef nadir::base base;

typedef nadir::chars_t chars_t;
typedef nadir::tchars_t tchars_t;
typedef nadir::wchars_t wchars_t;

typedef nadir::char_array char_array;
typedef nadir::tchar_array tchar_array;
typedef nadir::wchar_array wchar_array;

typedef nadir::char_string char_string;
typedef nadir::tchar_string tchar_string;
typedef nadir::wchar_string wchar_string;

typedef nadir::chars_to_string chars_to_string;
typedef nadir::chars_to_tstring chars_to_tstring;
typedef nadir::chars_to_wstring chars_to_wstring;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline seconds_t mseconds_seconds
(mseconds_t mseconds) { return mseconds / 1000; }

inline mseconds_t mseconds_mseconds
(mseconds_t mseconds) { return mseconds % 1000; }

inline useconds_t mseconds_useconds
(mseconds_t mseconds) { return mseconds_mseconds(mseconds) * 1000; }

inline nseconds_t mseconds_nseconds
(mseconds_t mseconds) { return mseconds_useconds(mseconds) * 1000; }

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::creator creator;
typedef nadir::create_exception create_exception;
typedef nadir::create_status create_status;
const nadir::create_status
    destroy_success = nadir::destroy_success,
    create_success = nadir::create_success,
    create_failed = nadir::create_failed,
    destroy_failed = nadir::destroy_failed;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::locked locked;
typedef nadir::locker locker;
typedef nadir::lock_status lock_status;
const nadir::lock_status
    unlock_success     = nadir::unlock_success,
    lock_success       = nadir::lock_success,
    lock_failed        = nadir::lock_failed,
    lock_busy          = nadir::lock_busy,
    lock_interrupted   = nadir::lock_interrupted,
    lock_invalid       = nadir::lock_invalid,
    unlock_failed      = nadir::unlock_failed,
    unlock_busy        = nadir::unlock_busy,
    unlock_interrupted = nadir::unlock_interrupted,
    unlock_invalid     = nadir::unlock_invalid;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::acquired acquired;
typedef nadir::acquire_status acquire_status;
typedef nadir::acquire_exception acquire_exception;
const nadir::acquire_status
    release_success = nadir::release_success,
    acquire_success = nadir::acquire_success,
    acquire_failed = nadir::acquire_failed,
    acquire_busy = nadir::acquire_busy,
    acquire_interrupted = nadir::acquire_interrupted,
    acquire_invalid = nadir::acquire_invalid ,
    release_failed = nadir::release_failed,
    release_busy = nadir::release_busy,
    release_interrupted = nadir::release_interrupted,
    release_invalid = nadir::release_invalid;


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::waited waited;
typedef nadir::waiter waiter;
typedef nadir::wait_status wait_status;
typedef nadir::wait_exception wait_exception;
const nadir::wait_status
    wait_success = nadir::wait_success,
    wait_failed = nadir::wait_failed,
    wait_busy = nadir::wait_busy,
    wait_interrupted = nadir::wait_interrupted,
    wait_invalid = nadir::wait_invalid;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::joined joined;
typedef nadir::join_status join_status;
typedef nadir::join_exception join_exception;
const nadir::join_status
    fork_success = nadir::fork_success,
    join_success = nadir::join_success,
    join_failed = nadir::join_failed,
    join_busy = nadir::join_busy,
    join_interrupted = nadir::join_interrupted,
    join_invalid = nadir::join_invalid,
    fork_failed = nadir::fork_failed,
    fork_busy = nadir::fork_busy,
    fork_interrupted = nadir::fork_interrupted,
    fork_invalid = nadir::fork_invalid;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::suspended suspended;
typedef nadir::suspend_status suspend_status;
typedef nadir::suspend_exception suspend_exception;
const nadir::suspend_status
    resume_success = nadir::resume_success,
    suspend_success = nadir::suspend_success,
    suspend_failed = nadir::suspend_failed,
    suspend_busy = nadir::suspend_busy,
    suspend_interrupted = nadir::suspend_interrupted,
    suspend_invalid = nadir::suspend_invalid,
    resume_failed = nadir::resume_failed,
    resume_busy = nadir::resume_busy,
    resume_interrupted = nadir::resume_interrupted,
    resume_invalid = nadir::resume_invalid;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef nadir::ran ran;

} // namespace fila

#endif // _FILA_NADIR_BASE_BASE_HPP
