#pragma once 

#include "Managed.hpp"
#include "Function.hpp"

namespace YAWN {
    class ThreadImpl : public NonCopyable {
    public:
        ThreadImpl(Function<void()> function);

        virtual ~ThreadImpl() = default;

    protected:
        Function<void()> _function;
    };

    class Thread : public Reference {
    public:
        Thread(Function<void()> function);

        ~Thread();

    private:
        ThreadImpl* _impl = nullptr;
    };
}

