//
// Created by BLSMNL00E on 06/08/2022.
//

#include "Logger.h"

namespace logger {
    log_level_t Settings::log_level = log_level_t::debug;
    std::unordered_map<std::string, logger_ptr> registered_loggers = {};

    template<typename... Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::warn(fmt, args...);
    }

    template<typename... Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::critical(fmt, args...);
    }

    template<typename... Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::info(fmt, args...);
    }

    template<typename... Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::debug(fmt, args...);
    }

    template<typename... Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::error(fmt, args...);
    }

    template<typename... Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::trace(fmt, args...);
    }

    void stacktrace() {

    }

    [[maybe_unused]]
    log_level_t Settings::setLogLevel(log_level_t level) {
        Settings::log_level = level;
        return Settings::log_level;
    }

    bool Settings::registerLogger(const logger_ptr& logger) {
        if(Settings::registered_loggers.contains(logger->name())) {
            return false;
        }
        auto insertion_result = Settings::registered_loggers.emplace(logger->name(), logger);
        return insertion_result.second;
    }
}