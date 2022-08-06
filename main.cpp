#include "logger/Logger.h"

void logTestMessages(int p) {
    logger::trace("This is a trace text with a parameter ({})", p);
    logger::debug("This is a debug text with a parameter ({})", p);
    logger::info("This is a info text with a parameter ({})", p);
    logger::warn("This is a info text with a parameter ({})", p);
    logger::error("This is a info text with a parameter ({})", p);
    logger::critical("This is a info text with a parameter ({})", p);
}

int main() {
    auto logger_settings = logger::Settings::getInstance();

    // change log pattern
    logger_settings->hideAllFromLogs();
    logger::info("{0:>^5} FORMATTING TESTS {0:<^5}", "");
    logger_settings->resetLoggingFormat();

    // simple log
    logTestMessages(1);

    // log with time
    logger_settings->displayLogTime();
    logTestMessages(2);
    logger_settings->resetLoggingFormat();

    // log with pid
    logger_settings->displayPid();
    logTestMessages(3);
    logger_settings->resetLoggingFormat();

    // log with thread id
    logger_settings->displayThreadId();
    logTestMessages(4);
    logger_settings->resetLoggingFormat();

    // log with thread id + pid
    logger_settings->displayThreadId()->displayPid();
    logTestMessages(5);

    // log with time + previous state
    logger_settings->displayLogTime();
    logTestMessages(6);

    // log with previous state - pid & thread id
    logger_settings->hidePid()->hideThreadId();
    logTestMessages(7);

    // log with previous state and higher threshold
    logger_settings->setLogLevel(logger::log_level_t::warn);
    logTestMessages(8);

    return 0;
}
