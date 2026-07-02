#include <deoxy/logging/logger.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <memory>
#include <vector>

namespace Deoxy::Logging {
    static std::shared_ptr<spdlog::logger> s_engineLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;

    void Logger::Init() {
        std::filesystem::create_directories("Logs");

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/Deoxy.log", true);

        std::vector<spdlog::sink_ptr> sinks {
            consoleSink,
            fileSink
        };

        s_engineLogger = std::make_shared<spdlog::logger>("Deoxy", sinks.begin(), sinks.end());
        s_clientLogger = std::make_shared<spdlog::logger>("App", sinks.begin(), sinks.end());

        spdlog::register_logger(s_engineLogger);
        spdlog::register_logger(s_clientLogger);

        s_engineLogger->set_level(spdlog::level::trace);
        s_clientLogger->set_level(spdlog::level::trace);

        s_engineLogger->flush_on(spdlog::level::trace);
        s_clientLogger->flush_on(spdlog::level::trace);

        consoleSink->set_pattern("%^[%T] %n: %v%$");
        fileSink->set_pattern("[%Y-%m-%d %T] [%l] %n: %v");
    }


    void Logger::LogEngine(LogLevel level, std::string_view message) {
        switch (level) {
            case LogLevel::Trace:    s_engineLogger->trace(message); break;
            case LogLevel::Info:     s_engineLogger->info(message); break;
            case LogLevel::Warn:     s_engineLogger->warn(message); break;
            case LogLevel::Error:    s_engineLogger->error(message); break;
            case LogLevel::Critical: s_engineLogger->critical(message); break;
        }
    }

    void Logger::LogClient(LogLevel level, std::string_view message) {
        switch (level) {
            case LogLevel::Trace:    s_clientLogger->trace(message); break;
            case LogLevel::Info:     s_clientLogger->info(message); break;
            case LogLevel::Warn:     s_clientLogger->warn(message); break;
            case LogLevel::Error:    s_clientLogger->error(message); break;
            case LogLevel::Critical: s_clientLogger->critical(message); break;
        }
    }
}