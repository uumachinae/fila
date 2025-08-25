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
///   File: Joined.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_JOINED_HPP
#define _FILA_BASE_JOINED_HPP

#include "fila/base/Base.hpp"
#include "patrona/base/Joined.hpp"

namespace fila {

typedef ::patrona::JoinStatus JoinStatus;
static const JoinStatus JoinSuccess = ::patrona::JoinSuccess;
static const JoinStatus JoinFailed = ::patrona::JoinFailed;
static const JoinStatus JoinBusy = ::patrona::JoinBusy;
static const JoinStatus JoinInterrupted = ::patrona::JoinInterrupted;
static const JoinStatus JoinInvalid = ::patrona::JoinInvalid;
static const JoinStatus ForkSuccess = ::patrona::ForkSuccess;
static const JoinStatus ForkFailed = ::patrona::ForkFailed;
static const JoinStatus ForkBusy = ::patrona::ForkBusy;
static const JoinStatus ForkInterrupted = ::patrona::ForkInterrupted;
static const JoinStatus ForkInvalid = ::patrona::ForkInvalid;

typedef ::patrona::JoinException JoinException;

typedef ::patrona::Joined Joined;
typedef ::patrona::Joiner Joiner;
typedef ::patrona::Forker Forker;

} // namespace fila

#endif // _FILA_BASE_JOINED_HPP
