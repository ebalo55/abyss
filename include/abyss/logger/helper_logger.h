//
// Created by ebalo on 06/08/2022.
//

#ifndef SPDLOG_SAMPLE_HELPER_LOGGER_H
#define SPDLOG_SAMPLE_HELPER_LOGGER_H

#include <spdlog/spdlog.h>

namespace abyss::logger {
    /**
     * Log a warning message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log a critical message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::critical(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log an informational message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log a debug message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log an error message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log a trace message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::trace(fmt, std::forward<Args>(args)...);
    }

    /**
     * Prints the current call stacktrace
     */
    void stacktrace();
}

#endif //SPDLOG_SAMPLE_HELPER_LOGGER_H
