#include "Logger.h"

int main() {
    logger::info("Welcome to spdlog!");
    logger::error("Some error message with arg: {}", 1);

    logger::warn("Easy padding in numbers like {:08d}", 12);
    logger::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    logger::info("Support for floats {:03.2f}", 1.23456);
    logger::info("Positional args are {1} {0}..", "too", "supported");
    logger::info("{:<30}", "left aligned");

    auto current_log_level = logger::Settings::setLogLevel(spdlog::level::info);
    assert(current_log_level == spdlog::level::info); // Set global log level to info
    logger::info("This message should be displayed..");
    logger::trace("This should not be displayed");

    // change log pattern
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%^%l%$] [pid %P] [thread %t] %v");
    logger::Settings::setLogLevel(spdlog::level::debug); // Set global log level to info
    logger::debug("This message should be displayed..");

    return 0;
}
