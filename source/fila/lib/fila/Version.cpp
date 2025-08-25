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
///   File: Version.cpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#include "fila/lib/fila/Version.hpp"

#if !defined(FILA_LIB_FILA_VERSION_NAME)
#define FILA_LIB_FILA_VERSION_NAME "libfila"
#endif /// !defined(FILA_LIB_FILA_VERSION_NAME)

#if !defined(FILA_LIB_FILA_VERSION_MAJOR)
#define FILA_LIB_FILA_VERSION_MAJOR 0
#endif /// !defined(FILA_LIB_FILA_VERSION_MAJOR)

#if !defined(FILA_LIB_FILA_VERSION_MINOR)
#define FILA_LIB_FILA_VERSION_MINOR 0
#endif /// !defined(FILA_LIB_FILA_VERSION_MINOR)

#if !defined(FILA_LIB_FILA_VERSION_RELEASE)
#define FILA_LIB_FILA_VERSION_RELEASE 0
#endif /// !defined(FILA_LIB_FILA_VERSION_RELEASE)

namespace fila {
namespace lib {
namespace fila {

namespace which {
typedef lib::Version VersionImplements;
///////////////////////////////////////////////////////////////////////
///  Class: Version
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Version: virtual public VersionImplements {
public:
    typedef VersionImplements Implements;
    Version() {
    }
    virtual const char_t* Name() const {
        return FILA_LIB_FILA_VERSION_NAME;
    }
    virtual unsigned Major() const {
        return FILA_LIB_FILA_VERSION_MAJOR;
    }
    virtual unsigned Minor() const {
        return FILA_LIB_FILA_VERSION_MINOR;
    }
    virtual unsigned Release() const {
        return FILA_LIB_FILA_VERSION_RELEASE;
    }
}; /// class _EXPORT_CLASS Version
} /// namespace which

///////////////////////////////////////////////////////////////////////
///  Class: Version
///////////////////////////////////////////////////////////////////////
const lib::Version& Version::Which() {
    static const which::Version version;
    return version;
}

} /// namespace fila
} /// namespace lib
} /// namespace fila
