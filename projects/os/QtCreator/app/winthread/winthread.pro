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
#   File: winthread.pro
#
# Author: $author$
#   Date: 8/14/2025
#
# os specific QtCreator project .pro file for framework fila executable winthread
########################################################################
# Depends: rostra;nadir;crono
#
# Debug: fila/build/os/QtCreator/Debug/bin/winthread
# Release: fila/build/os/QtCreator/Release/bin/winthread
# Profile: fila/build/os/QtCreator/Profile/bin/winthread
#
include(../../../../../build/QtCreator/fila.pri)
include(../../../../QtCreator/fila.pri)
include(../../fila.pri)
include(../../../../QtCreator/app/winthread/winthread.pri)

TARGET = $${winthread_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${winthread_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${winthread_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${winthread_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${winthread_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${winthread_HEADERS} \
$${winthread_OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${winthread_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${winthread_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${winthread_LIBS} \
$${FRAMEWORKS} \

########################################################################
