#pragma once

#include <format>
#include <string_view>
#include <utility>

namespace Deoxy::Logging {
    enum class LogLevel {
        Trace,
        Info,
        Warn,
        Error,
        Critical
    };

    class Logger {
    public:
        static void Init();

        static void LogEngine(LogLevel level, std::string_view message);
        static void LogClient(LogLevel level, std::string_view message);

        template<typename... Args>
        static void LogEngineFormat(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
            LogEngine(level, std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void LogClientFormat(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
            LogClient(level, std::format(fmt, std::forward<Args>(args)...));
        }
    };
}