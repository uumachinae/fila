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
#   File: fsemaphore.pro
#
# Author: $author$
#   Date: 8/17/2025
#
# os specific QtCreator project .pro file for framework fila executable fsemaphore
########################################################################
# Depends: rostra;nadir;crono
#
# Debug: fila/build/os/QtCreator/Debug/bin/fsemaphore
# Release: fila/build/os/QtCreator/Release/bin/fsemaphore
# Profile: fila/build/os/QtCreator/Profile/bin/fsemaphore
#
include(../../../../../build/QtCreator/fila.pri)
include(../../../../QtCreator/fila.pri)
include(../../fila.pri)
include(../../../../QtCreator/app/fsemaphore/fsemaphore.pri)

TARGET = $${fsemaphore_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${fsemaphore_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${fsemaphore_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${fsemaphore_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${fsemaphore_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${fsemaphore_HEADERS} \
$${fsemaphore_OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${fsemaphore_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${fsemaphore_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${fsemaphore_LIBS} \
$${FRAMEWORKS} \

########################################################################
