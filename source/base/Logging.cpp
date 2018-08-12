#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "Logging.h"

Logging::LogLevel Logging::level = Logging::TRACE;

void Logging::Log(Logging::LogLevel loglevel, const char *path, const char *func, const int line, const char* format, ...)
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

