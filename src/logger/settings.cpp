//
// Created by ebalo on 06/08/2022.
//

#include "abyss/logger/settings.h"

namespace abyss::logger {
    // initialize the 'Settings' class static variables
    std::shared_ptr<settings> settings::instance_ = nullptr;

    settings::settings() {
        this->setLogLevel(log_level_t::trace);
        this->setLogPattern();
    }

    std::shared_ptr<settings> settings::getInstance() {
        [[unlikely]]
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<settings>(new settings());
        }
        return instance_;
    }

    [[maybe_unused]]
    std::shared_ptr<settings> settings::setLogLevel(log_level_t level) {
        settings::log_level_ = level;
        spdlog::set_level(level);
        return instance_;
    }

    void settings::setLogPattern() const {
        this->setLogPattern(spdlog::default_logger(), this->logging_format_);
    }

    void settings::setLogPattern(const raw_logger_ptr &logger, const logging_format_t &format) const {
        logger->set_pattern(
                fmt::format(
                        "{}{}{}{}{}%v",
                        logging_format_.logging_level ? "[%^%l%$]" : "",
                        logging_format_.log_time ? " [%Y-%m-%d %H:%M:%S.%e %z]" : "",
                        logging_format_.pid ? " [pid %P]" : "",
                        logging_format_.thread_id ? " [thread %t]" : "",
                        logging_format_.logging_level || logging_format_.log_time || logging_format_.pid ||
                        logging_format_.thread_id ? " " : ""
                )
        );
    }

    std::shared_ptr<settings> settings::displayLogTime() {
        logging_format_.log_time = true;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::hideLogTime() {
        logging_format_.log_time = false;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::displayPid() {
        logging_format_.pid = true;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::hidePid() {
        logging_format_.pid = false;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::displayThreadId() {
        logging_format_.thread_id = true;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::hideThreadId() {
        logging_format_.thread_id = false;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::displayLoggingLevel() {
        logging_format_.logging_level = true;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::hideLoggingLevel() {
        logging_format_.logging_level = false;

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::resetLoggingFormat() {
        logging_format_ = {
                .logging_level = true,
                .log_time = false,
                .pid = false,
                .thread_id = false,
        };

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::hideAllFromLogs() {
        logging_format_ = {false, false, false, false};

        this->setLogPattern();
        return instance_;
    }

    std::shared_ptr<settings> settings::setDefaultLogger(const raw_logger_ptr &logger) {
        spdlog::set_default_logger(logger);
        return instance_;
    }

    std::shared_ptr<settings> settings::setLogLevel(const raw_logger_ptr &logger, log_level_t level) {
        logger->set_level(level);
        return instance_;
    }

    std::shared_ptr<settings> settings::displayLogTime(const raw_logger_ptr &logger, logging_format_t &format) {
        format.log_time = true;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::hideLogTime(const raw_logger_ptr &logger, logging_format_t &format) {
        format.log_time = false;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::displayPid(const raw_logger_ptr &logger, logging_format_t &format) {
        format.pid = true;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::hidePid(const raw_logger_ptr &logger, logging_format_t &format) {
        format.pid = false;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::displayThreadId(const raw_logger_ptr &logger, logging_format_t &format) {
        format.thread_id = true;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::hideThreadId(const raw_logger_ptr &logger, logging_format_t &format) {
        format.thread_id = false;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::displayLoggingLevel(const raw_logger_ptr &logger, logging_format_t &format) {
        format.logging_level = true;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::hideLoggingLevel(const raw_logger_ptr &logger, logging_format_t &format) {
        format.logging_level = false;

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::resetLoggingFormat(const raw_logger_ptr &logger, logging_format_t &format) {
        format = {
                .logging_level = true,
                .log_time = false,
                .pid = false,
                .thread_id = false,
        };

        this->setLogPattern(logger, format);
        return instance_;
    }

    std::shared_ptr<settings> settings::hideAllFromLogs(const raw_logger_ptr &logger, logging_format_t &format) {
        format = {false, false, false, false};

        this->setLogPattern(logger, format);
        return instance_;
    }
}