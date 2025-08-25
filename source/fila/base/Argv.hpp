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
///   File: Argv.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_BASE_ARGV_HPP
#define _FILA_BASE_ARGV_HPP

#include "patrona/base/String.hpp"
#include "patrona/base/Array.hpp"

namespace fila {

typedef patrona::ArrayTImplements ArgvTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: ArgvT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 typename TSize = size_t, TSize VSize = PATRONA_ARRAY_DEFAULT_SIZE,
 class TString = patrona::StringT<TChar, TEnd, VEnd>,
 class TExtends = patrona::ArrayT<TChar*, TSize, VSize>,
 class TImplements = ArgvTImplements>

class _EXPORT_CLASS ArgvT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TString string_t;
    typedef TChar* chars_t;
    typedef TChar char_t;
    typedef TSize size_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ArgvT(const char_t** elements, size_t length): m_end(0) {
        if ((Append(elements, length))) {
            AppendEnd();
        }
    }
    ArgvT(const ArgvT& copy): m_end(0) {
        if ((Append(copy.Elements(), copy.Length()))) {
            AppendEnd();
        }
    }
    ArgvT(): m_end(0) {
    }
    virtual ~ArgvT() {
        Clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Assign(const char_t** elements, size_t length) {
        size_t count = 0;
        Clear();
        count = Append(elements, length);
        return count;
    }
    virtual size_t Append(const char_t** elements, size_t length) {
        size_t count = 0;
        if ((elements) && (length)) {
            for (size_t index = m_strings.Length(); count < length; ++count) {
                string_t s(elements[count]);
                chars_t chars = 0;
                if (0 < (m_strings.Append(&s, 1))) {
                    if ((chars = m_strings[index + count].Buffer())) {
                        if (0 < (Extends::Append(&chars, 1))) {
                            continue;
                        }
                    }
                }
                break;
            }
        }
        return count;
    }
    virtual size_t AppendEnd() {
        size_t count = Extends::Append(&m_end, 1);
        return count;
    }
    virtual size_t Clear() {
        size_t count = Extends::Clear();
        m_strings.Clear();
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef patrona::ArrayT<string_t, size_t, VSize> strings_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    chars_t m_end;
    strings_t m_strings;
};
typedef ArgvT<> Argv;

} // namespace fila 

#endif // _FILA_BASE_ARGV_HPP 
