#pragma once
#include "pch.h"
#include <print>
#include <format>
#include <fstream>
#include <source_location>
#include <filesystem>

namespace Gnote
{
enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERR,
    TRACE,
    CRITICAL
};

template <LogLevel L, typename... Args> struct GNOTE_API CorePrint
{
    CorePrint(std::format_string<Args...> fmt, Args &&...args,
              const std::source_location &location = std::source_location::current())
    {
        const char *c = "?";
        switch (L)
        {
        case LogLevel::DEBUG:
            c = "D";
            break;
        case LogLevel::ERR:
            c = "E";
            break;
        case LogLevel::INFO:
            c = "I";
            break;
        case LogLevel::WARN:
            c = "W";
            break;
        case LogLevel::TRACE:
            c = "T";
            break;
        case LogLevel::CRITICAL:
            c = "C";
            break;
        }

        auto userMessage = std::format(fmt, std::forward<Args>(args)...);

        auto fullMessage =
            std::format("[{}] [{}:{}] {}", c, std::filesystem::path(location.file_name()).filename().string(),
                        location.line(), userMessage);

        std::println("{}", fullMessage);
    }
};

template <LogLevel L = {}, class... Args> CorePrint(std::format_string<Args...>, Args &&...) -> CorePrint<L, Args...>;

template <class... Args> using CoreDebug = CorePrint<LogLevel::DEBUG, Args...>;
template <class... Args> using CoreInfo = CorePrint<LogLevel::INFO, Args...>;
template <class... Args> using CoreWarn = CorePrint<LogLevel::WARN, Args...>;
template <class... Args> using CoreError = CorePrint<LogLevel::ERR, Args...>;
template <class... Args> using CoreTrace = CorePrint<LogLevel::TRACE, Args...>;
template <class... Args> using CoreCritical = CorePrint<LogLevel::CRITICAL, Args...>;
class GNOTE_API LoggerEntry
{
  public:
    explicit LoggerEntry(const std::string &fileName) : outputFile(fileName, std::ios::app)
    {
        if (!outputFile)
        {
            std::terminate();
        }
    };

  private:
    std::ofstream outputFile;
};
} // namespace Gnote
