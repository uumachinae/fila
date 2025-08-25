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
///   File: Locked.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_LOCKED_HPP
#define _FILA_BASE_LOCKED_HPP

#include "patrona/base/Locked.hpp"

namespace fila {

typedef ::patrona::LockStatus LockStatus;
static const LockStatus LockSuccess = ::patrona::LockSuccess;
static const LockStatus LockFailed = ::patrona::LockFailed;
static const LockStatus LockBusy = ::patrona::LockBusy;
static const LockStatus LockInterrupted = ::patrona::LockInterrupted;
static const LockStatus LockInvalid = ::patrona::LockInvalid;
static const LockStatus UnlockSuccess = ::patrona::UnlockSuccess;
static const LockStatus UnlockFailed = ::patrona::UnlockFailed;
static const LockStatus UnlockBusy = ::patrona::UnlockBusy;
static const LockStatus UnlockInterrupted = ::patrona::UnlockInterrupted;
static const LockStatus UnlockInvalid = ::patrona::UnlockInvalid;

typedef ::patrona::LockException LockException;

typedef ::patrona::Locked Locked;
typedef ::patrona::Locker Locker;

} // namespace fila

#endif // _FILA_BASE_LOCKED_HPP 
