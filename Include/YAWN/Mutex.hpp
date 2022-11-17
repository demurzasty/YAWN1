#pragma once 

#include "Managed.hpp"

namespace YAWN {
    class MutexImpl : public NonCopyable {
    public:
        virtual ~MutexImpl() = default;

        virtual void Lock() = 0;

        virtual bool TryLock() = 0;

        virtual void Unlock() = 0;
    };

    class Mutex : public Reference {
    public:
        Mutex();

        ~Mutex();

        void Lock();

        bool TryLock();

        void Unlock();

    private:
        MutexImpl* _impl = nullptr;
    };

    class Lock : public NonCopyable {
    public:
        Lock(Mutex& mutex);

        ~Lock();

    private:
        Mutex& _mutex;
    };
}