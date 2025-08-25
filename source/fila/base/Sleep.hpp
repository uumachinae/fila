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
///   File: Sleep.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_SLEEP_HPP
#define _FILA_BASE_SLEEP_HPP

#include "patrona/base/Sleep.hpp"

namespace fila {

typedef ::patrona::SleepStatus SleepStatus;
static const SleepStatus SleepSuccess = ::patrona::SleepSuccess;
static const SleepStatus SleepFailed = ::patrona::SleepFailed;
static const SleepStatus SleepBusy = ::patrona::SleepBusy;
static const SleepStatus SleepInterrupted = ::patrona::SleepInterrupted;
static const SleepStatus SleepInvalid = ::patrona::SleepInvalid;
static const SleepStatus WakeSuccess = ::patrona::WakeSuccess;
static const SleepStatus WakeFailed = ::patrona::WakeFailed;
static const SleepStatus WakeBusy = ::patrona::WakeBusy;
static const SleepStatus WakeInterrupted = ::patrona::WakeInterrupted;
static const SleepStatus WakeInvalid = ::patrona::WakeInvalid;

typedef ::patrona::SleepException SleepException;

typedef ::patrona::Sleeper Sleeper;

} // namespace fila 

#endif // _FILA_BASE_SLEEP_HPP 
        

