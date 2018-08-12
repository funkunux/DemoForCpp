#ifndef __DEMO_FOR_CPP_LOGGING_H__
#define __DEMO_FOR_CPP_LOGGING_H__

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

    static void Log(LogLevel, const char *, const char *, const int, const char*, ...);
    static LogLevel level;
};

#define DEMO_TRACE(format, args...)     Logging::Log(Logging::TRACE, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_DEBUG(format, args...)     Logging::Log(Logging::DEBUG, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_INFO(format,  args...)     Logging::Log(Logging::INFO,  __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_WARN(format,  args...)     Logging::Log(Logging::WARN,  __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_ERROR(format, args...)     Logging::Log(Logging::ERROR, __FILE__, __FUNCTION__, __LINE__, format, ##args)
#define DEMO_FATAL(format, args...)     Logging::Log(Logging::FATAL, __FILE__, __FUNCTION__, __LINE__, format, ##args)

#endif
