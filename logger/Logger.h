//
// Created by BLSMNL00E on 06/08/2022.
//

#ifndef SPDLOG_SAMPLE_LOGGER_H
#define SPDLOG_SAMPLE_LOGGER_H

#include "logger_inl.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <unordered_map>
#include <fmt/format.h>

namespace logger {
    typedef spdlog::level::level_enum log_level_t;
    typedef std::shared_ptr<spdlog::logger> logger_ptr;


    class Settings {
    private:
        typedef std::shared_ptr<Settings> instance_t;
        static instance_t instance;

        log_level_t log_level;
        std::unordered_map<std::string, logger_ptr> registered_loggers = {};

        struct logging_format_t {
            bool logging_level = true;
            bool log_time = false;
            bool pid = false;
            bool thread_id = false;
        } logging_format;

        Settings();

        /**
         * Defines or update the current logging pattern
         */
        void setLogPattern();

    public:
        /**
         * Get the singleton instance
         * @return
         */
        static instance_t getInstance();

        /**
         * Globally set the log level and returns the current one
         * @param level
         * @return
         */
        [[maybe_unused]]
        log_level_t setLogLevel(log_level_t level);

        /**
         * Register a new instance of a logger and store it in memory for fast non-blocking retrieval.
         * Returns false if the logger name is already registered, otherwise returns true.
         * @param logger
         * @return
         */
        bool registerLogger(const logger_ptr &logger);

        /**
         * Create and register a new instance of a colored multi-threaded stdout logger
         * @param logger_name
         * @return
         */
        logger_ptr makeConsoleLogger(const std::string &logger_name);

        /**
         * Displays logging time into log records
         * @return
         */
        instance_t displayLogTime();

        /**
         * Hides logging time from log records
         * @return
         */
        instance_t hideLogTime();

        /**
         * Displays the process id into log records
         * @return
         */
        instance_t displayPid();

        /**
         * Hides the process id from log records
         * @return
         */
        instance_t hidePid();

        /**
         * Displays the current thread id into log records
         * @return
         */
        instance_t displayThreadId();

        /**
         * Hides the current thread id from log records
         * @return
         */
        instance_t hideThreadId();

        /**
         * Displays the current logging level into log records
         * @return
         */
        instance_t displayLoggingLevel();

        /**
         * Hides the current logging level from log records
         * @return
         */
        instance_t hideLoggingLevel();

        instance_t resetLoggingFormat();

        instance_t hideAllFromLogs();
    };
}

#endif //SPDLOG_SAMPLE_LOGGER_H
