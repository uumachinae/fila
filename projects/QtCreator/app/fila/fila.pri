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
#   File: fila.pri
#
# Author: $author$
#   Date: 8/11/2025
#
# generic QtCreator project .pri file for framework fila executable fila
########################################################################

########################################################################
# fila

# fila_exe TARGET
#
fila_exe_TARGET = fila

# fila_exe INCLUDEPATH
#
fila_exe_INCLUDEPATH += \
$${fila_INCLUDEPATH} \

# fila_exe DEFINES
#
fila_exe_DEFINES += \
$${fila_DEFINES} \
DEFAULT_LOGGING_LEVELS_ERROR \
XOS_CONSOLE_MAIN_MAIN \

########################################################################
# fila_exe OBJECTIVE_HEADERS
#
#fila_exe_OBJECTIVE_HEADERS += \
#$${FILA_SRC}/xos/app/console/fila/main.hh \

# fila_exe OBJECTIVE_SOURCES
#
#fila_exe_OBJECTIVE_SOURCES += \
#$${FILA_SRC}/xos/app/console/fila/main.mm \

########################################################################
# fila_exe HEADERS
#
fila_exe_HEADERS += \
$${NADIR_SRC}/xos/console/main_opt.hpp \
$${NADIR_SRC}/xos/console/main.hpp \
$${NADIR_SRC}/xos/console/getopt/main_opt.hpp \
$${NADIR_SRC}/xos/console/getopt/main.hpp \
\
$${NADIR_SRC}/xos/app/console/main_opt.hpp \
$${NADIR_SRC}/xos/app/console/main.hpp \
$${NADIR_SRC}/xos/app/console/version/main_opt.hpp \
$${NADIR_SRC}/xos/app/console/version/main.hpp \
$${NADIR_SRC}/xos/app/console/output/base/main_opt.hpp \
$${NADIR_SRC}/xos/app/console/output/base/main.hpp \
$${NADIR_SRC}/xos/app/console/input/base/main_opt.hpp \
$${NADIR_SRC}/xos/app/console/input/base/main.hpp \
\
$${NADIR_SRC}/xos/app/console/framework/version/main_opt.hpp \
$${NADIR_SRC}/xos/app/console/framework/version/main.hpp \
$${NADIR_SRC}/xos/app/console/nadir/version/main_opt.hpp \
$${NADIR_SRC}/xos/app/console/nadir/version/main.hpp \
\
$${FILA_SRC}/xos/app/console/framework/version/main_opt.hpp \
$${FILA_SRC}/xos/app/console/framework/version/main.hpp \
$${FILA_SRC}/xos/app/console/fila/version/main_opt.hpp \
$${FILA_SRC}/xos/app/console/fila/version/main.hpp \
$${FILA_SRC}/xos/app/console/fila/main_opt.hpp \
$${FILA_SRC}/xos/app/console/fila/main.hpp \

# fila_exe SOURCES
#
fila_exe_SOURCES += \
$${FILA_SRC}/xos/app/console/fila/main_opt.cpp \
$${FILA_SRC}/xos/app/console/fila/main.cpp \

########################################################################
# fila_exe FRAMEWORKS
#
fila_exe_FRAMEWORKS += \
$${fila_FRAMEWORKS} \

# fila_exe LIBS
#
fila_exe_LIBS += \
$${fila_LIBS} \

########################################################################
# NO Qt
QT -= gui core
