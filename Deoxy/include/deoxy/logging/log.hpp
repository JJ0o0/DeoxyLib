#pragma once

#include "logger.hpp"

/**
 * @ingroup Logging
 * @brief Logs a trace message.
 */
#define APP_TRACE(...)    ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Trace, __VA_ARGS__)

/**
 * @ingroup Logging
 * @brief Logs an informational message.
 */
#define APP_INFO(...)     ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Info, __VA_ARGS__)

/**
 * @ingroup Logging
 * @brief Logs a warning message.
 */
#define APP_WARN(...)     ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Warn, __VA_ARGS__)

/**
 * @ingroup Logging
 * @brief Logs an error message.
 */
#define APP_ERROR(...)    ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Error, __VA_ARGS__)

/**
 * @ingroup Logging
 * @brief Logs a critical error message.
 */
#define APP_CRITICAL(...) ::Deoxy::Logging::Logger::LogClientFormat(::Deoxy::Logging::LogLevel::Critical, __VA_ARGS__)