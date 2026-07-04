#pragma once

#include "log.hpp"
#include <cstdlib>
#include <fmt/format.h>

#ifdef DEOXY_DEBUG
    /**
     * @ingroup Logging
     * @brief Verifies that a condition is true.
     *
     * If the condition evaluates to false, an error message is logged
     * and the application is terminated.
     *
     * Assertions are only enabled in debug builds.
     *
     * @param condition Condition to evaluate.
     * @param ... Format string and optional arguments describing the failure.
     *
     * @note A message is required when using this macro.
     */
    #define APP_ASSERT(condition, ...)                                      \
        do {                                                                \
            if (!(condition)) {                                             \
                APP_CRITICAL(                                               \
                    "Assertion failed in {}:{}\n{}",                        \
                    __FILE__,                                               \
                    __LINE__,                                               \
                    fmt::format(__VA_ARGS__)                                \
                );                                                          \
                std::abort();                                               \
            }                                                               \
        } while (false)
#else
    #define APP_ASSERT(condition, ...)                                      \
        do {                                                                \
            (void)sizeof(condition);                                        \
        } while (false)
#endif