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
///   File: DLLibraryMain.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_OS_DLLIBRARYMAIN_HPP
#define _FILA_OS_DLLIBRARYMAIN_HPP

#include "fila/base/Base.hpp"
#include "crono/io/Logger.hpp"

namespace fila {
namespace os {

typedef ImplementBase DLLibraryMainImplements;
///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryMain
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLLibraryMain: virtual public DLLibraryMainImplements {
public:
    typedef DLLibraryMainImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() { return true; }
    virtual bool Fini() { return true; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static DLLibraryMain& TheDLLibraryMain();
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef DLLibraryMain DLLibraryMainExtendTImplements;
typedef Base DLLibraryMainExtendTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryMainExtendT
///////////////////////////////////////////////////////////////////////
template
<class TImplements = DLLibraryMainExtendTImplements,
 class TExtends = DLLibraryMainExtendTExtends>

class _EXPORT_CLASS DLLibraryMainExtendT
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TImplements DLLibraryMain;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLLibraryMainExtendT() {
    }
    virtual ~DLLibraryMainExtendT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef DLLibraryMainExtendT<> DLLibraryMainExtend;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void _init(void);
void _fini(void);

} // namespace os
} // namespace fila

#endif // _FILA_OS_DLLIBRARYMAIN_HPP
