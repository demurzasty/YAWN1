#include <YAWN/DirectoryMonitor.hpp>

#ifdef _WIN32
#include "Win32/DirectoryMonitorWin32.hpp"
#endif

using namespace YAWN;

DirectoryMonitor::DirectoryMonitor(const String& path) {
#ifdef _WIN32
    _impl = new DirectoryMonitorWin32(path);
#endif
}

DirectoryMonitor::~DirectoryMonitor() {
    delete _impl;
}

bool DirectoryMonitor::Poll() {
    return _impl ? _impl->Poll() : false;
}
