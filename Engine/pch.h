#pragma once

#include <algorithm>
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
#define GNOTE_API __attribute__((visibility)("default"))
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
#define GNOTE_ASSERT(x, ...)                                                   \
  {                                                                            \
    if (!(x)) {                                                                \
      LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                         \
      __debugbreak();                                                          \
    }                                                                          \
  }
#define GNOTE_CORE_ASSERT(x, ...)                                              \
  {                                                                            \
    if (!(x)) {                                                                \
      CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                    \
      __debugbreak();                                                          \
    }                                                                          \
  }
#else
#define GNOTE_ASSERT(x, ...)
#define GNOTE_CORE_ASSERT(x, ...)
#endif

#define GNOTE_EVENT_BIND(function)                                             \
  std::bind(&function, this, std::placeholders::_1)

#define DYNAMIC_CAST(value, type) std::dynamic_pointer_cast<type>(value)

namespace Gnote {
template <typename T> using Ref = std::shared_ptr<T>;
template <typename T> using Scope = std::unique_ptr<T>;
} // namespace Gnote
