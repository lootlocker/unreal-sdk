#pragma once

#if defined(__clang__)
    #define LL_IGNORE_DEPRECATED_START \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
    #define LL_IGNORE_DEPRECATED_END \
        _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
    #define LL_IGNORE_DEPRECATED_START \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
    #define LL_IGNORE_DEPRECATED_END \
        _Pragma("GCC diagnostic pop")
#else
    #define LL_IGNORE_DEPRECATED_START \
        __pragma(warning(push)) \
        __pragma(warning(disable : 4996))
    #define LL_IGNORE_DEPRECATED_END \
        __pragma(warning(pop))
#endif