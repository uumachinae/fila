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
#   File: libfila.pri
#
# Author: $author$
#   Date: 8/11/2025
#
# generic QtCreator project .pri file for framework fila static library libfila
########################################################################

########################################################################
# libfila
XOS_LIB_FILA_VERSION_BUILD_DATE = 8/11/2025 #$$system(~/bin/utility/tdate)

# libfila TARGET
#
libfila_TARGET = fila
libfila_TEMPLATE = lib
libfila_CONFIG += staticlib

# libfila INCLUDEPATH
#
libfila_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# libfila DEFINES
#
libfila_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_LIB_FILA_VERSION_BUILD_DATE=$${XOS_LIB_FILA_VERSION_BUILD_DATE} \

########################################################################
# libfila OBJECTIVE_HEADERS
#
#libfila_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/xos/lib/fila/version.hh \

# libfila OBJECTIVE_SOURCES
#
#libfila_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/xos/lib/fila/version.mm \

########################################################################
# libfila HEADERS
#
libfila_HEADERS += \
$${FILA_SRC}/xos/platform/condition.h \
$${FILA_SRC}/xos/platform/condition.hpp \
$${FILA_SRC}/xos/platform/microsoft/windows/os/mutex.h \
$${FILA_SRC}/xos/platform/microsoft/windows/os/mutex.hpp \
$${FILA_SRC}/xos/platform/microsoft/windows/posix/mutex.h \
$${FILA_SRC}/xos/platform/microsoft/windows/posix/mutex.hpp \
$${FILA_SRC}/xos/platform/microsoft/windows/posix/semaphore.h \
$${FILA_SRC}/xos/platform/microsoft/windows/posix/semaphore.hpp \
$${FILA_SRC}/xos/platform/mutex.h \
$${FILA_SRC}/xos/platform/mutex.hpp \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Mutex.h \
$${FILA_SRC}/xos/platform/os/microsoft/windows/Mutex.hpp \
$${FILA_SRC}/xos/platform/os/oracle/solaris/mutex.h \
$${FILA_SRC}/xos/platform/os/oracle/solaris/mutex.hpp \
$${FILA_SRC}/xos/platform/os/platform/mutex.hpp \
$${FILA_SRC}/xos/platform/os/posix/mutex.h \
$${FILA_SRC}/xos/platform/os/posix/mutex.hpp \
$${FILA_SRC}/xos/platform/semaphore.h \
$${FILA_SRC}/xos/platform/semaphore.hpp \
$${FILA_SRC}/xos/platform/thread.h \
$${FILA_SRC}/xos/platform/thread.hpp \
\
$${FILA_SRC}/xos/mt/apple/mach/semaphore.hpp \
$${FILA_SRC}/xos/mt/apple/osx/condition.hpp \
$${FILA_SRC}/xos/mt/apple/osx/mutex.hpp \
$${FILA_SRC}/xos/mt/apple/osx/pipe.hpp \
$${FILA_SRC}/xos/mt/apple/osx/process.hpp \
$${FILA_SRC}/xos/mt/apple/osx/semaphore.hpp \
$${FILA_SRC}/xos/mt/apple/osx/thread.hpp \
$${FILA_SRC}/xos/mt/condition.hpp \
$${FILA_SRC}/xos/mt/conditions.hpp \
$${FILA_SRC}/xos/mt/linux/condition.hpp \
$${FILA_SRC}/xos/mt/linux/mutex.hpp \
$${FILA_SRC}/xos/mt/linux/semaphore.hpp \
$${FILA_SRC}/xos/mt/linux/thread.hpp \
$${FILA_SRC}/xos/mt/mach/mutex.hpp \
$${FILA_SRC}/xos/mt/mach/semaphore.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/crt/thread.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/mutex.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/mutexes.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/semaphore.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/semaphores.hpp \
$${FILA_SRC}/xos/mt/microsoft/windows/thread.hpp \
$${FILA_SRC}/xos/mt/mutex.hpp \
$${FILA_SRC}/xos/mt/mutexes.hpp \
$${FILA_SRC}/xos/mt/oracle/solaris/mutex.hpp \
$${FILA_SRC}/xos/mt/oracle/solaris/semaphore.hpp \
$${FILA_SRC}/xos/mt/os/condition.hpp \
$${FILA_SRC}/xos/mt/os/mutex.hpp \
$${FILA_SRC}/xos/mt/os/os.hpp \
$${FILA_SRC}/xos/mt/os/pipe.hpp \
$${FILA_SRC}/xos/mt/os/process.hpp \
$${FILA_SRC}/xos/mt/os/semaphore.hpp \
$${FILA_SRC}/xos/mt/os/semaphores.hpp \
$${FILA_SRC}/xos/mt/os/thread.hpp \
$${FILA_SRC}/xos/mt/pipe.hpp \
$${FILA_SRC}/xos/mt/posix/condition.hpp \
$${FILA_SRC}/xos/mt/posix/mutex.hpp \
$${FILA_SRC}/xos/mt/posix/pipe.hpp \
$${FILA_SRC}/xos/mt/posix/process.hpp \
$${FILA_SRC}/xos/mt/posix/semaphore.hpp \
$${FILA_SRC}/xos/mt/posix/thread.hpp \
$${FILA_SRC}/xos/mt/posix/timed.hpp \
$${FILA_SRC}/xos/mt/process.hpp \
$${FILA_SRC}/xos/mt/semaphore.hpp \
$${FILA_SRC}/xos/mt/semaphores.hpp \
$${FILA_SRC}/xos/mt/thread.hpp \
$${FILA_SRC}/xos/mt/threads.hpp \
\
$${FILA_SRC}/xos/lib/fila/version.hpp \

# libfila SOURCES
#
libfila_SOURCES += \
$${FILA_SRC}/xos/lib/fila/version.cpp \

########################################################################
# libfila HEADERS
#
libfila_HEADERS += \
$${FILA_SRC}/fila/base/Acquired.hpp \
$${FILA_SRC}/fila/base/Argv.hpp \
$${FILA_SRC}/fila/base/Attached.hpp \
$${FILA_SRC}/fila/base/Base.hpp \
$${FILA_SRC}/fila/base/Created.hpp \
$${FILA_SRC}/fila/base/Joined.hpp \
$${FILA_SRC}/fila/base/Locked.hpp \
$${FILA_SRC}/fila/base/Opened.hpp \
$${FILA_SRC}/fila/base/Ran.hpp \
$${FILA_SRC}/fila/base/Sleep.hpp \
$${FILA_SRC}/fila/base/Suspended.hpp \
$${FILA_SRC}/fila/base/Waited.hpp \
\
$${FILA_SRC}/fila/mt/apple/mach/Semaphore.hpp \
$${FILA_SRC}/fila/mt/apple/osx/Mutex.hpp \
$${FILA_SRC}/fila/mt/apple/osx/Process.hpp \
$${FILA_SRC}/fila/mt/apple/osx/Semaphore.hpp \
$${FILA_SRC}/fila/mt/apple/osx/Sleep.hpp \
$${FILA_SRC}/fila/mt/apple/osx/Thread.hpp \
$${FILA_SRC}/fila/mt/microsoft/windows/crt/Thread.hpp \
$${FILA_SRC}/fila/mt/microsoft/windows/Mutex.hpp \
$${FILA_SRC}/fila/mt/microsoft/windows/Process.hpp \
$${FILA_SRC}/fila/mt/microsoft/windows/Semaphore.hpp \
$${FILA_SRC}/fila/mt/microsoft/windows/Sleep.hpp \
$${FILA_SRC}/fila/mt/microsoft/windows/Thread.hpp \
$${FILA_SRC}/fila/mt/Mutex.hpp \
$${FILA_SRC}/fila/mt/os/Mutex.hpp \
$${FILA_SRC}/fila/mt/os/Os.hpp \
$${FILA_SRC}/fila/mt/os/Process.hpp \
$${FILA_SRC}/fila/mt/os/Semaphore.hpp \
$${FILA_SRC}/fila/mt/os/Sleep.hpp \
$${FILA_SRC}/fila/mt/os/Thread.hpp \
$${FILA_SRC}/fila/mt/posix/Mutex.hpp \
$${FILA_SRC}/fila/mt/posix/Process.hpp \
$${FILA_SRC}/fila/mt/posix/Semaphore.hpp \
$${FILA_SRC}/fila/mt/posix/Sleep.hpp \
$${FILA_SRC}/fila/mt/posix/Thread.hpp \
$${FILA_SRC}/fila/mt/Process.hpp \
$${FILA_SRC}/fila/mt/Semaphore.hpp \
$${FILA_SRC}/fila/mt/Sleep.hpp \
$${FILA_SRC}/fila/mt/Thread.hpp \
\
$${FILA_SRC}/fila/os/apple/osx/DLLibrary.hpp \
$${FILA_SRC}/fila/os/apple/osx/DLLibraryMain.hpp \
$${FILA_SRC}/fila/os/DLLibrary.hpp \
$${FILA_SRC}/fila/os/DLLibraryMain.hpp \
$${FILA_SRC}/fila/os/microsoft/windows/DLLibrary.hpp \
$${FILA_SRC}/fila/os/microsoft/windows/DLLibraryMain.hpp \
$${FILA_SRC}/fila/os/os/DLLibrary.hpp \
$${FILA_SRC}/fila/os/os/DLLibraryMain.hpp \
$${FILA_SRC}/fila/os/os/Os.hpp \
$${FILA_SRC}/fila/os/posix/DLLibrary.hpp \
$${FILA_SRC}/fila/os/posix/DLLibraryMain.hpp \
\
$${FILA_SRC}/fila/lib/Version.hpp \
$${FILA_SRC}/fila/lib/fila/Version.hpp \
$${FILA_SRC}/fila/lib/fila/Versions.hpp \

# libfila SOURCES
#
libfila_SOURCES += \
$${FILA_SRC}/fila/base/Acquired.cpp \
$${FILA_SRC}/fila/base/Argv.cpp \
$${FILA_SRC}/fila/base/Attached.cpp \
$${FILA_SRC}/fila/base/Base.cpp \
$${FILA_SRC}/fila/base/Created.cpp \
$${FILA_SRC}/fila/base/Joined.cpp \
$${FILA_SRC}/fila/base/Locked.cpp \
$${FILA_SRC}/fila/base/Opened.cpp \
$${FILA_SRC}/fila/base/Ran.cpp \
$${FILA_SRC}/fila/base/Sleep.cpp \
$${FILA_SRC}/fila/base/Suspended.cpp \
$${FILA_SRC}/fila/base/Waited.cpp \
\
$${FILA_SRC}/fila/mt/os/Mutex.cpp \
$${FILA_SRC}/fila/mt/os/Os.cpp \
$${FILA_SRC}/fila/mt/os/Process.cpp \
$${FILA_SRC}/fila/mt/os/Semaphore.cpp \
$${FILA_SRC}/fila/mt/os/Sleep.cpp \
$${FILA_SRC}/fila/mt/os/Thread.cpp \
\
$${FILA_SRC}/fila/os/DLLibrary.cpp \
\
$${FILA_SRC}/fila/lib/fila/Version.cpp \
$${FILA_SRC}/fila/lib/fila/Versions.cpp \

########################################################################
