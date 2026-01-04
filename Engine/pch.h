#pragma once

#include <algorithm>
#include <array>
#include <assert.h>
#include <bitset>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

#if ON_GNOTE_ENGINE
#if DYNAMIC_BUILD
#ifdef _MSC_VER
#define GNOTE_API __declspec(dllexport)
#else
#define GNOTE_API __attribute__((visibility("default")))
#endif
#else
#define GNOTE_API
#endif
#else
#if DYNAMIC_IMPORT
#ifdef _MSC_VER
#define GNOTE_API __declspec(dllimport)
#else
#define GNOTE_API
#endif
#else
#define GNOTE_API
#endif
#endif

#ifdef GNOTE_ENABLE_ASSERTS
#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#define EXPORT_FN __declspec(dllexport)
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#define EXPORT_FN
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#define EXPORT_FN
#endif
#define GNOTE_ASSERT(x, ...)                                                                                           \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                           \
            DEBUG_BREAK();                                                                                             \
        }                                                                                                              \
    }
#define GNOTE_CORE_ASSERT(x, ...)                                                                                      \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                      \
            DEBUG_BREAK();                                                                                             \
        }                                                                                                              \
    }
#else
#define GNOTE_ASSERT(x, ...)
#define GNOTE_CORE_ASSERT(x, ...)
#endif

#define GNOTE_EVENT_BIND(function) std::bind(&function, this, std::placeholders::_1)

#define DYNAMIC_CAST(value, type) std::dynamic_pointer_cast<type>(value)

namespace Gnote
{
template <typename T> using Ref = std::shared_ptr<T>;
template <typename T> using Scope = std::unique_ptr<T>;
} // namespace Gnote
