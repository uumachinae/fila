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
#ifndef _FILA_MT_POSIX_SLEEP_HPP
#define _FILA_MT_POSIX_SLEEP_HPP

#include "fila/mt/Sleep.hpp"
#include "crono/io/Logger.hpp"

namespace fila {
namespace mt {
namespace posix {

void SleepSeconds(seconds_t seconds) {
    unsigned int secondsRemain = 0;

    CRONO_LOG_DEBUG("sleep(seconds = " << seconds << ")...");
    if ((secondsRemain = sleep(seconds))) {
        CRONO_LOG_ERROR("...interrupted secondsRemain = " << secondsRemain << " on sleep(seconds = " << seconds << ")");
    }
}
void SleepMilliseconds(mseconds_t milliseconds) {
    useconds_t useconds = milliseconds*1000;
    int err = 0;

    if (1000 <= (milliseconds)) {
        CRONO_LOG_DEBUG("usleep(useconds = " << useconds << ")...");
    } else {
        if (500 <= (milliseconds)) {
            CRONO_LOG_TRACE("usleep(useconds = " << useconds << ")...");
        }
    }
    if ((err = usleep(useconds))) {
        err = errno;
        CRONO_LOG_ERROR("...failed err = " << err << " on usleep(useconds = " << useconds << ")");
    }
}

} // namespace posix
} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_POSIX_SLEEP_HPP 
