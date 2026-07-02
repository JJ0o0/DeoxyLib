#pragma once

#include "logger.hpp"

#define DEOXY_TRACE(...)    ::Deoxy::Logging::Logger::LogEngineFormat(::Deoxy::Logging::LogLevel::Trace, __VA_ARGS__)
#define DEOXY_INFO(...)     ::Deoxy::Logging::Logger::LogEngineFormat(::Deoxy::Logging::LogLevel::Info, __VA_ARGS__)
#define DEOXY_WARN(...)     ::Deoxy::Logging::Logger::LogEngineFormat(::Deoxy::Logging::LogLevel::Warn, __VA_ARGS__)
#define DEOXY_ERROR(...)    ::Deoxy::Logging::Logger::LogEngineFormat(::Deoxy::Logging::LogLevel::Error, __VA_ARGS__)
#define DEOXY_CRITICAL(...) ::Deoxy::Logging::Logger::LogEngineFormat(::Deoxy::Logging::LogLevel::Critical, __VA_ARGS__)