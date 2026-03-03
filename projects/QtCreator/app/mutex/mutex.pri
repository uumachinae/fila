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
#   File: mutex.pri
#
# Author: $author$
#   Date: 8/12/2025
#
# generic QtCreator project .pri file for framework fila executable mutex
########################################################################

########################################################################
# mutex

# mutex TARGET
#
mutex_TARGET = mutex

# mutex INCLUDEPATH
#
mutex_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# mutex DEFINES
#
mutex_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_CONSOLE_MAIN_MAIN \

########################################################################
# mutex OBJECTIVE_HEADERS
#
#mutex_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/xos/app/console/mutex/main.hh \

# mutex OBJECTIVE_SOURCES
#
#mutex_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/xos/app/console/mutex/main.mm \

########################################################################
# mutex HEADERS
#
mutex_HEADERS += \
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

# mutex SOURCES
#
mutex_SOURCES += \
$${ROSTRA_SRC}/xos/os/sleep.cpp \
$${ROSTRA_SRC}/xos/os/oses.cpp \
\
$${FILA_SRC}/xos/mt/os/os.cpp \
$${FILA_SRC}/xos/mt/mutexes.cpp \
\
$${FILA_SRC}/xos/app/console/mutex/main_opt.cpp \
$${FILA_SRC}/xos/app/console/mutex/main.cpp \

########################################################################
# mutex FRAMEWORKS
#
mutex_FRAMEWORKS += \
$${fila_FRAMEWORKS} \

# mutex LIBS
#
mutex_LIBS += \
$${fila_LIBS} \

########################################################################
# NO Qt
QT -= gui core
