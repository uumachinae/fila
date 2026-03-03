########################################################################
# Copyright (c) 1988-2025 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: winmutex.pri
#
# Author: $author$
#   Date: 8/13/2025
#
# generic QtCreator project .pri file for framework fila executable winmutex
########################################################################

########################################################################
# winmutex

# winmutex TARGET
#
winmutex_TARGET = winmutex

# winmutex INCLUDEPATH
#
winmutex_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# winmutex DEFINES
#
winmutex_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_CONSOLE_MAIN_MAIN \

########################################################################
# winmutex OBJECTIVE_HEADERS
#
#winmutex_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/xos/app/console/winmutex/main.hh \

# winmutex OBJECTIVE_SOURCES
#
#winmutex_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/xos/app/console/winmutex/main.mm \

########################################################################
# winmutex HEADERS
#
winmutex_HEADERS += \
$${ROSTRA_SRC}/xos/platform/os/posix/sys/time.h \
$${ROSTRA_SRC}/xos/platform/os/posix/sys/time.hpp \
$${ROSTRA_SRC}/xos/platform/os/oses.hpp \
\
$${ROSTRA_SRC}/xos/os/os.hpp \
$${ROSTRA_SRC}/xos/os/sleep.hpp \
$${ROSTRA_SRC}/xos/os/time.hpp \
$${ROSTRA_SRC}/xos/os/linux/sleep.hpp \
$${ROSTRA_SRC}/xos/os/linux/time.hpp \
$${ROSTRA_SRC}/xos/os/posix/sleep.hpp \
$${ROSTRA_SRC}/xos/os/posix/time.hpp \
$${ROSTRA_SRC}/xos/os/apple/osx/sleep.hpp \
$${ROSTRA_SRC}/xos/os/apple/osx/time.hpp \
$${ROSTRA_SRC}/xos/os/microsoft/windows/sleep.hpp \
$${ROSTRA_SRC}/xos/os/microsoft/windows/time.hpp \
$${ROSTRA_SRC}/xos/os/microsoft/windows.hpp \
$${ROSTRA_SRC}/xos/os/oses.hpp \
\
$${FILA_SRC}/xos/platform/microsoft/windows/posix/mutex.h \
$${FILA_SRC}/xos/platform/microsoft/windows/posix/mutex.hpp \
$${FILA_SRC}/xos/platform/microsoft/windows/os/mutex.h \
$${FILA_SRC}/xos/platform/microsoft/windows/os/mutex.hpp \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Mutex.h \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Mutex.hpp \
\
$${FILA_SRC}/xos/platform/os/oracle/solaris/mutex.h \
$${FILA_SRC}/xos/platform/os/oracle/solaris/mutex.hpp \
$${FILA_SRC}/xos/platform/os/mach/lock_set.h \
$${FILA_SRC}/xos/platform/os/mach/lock_set.hpp \
$${FILA_SRC}/xos/platform/os/posix/mutex.h \
$${FILA_SRC}/xos/platform/os/posix/mutex.hpp \
$${FILA_SRC}/xos/platform/os/platform/mutex.h \
$${FILA_SRC}/xos/platform/os/platform/mutex.hpp \
\
$${FILA_SRC}/xos/mt/apple/osx/mutex.hpp \
$${FILA_SRC}/xos/mt/linux/mutex.hpp \
$${FILA_SRC}/xos/mt/mach/mutex.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/mutex.hpp \
$${FILA_SRC}/xos/mt/mutex.hpp \
$${FILA_SRC}/xos/mt/oracle/solaris/mutex.hpp \
$${FILA_SRC}/xos/mt/os/os.hpp \
$${FILA_SRC}/xos/mt/os/mutex.hpp \
$${FILA_SRC}/xos/mt/os/posix/mutex.hpp \
$${FILA_SRC}/xos/mt/posix/mutex.hpp \
$${FILA_SRC}/xos/mt/mutexes.hpp \
\
$${FILA_SRC}/xos/app/console/mt/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/main.hpp \
$${FILA_SRC}/xos/app/console/mt/os/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/os/main.hpp \
\
$${FILA_SRC}/xos/app/console/mt/mutex/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/mutex/main.hpp \
$${FILA_SRC}/xos/app/console/mt/mutex/os/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/mutex/os/main.hpp \
\
$${FILA_SRC}/xos/app/console/mutex/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mutex/main.hpp \
\
$${FILA_SRC}/xos/app/console/microsoft/windows/mt/main_opt.hpp \
$${FILA_SRC}/xos/app/console/microsoft/windows/mt/main.hpp \
$${FILA_SRC}/xos/app/console/microsoft/windows/mutex/main_opt.hpp \
$${FILA_SRC}/xos/app/console/microsoft/windows/mutex/main.hpp \

# winmutex SOURCES
#
winmutex_SOURCES += \
$${ROSTRA_SRC}/xos/os/sleep.cpp \
$${ROSTRA_SRC}/xos/os/oses.cpp \
\
$${FILA_SRC}/xos/mt/os/os.cpp \
$${FILA_SRC}/xos/mt/mutexes.cpp \
\
$${FILA_SRC}/xos/app/console/microsoft/windows/mutex/main_opt.cpp \
$${FILA_SRC}/xos/app/console/microsoft/windows/mutex/main.cpp \

########################################################################
# winmutex FRAMEWORKS
#
winmutex_FRAMEWORKS += \
$${fila_FRAMEWORKS} \

# winmutex LIBS
#
winmutex_LIBS += \
$${fila_LIBS} \

########################################################################
# NO Qt
QT -= gui core

