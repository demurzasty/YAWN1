#pragma once 

#include "Core.hpp"

namespace YAWN {
    class Logger : public NonInstantiable {
    public:
        Logger() = delete;

        static void Log(const char* format, ...);
    };
}