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
#   File: thread.pri
#
# Author: $author$
#   Date: 8/12/2025
#
# generic QtCreator project .pri file for framework fila executable thread
########################################################################

########################################################################
# thread

# thread TARGET
#
thread_TARGET = thread

# thread INCLUDEPATH
#
thread_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# thread DEFINES
#
thread_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_CONSOLE_MAIN_MAIN \

########################################################################
# thread OBJECTIVE_HEADERS
#
#thread_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/xos/app/console/thread/main.hh \

# thread OBJECTIVE_SOURCES
#
#thread_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/xos/app/console/thread/main.mm \

########################################################################
# thread HEADERS
#
thread_HEADERS += \
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
$${NADIR_SRC}/xos/base/ran.hpp \
$${NADIR_SRC}/xos/base/suspended.hpp \
$${NADIR_SRC}/xos/base/resumed.hpp \
$${NADIR_SRC}/xos/base/forked.hpp \
$${NADIR_SRC}/xos/base/joined.hpp \
\
$${FILA_SRC}/xos/app/console/mt/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/main.hpp \
$${FILA_SRC}/xos/app/console/mt/os/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/os/main.hpp \
\
$${FILA_SRC}/xos/platform/microsoft/windows/posix/mutex.h \
$${FILA_SRC}/xos/platform/microsoft/windows/posix/mutex.hpp \
$${FILA_SRC}/xos/platform/microsoft/windows/os/mutex.h \
$${FILA_SRC}/xos/platform/microsoft/windows/os/mutex.hpp \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Mutex.h \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Mutex.hpp \
$${FILA_SRC}/xos/platform/os/oracle/solaris/mutex.h \
$${FILA_SRC}/xos/platform/os/oracle/solaris/mutex.hpp \
$${FILA_SRC}/xos/platform/os/mach/lock_set.h \
$${FILA_SRC}/xos/platform/os/mach/lock_set.hpp \
$${FILA_SRC}/xos/platform/os/posix/mutex.h \
$${FILA_SRC}/xos/platform/os/posix/mutex.hpp \
$${FILA_SRC}/xos/platform/os/platform/mutex.h \
$${FILA_SRC}/xos/platform/os/platform/mutex.hpp \
\
$${FILA_SRC}/xos/mt/os/os.hpp \
$${FILA_SRC}/xos/mt/apple/osx/mutex.hpp \
$${FILA_SRC}/xos/mt/linux/mutex.hpp \
$${FILA_SRC}/xos/mt/mach/mutex.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/mutex.hpp \
$${FILA_SRC}/xos/mt/mutex.hpp \
$${FILA_SRC}/xos/mt/oracle/solaris/mutex.hpp \
$${FILA_SRC}/xos/mt/os/mutex.hpp \
$${FILA_SRC}/xos/mt/os/posix/mutex.hpp \
$${FILA_SRC}/xos/mt/posix/mutex.hpp \
$${FILA_SRC}/xos/mt/mutexes.hpp \
\
$${FILA_SRC}/xos/platform/thread.h \
$${FILA_SRC}/xos/platform/thread.hpp \
$${FILA_SRC}/xos/platform/os/platform/thread.hpp \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Thread.h \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Thread.hpp \
\
$${FILA_SRC}/xos/mt/thread.hpp \
$${FILA_SRC}/xos/mt/posix/thread.hpp \
$${FILA_SRC}/xos/mt/os/thread.hpp \
$${FILA_SRC}/xos/mt/threads.hpp \
\
$${FILA_SRC}/xos/app/console/mt/mutex/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/mutex/main.hpp \
$${FILA_SRC}/xos/app/console/mt/mutex/os/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/mutex/os/main.hpp \
$${FILA_SRC}/xos/app/console/mutex/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mutex/main.hpp \
\
$${FILA_SRC}/xos/app/console/mt/thread/array.hpp \
$${FILA_SRC}/xos/app/console/mt/thread/main_opt.hpp \
$${FILA_SRC}/xos/app/console/mt/thread/main.hpp \
$${FILA_SRC}/xos/app/console/thread/main_opt.hpp \
$${FILA_SRC}/xos/app/console/thread/main.hpp \

# thread SOURCES
#
thread_SOURCES += \
$${ROSTRA_SRC}/xos/os/sleep.cpp \
$${ROSTRA_SRC}/xos/os/oses.cpp \
\
$${NADIR_SRC}/xos/base/ran.cpp \
$${NADIR_SRC}/xos/base/suspended.cpp \
$${NADIR_SRC}/xos/base/resumed.cpp \
$${NADIR_SRC}/xos/base/forked.cpp \
$${NADIR_SRC}/xos/base/joined.cpp \
\
$${FILA_SRC}/xos/mt/os/os.cpp \
$${FILA_SRC}/xos/mt/os/mutex.cpp \
$${FILA_SRC}/xos/mt/mutexes.cpp \
$${FILA_SRC}/xos/mt/threads.cpp \
\
$${FILA_SRC}/xos/app/console/mt/thread/array.cpp \
$${FILA_SRC}/xos/app/console/thread/main.cpp \

########################################################################
# thread FRAMEWORKS
#
thread_FRAMEWORKS += \
$${fila_FRAMEWORKS} \

# thread LIBS
#
thread_LIBS += \
$${fila_LIBS} \

########################################################################
# NO Qt
QT -= gui core
