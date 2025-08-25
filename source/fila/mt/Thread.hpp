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
///   File: Thread.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_MT_THREAD_HPP
#define _FILA_MT_THREAD_HPP

#include "fila/base/Ran.hpp"
#include "fila/base/Suspended.hpp"
#include "fila/base/Joined.hpp"
#include "fila/base/Created.hpp"

namespace fila {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: ThreadTImplementsT
///////////////////////////////////////////////////////////////////////
template
<class TRan = Ran, class TSuspended = Suspended, class TJoined = Joined>

class _EXPORT_CLASS ThreadTImplementsT
: virtual public TRan, virtual public TSuspended, virtual public TJoined {
public:
};
typedef ThreadTImplementsT<> ThreadTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: ThreadT
///////////////////////////////////////////////////////////////////////
template <class TImplements = ThreadTImplements>
class _EXPORT_CLASS ThreadT: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(bool initiallySuspended) { return false; }
    virtual bool Create() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ThreadT<> Thread;

} // namespace mt 
} // namespace fila 

#endif // _FILA_MT_THREAD_HPP 
        

