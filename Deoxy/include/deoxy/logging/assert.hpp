#pragma once

#include "log.hpp"
#include <cstdlib>

#ifdef DEOXY_DEBUG
    #define APP_ASSERT(condition, ...)                                      \
        do {                                                               \
            if (!(condition)) {                                            \
                APP_CRITICAL("Assertion failed: " __VA_ARGS__);            \
                std::abort();                                              \
            }                                                              \
        } while (false)
#else
    #define APP_ASSERT(condition, ...) do { (void)sizeof(condition); } while (false)
#endif