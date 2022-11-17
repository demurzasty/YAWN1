#include <YAWN/Logger.hpp>

#include <stdio.h>
#include <stdarg.h>

using namespace YAWN;

void Logger::Log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
