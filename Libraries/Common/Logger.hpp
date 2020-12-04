#ifndef LOGGER_HPP_
#define LOGGER_HPP_

enum LOG_LEVEL {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

class Logger
{
    Logger();
    ~Logger();

    static void Log(const char* msg, LOG_LEVEL level);
};

#endif // LOGGER_HPP_