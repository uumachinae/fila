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
///   File: Created.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_CREATED_HPP
#define _FILA_BASE_CREATED_HPP

#include "patrona/base/Created.hpp"

namespace fila {

typedef ::patrona::CreateStatus CreateStatus;
static const CreateStatus CreateSuccess = ::patrona::CreateSuccess;
static const CreateStatus CreateFailed = ::patrona::CreateFailed;
static const CreateStatus DestroySuccess = ::patrona::DestroySuccess;
static const CreateStatus DestroyFailed = ::patrona::DestroyFailed;

typedef ::patrona::CreateException CreateException;
typedef ::patrona::Creator Creator;

} // namespace fila

#endif // _FILA_BASE_CREATED_HPP 
