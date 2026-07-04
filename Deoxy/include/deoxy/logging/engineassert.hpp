#pragma once

#include "log.hpp"
#include <cstdlib>
#include <fmt/format.h>

#ifdef DEOXY_DEBUG
    #define DEOXY_ASSERT(condition, ...)                                      \
        do {                                                                \
            if (!(condition)) {                                             \
                DEOXY_CRITICAL(                                               \
                    "Assertion failed in {}:{}\n{}",                        \
                    __FILE__,                                               \
                    __LINE__,                                               \
                    fmt::format(__VA_ARGS__)                                \
                );                                                          \
                std::abort();                                               \
            }                                                               \
        } while (false)
#else
    #define DEOXY_ASSERT(condition, ...)                                      \
        do {                                                                \
            (void)sizeof(condition);                                        \
        } while (false)
#endif