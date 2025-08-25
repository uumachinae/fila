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
///   File: Waited.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_WAITED_HPP
#define _FILA_BASE_WAITED_HPP

#include "patrona/base/Waited.hpp"

namespace fila {

typedef ::patrona::WaitStatus WaitStatus;
static const WaitStatus WaitSuccess = ::patrona::WaitSuccess;
static const WaitStatus WaitFailed = ::patrona::WaitFailed;
static const WaitStatus WaitBusy = ::patrona::WaitBusy;
static const WaitStatus WaitInterrupted = ::patrona::WaitInterrupted;
static const WaitStatus WaitInvalid = ::patrona::WaitInvalid;
static const WaitStatus ContinueSuccess = ::patrona::ContinueSuccess;
static const WaitStatus ContinueFailed = ::patrona::ContinueFailed;
static const WaitStatus ContinueBusy = ::patrona::ContinueBusy;
static const WaitStatus ContinueInterrupted = ::patrona::ContinueInterrupted;
static const WaitStatus ContinueInvalid = ::patrona::ContinueInvalid;

typedef ::patrona::WaitException WaitException;

typedef ::patrona::Waited Waited;
typedef ::patrona::Waiter Waiter;
typedef ::patrona::Continuer Continuer;

} // namespace fila

#endif // _FILA_BASE_WAITED_HPP
