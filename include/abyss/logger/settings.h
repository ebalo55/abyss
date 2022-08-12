//
// Created by ebalo on 06/08/2022.
//

#ifndef SPDLOG_SAMPLE_SETTINGS_H
#define SPDLOG_SAMPLE_SETTINGS_H

#include "abyss/logger/types.h"
#include <spdlog/spdlog.h>
#include <memory>
#include <unordered_map>
#include <fmt/format.h>

namespace abyss::logger {
    /**
     * @author ebalo
     */
    class settings {
    private:
        static std::shared_ptr<settings> instance_;
        log_level_t log_level_;
        logging_format_t logging_format_;

        settings();

        /**
         * Defines or update the current logging pattern
         */
        void setLogPattern() const;

        /**
         * Defines or update the current logging pattern
         */
        void setLogPattern(const raw_logger_ptr &logger, const logging_format_t &format) const;

    public:
        /**
         * Get or create the singleton instance
         * @return Settings unique instance
         */
        static std::shared_ptr<settings> getInstance();

        /**
         * Globally set the default log level and returns the current one
         * @param level Log level to set up for the default channel
         * @return Logs back the newly defined log level
         */
        [[maybe_unused]]
        std::shared_ptr<settings> setLogLevel(log_level_t level);

        /**
         * Set the log level for the provided logger and returns the current one
         * @param logger Logger instance to set the log level on
         * @param level Log level to set up for the provided logger channel
         * @return Logs back the newly defined log level
         */
        [[maybe_unused]]
        std::shared_ptr<settings> setLogLevel(const raw_logger_ptr &logger, log_level_t level);

        /**
         * Displays logging time into log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayLogTime();

        /**
         * Displays logging time into log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayLogTime(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Hides logging time from log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideLogTime();

        /**
         * Hides logging time from log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideLogTime(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Displays the process id into log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayPid();

        /**
         * Displays the process id into log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayPid(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Hides the process id from log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hidePid();

        /**
         * Hides the process id from log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hidePid(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Displays the current thread id into log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayThreadId();

        /**
         * Displays the current thread id into log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayThreadId(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Hides the current thread id from log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideThreadId();

        /**
         * Hides the current thread id from log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideThreadId(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Displays the current logging level into log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayLoggingLevel();

        /**
         * Displays the current logging level into log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> displayLoggingLevel(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Hides the current logging level from log records
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideLoggingLevel();

        /**
         * Hides the current logging level from log records
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideLoggingLevel(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Reset the logging format to the default value
         * @return Settings unique instance
         */
        std::shared_ptr<settings> resetLoggingFormat();

        /**
         * Reset the logging format to the default value
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> resetLoggingFormat(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Hide all additional formatting from log messages
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideAllFromLogs();

        /**
         * Hide all additional formatting from log messages
         * @param logger Logger instance to set the format on
         * @param format Logger instance format reference where format data are stored
         * @return Settings unique instance
         */
        std::shared_ptr<settings> hideAllFromLogs(const raw_logger_ptr &logger, logging_format_t &format);

        /**
         * Defines the default logger used when called
         * @code abyss::logger::info @endcode
         * and similar functions
         * @param logger Logger instance to use as default logger, usually generated via
         * @code abyss::logger::generator @endcode instance methods or generator helpers like
         * @code abyss::logger::make_stdout_logger @endcode
         * @return Settings unique instance
         */
        std::shared_ptr<settings> setDefaultLogger(const raw_logger_ptr &logger);
    };
}

#endif //SPDLOG_SAMPLE_SETTINGS_H
