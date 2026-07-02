#pragma once

#include "logger.hpp"

#define APP_TRACE(...)    ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Trace, __VA_ARGS__)
#define APP_INFO(...)     ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Info, __VA_ARGS__)
#define APP_WARN(...)     ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Warn, __VA_ARGS__)
#define APP_ERROR(...)    ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Error, __VA_ARGS__)
#define APP_CRITICAL(...) ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Critical, __VA_ARGS__)