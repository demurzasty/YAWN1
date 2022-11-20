#pragma once 

#include "Core.hpp"
#include "String.hpp"

namespace YAWN {
    class DirectoryMonitorImpl : public NonCopyable {
    public:
        virtual ~DirectoryMonitorImpl() = default;

        virtual bool Poll() = 0;
    };

    class DirectoryMonitor : public NonCopyable {
    public:
        DirectoryMonitor(const String& path);

        ~DirectoryMonitor();

        bool Poll();

    private:
        DirectoryMonitorImpl* _impl = nullptr;
    };
}