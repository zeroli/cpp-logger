#include "logger.h"

#include <cstdarg>
#include <ctime>

namespace logger {
const char* Logger::s_levels[Level::NUM] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
};

Logger::Logger()
{

}
Logger::~Logger()
{
    close();
}

void Logger::open(const std::string& filename)
{
    close();

    fout_.open(filename, std::ios::app);
    if (!fout_.is_open()) {
        throw std::logic_error("failed to open file for logging: " + filename);
    }

    //auto len = fout_.seekp(std::ios::end);

}

void Logger::close()
{
    if (fout_.is_open()) {
        fout_.close();
    }
}

void Logger::log(Level level, const char* file, int line, const char* format, ...)
{
    if (!allow_log(level)) {
        return;
    }
    {  // print: "timestamp [LEVEL][FILE:LINE]"
        time_t curtime = time(nullptr);
        struct tm curtm;
        localtime_s(&curtm, &curtime);
        char timestamp[32];
        strftime(timestamp, sizeof timestamp, "%Y-%m-%d.%H:%M:%S", &curtm);
        char prefix[256];
        snprintf(prefix, sizeof prefix, "%s [%s][%s:%d]", timestamp, s_levels[level], file, line);
        fout_ << prefix;
    }
    {  // print: fromatted log message
        va_list ap;
        va_start(ap, format);
        auto size = vsnprintf(nullptr, 0, format, ap);
        va_end(ap);
        if (size > 0) {
            va_start(ap, format);
            char* buf = new char[size+=1];
            vsnprintf(buf, size, format, ap);
            fout_ << buf;
            delete []buf;
        }
    }
    fout_ << "\n";
    fout_.flush();
}

}  // namespace logger
