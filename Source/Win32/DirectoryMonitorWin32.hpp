#pragma once 

#include <YAWN/DirectoryMonitor.hpp>

#include <Windows.h>

namespace YAWN {
    class DirectoryMonitorWin32 : public DirectoryMonitorImpl {
    public:
        DirectoryMonitorWin32(const String& path);

        ~DirectoryMonitorWin32();

        bool Poll() override;

    private:
        String _path;
        HANDLE _handle;
    };
}