//
// Created by ebalo on 06/08/2022.
//

#ifndef SPDLOG_SAMPLE_HELPER_LOGGER_H
#define SPDLOG_SAMPLE_HELPER_LOGGER_H

#include <spdlog/spdlog.h>

namespace abyss::logger {
    /**
     * Log a warning _message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void warn(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log a critical _message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void critical(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::critical(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log an informational _message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void info(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log a debug _message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void debug(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log an error _message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void error(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    /**
     * Log a trace _message to the default logger
     * @tparam Args
     * @param fmt
     * @param args
     */
    template<typename ...Args>
    void trace(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::trace(fmt, std::forward<Args>(args)...);
    }
}

#endif //SPDLOG_SAMPLE_HELPER_LOGGER_H
