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
///   File: Process.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_MT_PROCESS_HPP
#define _FILA_MT_PROCESS_HPP

#include "fila/base/Suspended.hpp"
#include "fila/base/Joined.hpp"
#include "fila/base/Created.hpp"

namespace fila {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: ProcessTImplementsT
///////////////////////////////////////////////////////////////////////
template
<class TSuspended = Suspended, class TJoined = Joined, class TCreator = Creator>
class _EXPORT_CLASS ProcessTImplementsT
: virtual public TSuspended, virtual public TJoined, virtual public TCreator {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ProcessTImplementsT<> ProcessTImplements;

///////////////////////////////////////////////////////////////////////
///  Class: ProcessT
///////////////////////////////////////////////////////////////////////
template <class TImplements = ProcessTImplements>
class _EXPORT_CLASS ProcessT: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const char* path, char** argv, char** env,
     int* fdup, int** pdup, bool isDetached = false) {
        return false;
    }
    virtual bool Create() {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ProcessT<> Process;

} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_PROCESS_HPP 
        

