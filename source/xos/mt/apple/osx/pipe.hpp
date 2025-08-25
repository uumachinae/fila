///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: pipe.hpp
///
/// Author: $author$
///   Date: 10/3/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_APPLE_OSX_PIPE_HPP
#define _XOS_MT_APPLE_OSX_PIPE_HPP

#include "xos/mt/posix/pipe.hpp"

namespace xos {
namespace mt {
namespace apple {
namespace osx {

typedef posix::pipe pipe;
typedef posix::char_pipe char_pipe;
typedef posix::tchar_pipe tchar_pipe;
typedef posix::wchar_pipe wchar_pipe;

} /// namespace osx
} /// namespace apple
} /// namespace mt
} /// namespace xos

#endif /// _XOS_MT_APPLE_OSX_PIPE_HPP 
