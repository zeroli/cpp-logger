#include "logger.h"

using namespace logger;

int main()
{
    Logger::instance()->open("test.log");
    Logger::instance()->level(Logger::WARN);

    debug("hello logger: %d", 1);
    info("hello logger: %d", 2);
    warn("hello logger: %d", 3);
    error("hello logger: %d", 4);
    fatal("hello logger: %d", 5);
}
