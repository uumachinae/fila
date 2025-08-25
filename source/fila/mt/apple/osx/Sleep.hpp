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
#ifndef _FILA_MT_APPLE_OSX_SLEEP_HPP
#define _FILA_MT_APPLE_OSX_SLEEP_HPP

#include "fila/mt/posix/Sleep.hpp"

namespace fila {
namespace mt {
namespace apple {
namespace osx {

inline void SleepSeconds(seconds_t seconds) {
    posix::SleepSeconds(seconds);
}
inline void SleepMilliseconds(mseconds_t milliseconds) {
    posix::SleepMilliseconds(milliseconds);
}

} // namespace osx
} // namespace apple 
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_APPLE_OSX_SLEEP_HPP 
