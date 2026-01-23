#pragma once
#include <pch.h>
#include "LoggerEntry.h"

namespace Gnote
{

class GNOTE_API Logger
{
  public:
    static void Init();
    static void Shutdown();

  private:
};
}; // namespace Gnote

#if _DEBUG
#define CORE_LOG_TRACE(...) Gnote::CoreTrace(__VA_ARGS__)
#define CORE_LOG_DEBUG(...) Gnote::CoreDebug(__VA_ARGS__)
#define CORE_LOG_INFO(...) Gnote::CoreInfo(__VA_ARGS__)
#define CORE_LOG_WARN(...) Gnote::CoreWarn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) Gnote::CoreError(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) Gnote::CoreCritical(__VA_ARGS__)

#define LOG_TRACE(...) Gnote::CoreTrace(__VA_ARGS__)
#define LOG_DEBUG(...) Gnote::CoreDebug(__VA_ARGS__)
#define LOG_INFO(...) Gnote::CoreInfo(__VA_ARGS__)
#define LOG_WARN(...) Gnote::CoreWarn(__VA_ARGS__)
#define LOG_ERROR(...) Gnote::CoreError(__VA_ARGS__)
#define LOG_CRITICAL(...) Gnote::CoreCritical(__VA_ARGS__)

#else
#define CORE_LOG_TRACE(...)
#define CORE_LOG_DEBUG(...)
#define CORE_LOG_INFO(...)
#define CORE_LOG_WARN(...)
#define CORE_LOG_ERROR(...)
#define CORE_LOG_CIRITICAL(...)

#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CIRITICAL(...)
#endif
