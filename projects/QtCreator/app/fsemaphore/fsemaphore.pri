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
#   File: fsemaphore.pri
#
# Author: $author$
#   Date: 8/17/2025
#
# generic QtCreator project .pri file for framework fila executable fsemaphore
########################################################################

########################################################################
# fsemaphore

# fsemaphore TARGET
#
fsemaphore_TARGET = fsemaphore

# fsemaphore INCLUDEPATH
#
fsemaphore_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# fsemaphore DEFINES
#
fsemaphore_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_CONSOLE_MAIN_MAIN \

########################################################################
# fsemaphore OBJECTIVE_HEADERS
#
#fsemaphore_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/fila/app/console/semaphore/main.hh \

# fsemaphore OBJECTIVE_SOURCES
#
#fsemaphore_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/fila/app/console/semaphore/main.mm \

########################################################################
# fsemaphore HEADERS
#
fsemaphore_HEADERS += \
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
\
$${FILA_SRC}/fila/console/Main_main.hpp \
$${FILA_SRC}/fila/console/lib/fila/version/Main.hpp \
$${FILA_SRC}/fila/app/console/fila/MainOpt.hpp \
$${FILA_SRC}/fila/app/console/fila/Main.hpp \
\
$${FILA_SRC}/fila/app/console/mt/MainOpt.hpp \
$${FILA_SRC}/fila/app/console/mt/Main.hpp \
$${FILA_SRC}/fila/app/console/mutex/MainOpt.hpp \
$${FILA_SRC}/fila/app/console/mutex/Main.hpp \
$${FILA_SRC}/fila/app/console/semaphore/MainOpt.hpp \
$${FILA_SRC}/fila/app/console/semaphore/Main.hpp \

# fsemaphore SOURCES
#
fsemaphore_SOURCES += \
$${FILA_SRC}/fila/console/Main_main.cpp \
$${FILA_SRC}/fila/app/console/semaphore/MainOpt.cpp \
$${FILA_SRC}/fila/app/console/semaphore/Main.cpp \

########################################################################
# fsemaphore FRAMEWORKS
#
fsemaphore_FRAMEWORKS += \
$${fila_FRAMEWORKS} \

# fsemaphore LIBS
#
fsemaphore_LIBS += \
$${fila_LIBS} \

########################################################################
# NO Qt
QT -= gui core
