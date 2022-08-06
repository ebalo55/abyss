//
// Created by BLSMNL00E on 06/08/2022.
//

#include "Logger.h"

namespace logger {
    // initialize the 'Settings' class static variables
    Settings::instance_t Settings::instance = nullptr;

    Settings::Settings() {
        this->setLogLevel(log_level_t::trace);
        this->setLogPattern();
    }

    Settings::instance_t Settings::getInstance() {
        if (instance == nullptr) {
            instance = std::shared_ptr<Settings>(new Settings());
        }
        return instance;
    }

    [[maybe_unused]]
    log_level_t Settings::setLogLevel(log_level_t level) {
        Settings::log_level = level;
        spdlog::set_level(level);
        return Settings::log_level;
    }

    bool Settings::registerLogger(const logger_ptr &logger) {
        if (Settings::registered_loggers.contains(logger->name())) {
            return false;
        }
        auto insertion_result = Settings::registered_loggers.emplace(logger->name(), logger);
        return insertion_result.second;
    }

    logger_ptr Settings::makeConsoleLogger(const std::string &logger_name) {
        logger_ptr logger = spdlog::stdout_color_mt(logger_name);
        if (Settings::registerLogger(logger)) {
            return logger;
        }
        return nullptr;
    }

    void Settings::setLogPattern() {
        spdlog::set_pattern(
                fmt::format(
                        "{}{}{}{}{}%v",
                        logging_format.logging_level ? "[%^%l%$]" : "",
                        logging_format.log_time ? " [%Y-%m-%d %H:%M:%S.%e %z]" : "",
                        logging_format.pid ? " [pid %P]" : "",
                        logging_format.thread_id ? " [thread %t]" : "",
                        logging_format.logging_level || logging_format.log_time || logging_format.pid ||
                        logging_format.thread_id ? " " : ""
                )
        );
    }

    Settings::instance_t Settings::displayLogTime() {
        logging_format.log_time = true;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::hideLogTime() {
        logging_format.log_time = false;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::displayPid() {
        logging_format.pid = true;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::hidePid() {
        logging_format.pid = false;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::displayThreadId() {
        logging_format.thread_id = true;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::hideThreadId() {
        logging_format.thread_id = false;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::displayLoggingLevel() {
        logging_format.logging_level = true;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::hideLoggingLevel() {
        logging_format.logging_level = false;

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::resetLoggingFormat() {
        logging_format = {
                .logging_level = true,
                .log_time = false,
                .pid = false,
                .thread_id = false,
        };

        this->setLogPattern();
        return instance;
    }

    Settings::instance_t Settings::hideAllFromLogs() {
        logging_format = {false, false, false, false};

        this->setLogPattern();
        return instance;
    }
}