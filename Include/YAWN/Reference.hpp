#pragma once 

#include "Core.hpp"

namespace YAWN {
    class Reference : public NonCopyable {
    public:
        Reference(const Reference&) = delete;
        Reference& operator=(const Reference&) = delete;

        virtual ~Reference() = default;

        void Retain();

        void Release();

        isize RefCount() const;

    protected:
        Reference() = default;

    private:
        isize _counter = 0;
    };
}
