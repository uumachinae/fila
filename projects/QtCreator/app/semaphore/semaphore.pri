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
#   File: semaphore.pri
#
# Author: $author$
#   Date: 8/12/2025
#
# generic QtCreator project .pri file for framework fila executable semaphore
########################################################################

########################################################################
# semaphore

# semaphore TARGET
#
semaphore_TARGET = semaphore

# semaphore INCLUDEPATH
#
semaphore_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# semaphore DEFINES
#
semaphore_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_CONSOLE_MAIN_MAIN \

########################################################################
# semaphore OBJECTIVE_HEADERS
#
#semaphore_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/xos/app/console/semaphore/main.hh \

# semaphore OBJECTIVE_SOURCES
#
#semaphore_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/xos/app/console/semaphore/main.mm \

########################################################################
# semaphore HEADERS
#
semaphore_HEADERS += \
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
$${FILA_SRC}/xos/mt/semaphore.hpp \
$${FILA_SRC}/xos/mt/apple/mach/semaphore.hpp \
$${FILA_SRC}/xos/mt/apple/osx/semaphore.hpp \
$${FILA_SRC}/xos/mt/linux/semaphore.hpp \
$${FILA_SRC}/xos/mt/mach/semaphore.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/semaphore.hpp \
$${FILA_SRC}/xos/mt/oracle/solaris/semaphore.hpp \
$${FILA_SRC}/xos/mt/posix/semaphore.hpp \
$${FILA_SRC}/xos/mt/os/posix/semaphore.hpp \
$${FILA_SRC}/xos/mt/os/semaphore.hpp \
$${FILA_SRC}/xos/mt/semaphores.hpp \
\
$${FILA_SRC}/xos/app/console/mt/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/main.hpp \
$${FILA_SRC}/xos/app/console/mt/os/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/os/main.hpp \
\
$${FILA_SRC}/xos/app/console/mt/semaphore/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/semaphore/main.hpp \
$${FILA_SRC}/xos/app/console/semaphore/main_opt.hpp \
$${FILA_SRC}/xos/app/console/semaphore/main.hpp \

# semaphore SOURCES
#
semaphore_SOURCES += \
$${ROSTRA_SRC}/xos/os/sleep.cpp \
$${ROSTRA_SRC}/xos/os/oses.cpp \
\
$${FILA_SRC}/xos/mt/os/os.cpp \
$${FILA_SRC}/xos/mt/semaphores.cpp \
\
$${FILA_SRC}/xos/app/console/semaphore/main_opt.cpp \
$${FILA_SRC}/xos/app/console/semaphore/main.cpp \

########################################################################
# semaphore FRAMEWORKS
#
semaphore_FRAMEWORKS += \
$${fila_FRAMEWORKS} \

# semaphore LIBS
#
semaphore_LIBS += \
$${fila_LIBS} \

########################################################################
# NO Qt
QT -= gui core
