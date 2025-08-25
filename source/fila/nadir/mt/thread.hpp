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
///   File: thread.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_NADIR_MT_THREAD_HPP
#define _FILA_NADIR_MT_THREAD_HPP

#include "fila/nadir/base/base.hpp"

namespace fila {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: thread_creator_implementst
///////////////////////////////////////////////////////////////////////
template
<class TJoinedImplements = joined,
 class TSuspendedImplements = suspended,
 class TRanImplements = ran>

class _EXPORT_CLASS thread_creator_implementst
: virtual public TJoinedImplements,
  virtual public TSuspendedImplements,
  virtual public TRanImplements {
public:
    typedef TJoinedImplements JoinedImplements;
    typedef TSuspendedImplements SuspendedImplements;
    typedef TRanImplements RunImplements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef thread_creator_implementst<> thread_creator_implements;

typedef nadir::creatort<thread_creator_implements> threadt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: threadt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = threadt_implements>

class _EXPORT_CLASS threadt: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::create;
    virtual bool create(bool initiallySuspended) { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef threadt<> thread;

} // namespace mt 
} // namespace fila 

#endif // _FILA_NADIR_MT_THREAD_HPP 
