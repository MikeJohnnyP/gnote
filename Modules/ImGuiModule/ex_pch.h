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

#if ON_EXMODULE
#if DYNAMIC_BUILD
#ifdef _MSC_VER
#define GNOTE_EXMODULE __declspec(dllexport)
#else
#define GNOTE_EXMODULE __attribute__((visibility("default")))
#endif
#else
#define GNOTE_EXMODULE
#endif
#else
#if DYNAMIC_IMPORT
#ifdef _MSC_VER
#define GNOTE_EXMODULE __declspec(dllimport)
#else
#define GNOTE_EXMODULE
#endif
#else
#define GNOTE_EXMODULE
#endif
#endif

#ifdef GNOTE_EXMODULE_ENABLE_ASSERTS
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
#define GNOTE_EXMODULE_ASSERT(x, ...)                                          \
  {                                                                            \
    if (!(x)) {                                                                \
      LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                         \
      DEBUG_BREAK();                                                           \
    }                                                                          \
  }
#else
#define GNOTE_EXMODULE_ASSERT(x, ...)
#endif
