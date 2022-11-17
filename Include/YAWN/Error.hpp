#pragma once

#include "Logger.hpp"

#ifdef _MSC_VER
#	define YawnDebugBreak() __debugbreak()
#else
#	define YawnDebugBreak() __builtin_trap()
#endif

#ifdef _DEBUG
#	define Assert(expr, msg, ...) if (!(expr)) { YAWN::Logger::Log(msg, __VA_ARGS__); YawnDebugBreak(); } else ((void)0)
#   define CheckReturn(expr, msg, ...) do { if (!(expr)) { YAWN::Logger::Log(msg, __VA_ARGS__); return; } } while (0)
#   define CheckReturnValue(expr, value, msg, ...) if (!(expr)) { YAWN::Logger::Log(msg, __VA_ARGS__); return value; } else ((void)0)
#else
#	define Assert(...) ((void)0)
#   define CheckReturn(expr, ...) do { if (!(expr)) { return; } } while (0)
#   define CheckReturnValue(expr, value, ...) do { if (!(expr)) { return value; } } while (0)
#endif

