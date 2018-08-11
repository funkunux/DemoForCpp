#ifndef DEMO_FOR_CPP_LOGGING_H
#define DEMO_FOR_CPP_LOGGING_H

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

class Logging
{
public:
    enum LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
    };

    static void Log(LogLevel loglevel, const char *path, const char *func, const int line, const char* format, ...)
    {
        if(loglevel < Logging::level) return;
        const char *file = strrchr((char *)path, '/');
        (!file) ? file = path : file += 1;
        printf("[%s:(%s:%d)] ", file, func, line);
        
        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }

    static LogLevel level;
};

Logging::LogLevel Logging::level = Logging::TRACE;

#define DEMO_TRACE(format, args...)     Logging::Log(Logging::TRACE, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_DEBUG(format, args...)     Logging::Log(Logging::DEBUG, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_INFO(format,  args...)     Logging::Log(Logging::INFO, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_WARN(format,  args...)     Logging::Log(Logging::WARN, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_ERROR(format, args...)     Logging::Log(Logging::ERROR, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_FATAL(format, args...)     Logging::Log(Logging::FATAL, __FILE__, __FUNCTION__, __LINE__, format, ##args)

#endif
