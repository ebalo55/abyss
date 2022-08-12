//
// Created by ebalo on 12/08/22.
//

#include <utility>

#include "abyss/logger/abyss_logger.h"

namespace abyss::logger {
    logger::operator raw_logger_ptr() & {
        return this->logger_;
    }

    logger::operator logging_format_t() & {
        return this->logging_format_;
    }

    std::shared_ptr<logger> logger::make(raw_logger_ptr logger, logging_format_t logging_format) {
        return std::shared_ptr<abyss::logger::logger>(
                new abyss::logger::logger(
                        std::move(logger),
                        logging_format
                )
        );
    }

    std::shared_ptr<logger> logger::make(raw_logger_ptr logger) {
        return std::shared_ptr<abyss::logger::logger>(
                new abyss::logger::logger(
                        std::move(logger)
                )
        );
    }

    std::shared_ptr<logger> logger::displayLogTime() {
        settings::getInstance()->displayLogTime(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::hideLogTime() {
        settings::getInstance()->hideLogTime(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::displayPid() {
        settings::getInstance()->displayPid(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::hidePid() {
        settings::getInstance()->hidePid(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::displayThreadId() {
        settings::getInstance()->displayThreadId(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::hideThreadId() {
        settings::getInstance()->hideThreadId(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::displayLoggingLevel() {
        settings::getInstance()->displayLoggingLevel(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::hideLoggingLevel() {
        settings::getInstance()->hideLoggingLevel(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::resetLoggingFormat() {
        settings::getInstance()->resetLoggingFormat(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::hideAllFromLogs() {
        settings::getInstance()->hideAllFromLogs(this->logger_, this->logging_format_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::setAsDefaultLogger() {
        settings::getInstance()->setDefaultLogger(this->logger_);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    std::shared_ptr<logger> logger::setLogLevel(log_level_t level) {
        settings::getInstance()->setLogLevel(this->logger_, level);
        return std::shared_ptr<abyss::logger::logger>(this);
    }

    raw_logger_ptr logger::get() {
        return logger_;
    }
}