//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_ABYSS_LOGGER_H
#define ABYSS_ABYSS_LOGGER_H

#include <spdlog/spdlog.h>
#include <memory>
#include <utility>
#include "abyss/logger/settings.h"
#include "abyss/logger/types.h"

namespace abyss::logger {
    class logger {
    private:
        raw_logger_ptr logger_;
        logging_format_t logging_format_;

        logger(raw_logger_ptr logger, logging_format_t logging_format) : logger_(std::move(logger)),
                                                                     logging_format_(logging_format) {}

        explicit logger(raw_logger_ptr logger) : logger_(std::move(logger)), logging_format_() {}

    public:
        static std::shared_ptr<logger> make(raw_logger_ptr logger, logging_format_t logging_format);

        static std::shared_ptr<logger> make(raw_logger_ptr logger);

        logger() = delete;

        explicit operator raw_logger_ptr() &;

        explicit operator logging_format_t() &;

        raw_logger_ptr get();

        /**
         * Displays logging time into log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> displayLogTime();

        /**
         * Hides logging time from log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> hideLogTime();

        /**
         * Displays the process id into log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> displayPid();

        /**
         * Hides the process id from log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> hidePid();

        /**
         * Displays the current thread id into log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> displayThreadId();

        /**
         * Hides the current thread id from log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> hideThreadId();

        /**
         * Displays the current logging level into log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> displayLoggingLevel();

        /**
         * Hides the current logging level from log records
         * @return Current logger instance
         */
        std::shared_ptr<logger> hideLoggingLevel();

        /**
         * Reset the logging format to the default value
         * @return Current logger instance
         */
        std::shared_ptr<logger> resetLoggingFormat();

        /**
         * Hide all additional formatting from log messages
         * @return Current logger instance
         */
        std::shared_ptr<logger> hideAllFromLogs();

        /**
         * Defines the default logger used when called
         * @code abyss::logger::info @endcode
         * and similar functions
         * @return Current logger instance
         */
        std::shared_ptr<logger> setAsDefaultLogger();

        /**
         * Set the log level for the provided logger and returns the current one
         * @param level Log level to set up for the provided logger channel
         * @return Logs back the newly defined log level
         */
        [[maybe_unused]]
        std::shared_ptr<logger> setLogLevel(log_level_t level);
    };
}

#endif //ABYSS_ABYSS_LOGGER_H
