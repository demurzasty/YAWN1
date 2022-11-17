#pragma once 

#include "Array.hpp"

namespace YAWN {
    class String final {
        static constexpr usize MaxSmallStringLength = 22;

    public:
        String();
        String(const char* string);
        String(const char* string, usize size);

        String(const String& string);
        String(String&& string) noexcept;

        ~String();

        String& operator=(const String& string);
        String& operator=(String&& string) noexcept;

        bool operator<(const String& rhs) const;

        bool operator>(const String& ths) const;

        bool operator<=(const String& rhs) const;

        bool operator>=(const String& ths) const;

        bool operator==(const String& rhs) const;

        bool operator!=(const String& rhs) const;

        String operator+(const String& rhs) const;

        const char* CStr() const;

        usize Length() const;

        usize Hash() const;

        bool Empty() const;

    private:
        bool IsShort() const;

    private:
        struct Long {
            usize IsShort : 1;
            usize Length : sizeof(usize) * 8 - 1;
            char* Data;
        };

        struct Short {
            uint8 IsShort : 1;
            uint8 Length : 7;
            char Data[MaxSmallStringLength + 1];
        };

        union {
            Long _long;
            Short _short;
        };
    };
}