#pragma once

#include "enginelog.hpp"
#include <cstdlib>

#ifdef DEOXY_DEBUG
    #define DEOXY_ASSERT(condition, ...)                                    \
        do {                                                               \
            if (!(condition)) {                                            \
                DEOXY_CRITICAL("Assertion failed: " __VA_ARGS__);          \
                std::abort();                                              \
            }                                                              \
        } while (false)
#else
    #define DEOXY_ASSERT(condition, ...) do { (void)sizeof(condition); } while (false)
#endif