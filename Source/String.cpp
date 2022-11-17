#include <YAWN/String.hpp>
#include <YAWN/FNV1a.hpp>

#include <string.h>

using namespace YAWN;

String::String() {
    _short.IsShort = 1;
    _short.Length = 0;
}

String::String(const char* string) {
    const usize size = strlen(string);
    if (size > MaxSmallStringLength) {
        _long.IsShort = 0;
        _long.Length = size;
        _long.Data = new char[size + 1];
        memcpy(_long.Data, string, size + 1);
    } else {
        _short.IsShort = 1;
        _short.Length = uint8(size);
        memcpy(_short.Data, string, size + 1);
    }
}

String::String(const char* string, usize size) {
    if (size > MaxSmallStringLength) {
        _long.IsShort = 0;
        _long.Length = size;
        _long.Data = new char[size + 1];
        memcpy(_long.Data, string, size);
        _long.Data[size] = 0;
    } else {
        _short.IsShort = 1;
        _short.Length = uint8(size);
        memcpy(_short.Data, string, size);
        _short.Data[size] = 0;
    }
}

String::String(const String& string) {
    if (!string.IsShort()) {
        _long.IsShort = 0;
        _long.Length = string._long.Length;
        _long.Data = new char[_long.Length + 1];
        memcpy(_long.Data, string._long.Data, _long.Length + 1);
    } else {
        _short.IsShort = 1;
        _short.Length = string._short.Length;
        memcpy(_short.Data, string._short.Data, _short.Length + 1);
    }
}

String::String(String&& string) noexcept {
    if (!string.IsShort()) {
        _long = string._long;
        string._short.IsShort = 1;
        string._short.Length = 0;
    } else {
        _short = string._short;
        string._short.Length = 0;
    }
}

String::~String() {
    if (!IsShort()) {
        delete[] _long.Data;
    }
}

String& String::operator=(const String& string) {
    if (!IsShort()) {
        delete[] _long.Data;
    }

    if (!string.IsShort()) {
        _long.IsShort = 0;
        _long.Length = string._long.Length;
        _long.Data = new char[_long.Length + 1];
        memcpy(_long.Data, string._long.Data, _long.Length + 1);
    } else {
        _short.IsShort = 1;
        _short.Length = string._short.Length;
        memcpy(_short.Data, string._short.Data, _short.Length + 1);
    }

    return *this;
}

String& String::operator=(String&& string) noexcept {
    if (!IsShort()) {
        delete[] _long.Data;
    }

    if (!string.IsShort()) {
        _long = string._long;
        string._short.IsShort = 1;
        string._short.Length = 0;
    } else {
        _short = string._short;
        string._short.Length = 0;
    }

    return *this;
}

bool String::operator<(const String& rhs) const {
    return strcmp(CStr(), rhs.CStr()) < 0;
}

bool String::operator>(const String& rhs) const {
    return strcmp(CStr(), rhs.CStr()) > 0;
}

bool String::operator<=(const String& rhs) const {
    return strcmp(CStr(), rhs.CStr()) <= 0;
}

bool String::operator>=(const String& rhs) const {
    return strcmp(CStr(), rhs.CStr()) >= 0;
}

bool String::operator==(const String& rhs) const {
    return strcmp(CStr(), rhs.CStr()) == 0;
}

bool String::operator!=(const String& rhs) const {
    return strcmp(CStr(), rhs.CStr()) != 0;
}

const char* String::CStr() const {
    if (!Empty()) {
        return IsShort() ? _short.Data : _long.Data;
    }
    return "";
}

usize String::Length() const {
    return IsShort() ? _short.Length : _long.Length;
}

usize String::Hash() const {
    return FNV1a(CStr(), Length());
}

bool String::Empty() const {
    return Length() == 0;
}

String String::operator+(const String& rhs) const {
    const usize concatedSize = Length() + rhs.Length();

    Array<char> concated(concatedSize + 1);
    memcpy(concated.Data(), CStr(), Length());
    memcpy(concated.Data() + Length(), rhs.CStr(), rhs.Length());
    concated[concatedSize] = '\0';

    return concated.Data();
}

bool String::IsShort() const {
    return _short.IsShort;
}
