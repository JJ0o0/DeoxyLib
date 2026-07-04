#pragma once

#include <format>
#include <string_view>
#include <utility>

namespace Deoxy::Logging {
    /**
     * @ingroup Logging
     * @brief Severity levels used by the logging system.
     */
    enum class LogLevel {
        /// Diagnostic information useful during development.
        Trace,

        /// General informational messages.
        Info,

        /// Non-fatal warnings.
        Warn,

        /// Errors that prevent an operation from succeeding.
        Error,

        /// Critical errors that may terminate the application.
        Critical
    };

    /**
     * @ingroup Logging
     * @brief Static logging utility.
     *
     * Provides functions for logging engine and application messages
     * with different severity levels.
     */
    class Logger {
    public:
        /**
         * @brief Initializes the logging system.
         *
         * Called internally by the engine during startup.
         */
        static void Init();

        /**
         * @brief Logs a message from the engine.
         *
         * @param level Message severity.
         * @param message Message to log.
         */
        static void LogEngine(LogLevel level, std::string_view message);

        /**
         * @brief Logs a message from the application.
         *
         * @param level Message severity.
         * @param message Message to log.
        */
        static void LogClient(LogLevel level, std::string_view message);

        /**
         * @brief Formats and logs an engine message.
         *
         * @param level Message severity.
         * @param fmt Format string.
         * @param args Format arguments.
         */
        template<typename... Args>
        static void LogEngineFormat(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
            LogEngine(level, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Formats and logs an application message.
         *
         * @param level Message severity.
         * @param fmt Format string.
         * @param args Format arguments.
         */
        template<typename... Args>
        static void LogClientFormat(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
            LogClient(level, std::format(fmt, std::forward<Args>(args)...));
        }
    };
}