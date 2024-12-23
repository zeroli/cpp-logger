#pragma once

#include <string>
#include <fstream>

namespace logger {

class Logger {
public:
    enum Level {
      DEBUG = 0,
      INFO,
      WARN,
      ERROR,
      FATAL,
      NUM,
    };

    /// singleton instance
    static Logger* instance() {
        static Logger s_logger;
        return &s_logger;
    }

    void open(const std::string& filename);
    void close();

    void log(Level level, const char* file, int line, const char* format, ...);

    Level level() const { return level_; }
    void level(Level level) { level_ = level; }

    bool allow_log(Level level) const {
        return level >= level_;
    }
private:
    Logger();
    ~Logger();
private:
    static const char* s_levels[Level::NUM];
    std::ofstream fout_;

    // current level configuration
    // any log whose level >= `level_` will be printed, others dropped
    Level level_ {Level::DEBUG};
};

#define debug(format, ...) \
    if (logger::Logger::instance()->allow_log(logger::Logger::Level::DEBUG)) \
        logger::Logger::instance()->log( \
            logger::Logger::Level::DEBUG, \
            __FILE__, __LINE__, \
            format, ##__VA_ARGS__ \
            )
///###

#define info(format, ...) \
    if (logger::Logger::instance()->allow_log(logger::Logger::Level::INFO)) \
        logger::Logger::instance()->log( \
            logger::Logger::Level::INFO, \
            __FILE__, __LINE__, \
            format, ##__VA_ARGS__ \
            )
///###

#define warn(format, ...) \
    if (logger::Logger::instance()->allow_log(logger::Logger::Level::WARN)) \
        logger::Logger::instance()->log( \
            logger::Logger::Level::WARN, \
            __FILE__, __LINE__, \
            format, ##__VA_ARGS__ \
            )
///###

#define error(format, ...) \
    if (logger::Logger::instance()->allow_log(logger::Logger::Level::ERROR)) \
        logger::Logger::instance()->log( \
            logger::Logger::Level::ERROR, \
            __FILE__, __LINE__, \
            format, ##__VA_ARGS__ \
            )
///###

#define fatal(format, ...) \
    if (logger::Logger::instance()->allow_log(logger::Logger::Level::FATAL)) \
        logger::Logger::instance()->log( \
            logger::Logger::Level::FATAL, \
            __FILE__, __LINE__, \
            format, ##__VA_ARGS__ \
            )
///###

}  // namespace logger
