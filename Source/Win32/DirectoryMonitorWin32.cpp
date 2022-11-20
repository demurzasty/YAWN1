#include "DirectoryMonitorWin32.hpp"

using namespace YAWN;

DirectoryMonitorWin32::DirectoryMonitorWin32(const String& path)
    : _path(path) {
    _handle = FindFirstChangeNotification(path.CStr(), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE);
}

DirectoryMonitorWin32::~DirectoryMonitorWin32() {
    FindCloseChangeNotification(_handle);
}

bool DirectoryMonitorWin32::Poll() {
    bool changed = false;
	while (true) {
		DWORD result = WaitForSingleObject(_handle, 0);
		if (result == WAIT_OBJECT_0) {
			changed = true;
			FindNextChangeNotification(_handle);
		} else if (result == WAIT_TIMEOUT) {
			break;
		} else if (result == WAIT_FAILED || result == WAIT_ABANDONED) {
			return false;
		}
	}
	return changed;
}
