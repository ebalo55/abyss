//
// Created by BLSMNL00E on 06/08/2022.
//

#ifndef SPDLOG_SAMPLE_LOGGER_H
#define SPDLOG_SAMPLE_LOGGER_H

#include <spdlog/spdlog.h>
#include <memory>
#include <unordered_map>

namespace logger {
    typedef spdlog::level::level_enum log_level_t;
    typedef std::shared_ptr<spdlog::logger> logger_ptr;

    template<typename ...Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&... args);

    template<typename ...Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&... args);

    template<typename ...Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&... args);

    template<typename ...Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&... args);

    template<typename ...Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&... args);

    template<typename ...Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&... args);

    void stacktrace();

    class Settings {
    private:
        static log_level_t log_level;
        static std::unordered_map<std::string, logger_ptr> registered_loggers;
    public:
        /**
         * Globally set the log level and returns the current one
         * @param level
         * @return
         */
        [[maybe_unused]]
        static log_level_t setLogLevel(log_level_t level);

        /**
         * Register a new instance of a logger and store it in memory for fast non-blocking retrieval.
         * Returns false if the logger name is already registered, otherwise returns true.
         * @param logger
         * @return
         */
        static bool registerLogger(const logger_ptr& logger);
    };
}

#endif //SPDLOG_SAMPLE_LOGGER_H
