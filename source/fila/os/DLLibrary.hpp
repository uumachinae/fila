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
///   File: DLLibrary.hpp
///
/// Author: $author$
///   Date: 12/25/2018
///////////////////////////////////////////////////////////////////////
#ifndef _FILA_OS_DLLIBRARY_HPP
#define _FILA_OS_DLLIBRARY_HPP

#include "fila/base/Base.hpp"

#define FILA_OS_DLLIBRARY_SYMBOL_(identifier) "" #identifier ""
#define FILA_OS_DLLIBRARY_SYMBOL(identifier) FILA_OS_DLLIBRARY_SYMBOL_(identifier)

#if defined(WINDOWS)
#define FILA_OS_DLLIBRARY_FILE_EXTENSION "dll"
#else // defined(WINDOWS)
#if defined(APPLEOS)
#define FILA_OS_DLLIBRARY_FILE_EXTENSION "dylib"
#else // defined(APPLEOS)
#define FILA_OS_DLLIBRARY_FILE_EXTENSION "so"
#endif // defined(APPLEOS)
#endif // defined(WINDOWS)

#define FILA_OS_DLLIBRARY_FILE_EXTENSION_SEPARATOR "."
#define FILA_OS_DLLIBRARY_FILE_DIRECTORY_SEPARATORS "/\\"

namespace fila {
namespace os {

typedef ImplementBase DLLibraryTImplements;
///////////////////////////////////////////////////////////////////////
///  Class: DLLibraryT
///////////////////////////////////////////////////////////////////////
template <class TImplements = DLLibraryTImplements>
class _EXPORT_CLASS DLLibraryT: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open
    (const char* fileName, bool resolve = true, bool global = false) {
        return false;
    }
    virtual bool Close() {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* GetAddress(const char* symbol) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* FileName(String& name, const char* fileName) const {
        if ((fileName)) {
            const char *fileExtensionSeparator = 0, *fileExtension = 0;

            if ((fileExtensionSeparator = this->FileExtensionSeparator())
                && (fileExtension = this->FileExtension())) {
                const char* extension = 0;

                name.assign(fileName);
                if (!(extension = HasFileExtension(name))) {
                    name.append(fileExtensionSeparator);
                    name.append(fileExtension);
                    fileName = name.chars();
                }
            }
        }
        return fileName;
    }
    virtual const char* HasFileExtension(String& name) const {
        ssize_t epos = 0;
        if (0 <= (epos = name.rfind(FileExtensionSeparator()))) {
            ssize_t spos = 0;
            if (0 > (spos = name.find_first_of(FileDirectorySeparators(), epos))) {
                return name.chars() + epos + 1;
            }
        }
        return 0;
    }
    virtual const char* FileExtension() const {
        return FILA_OS_DLLIBRARY_FILE_EXTENSION;
    }
    virtual const char* FileExtensionSeparator() const {
        return FILA_OS_DLLIBRARY_FILE_EXTENSION_SEPARATOR;
    }
    virtual const char* FileDirectorySeparators() const {
        return FILA_OS_DLLIBRARY_FILE_DIRECTORY_SEPARATORS;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef DLLibraryT<> DLLibrary;

} // namespace os
} // namespace fila 

#endif // _FILA_OS_DLLIBRARY_HPP 
