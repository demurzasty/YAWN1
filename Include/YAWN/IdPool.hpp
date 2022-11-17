#pragma once 

#include "Array.hpp"

namespace YAWN {
    class IdPool : public NonCopyable {
    public:
        Id Acquire();

        void Dispose(Id id);

        bool IsValid(Id id) const;

    private:
        Array<Id> _pool;
        Id _disposed = None;
    };
}
