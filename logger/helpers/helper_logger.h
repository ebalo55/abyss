//
// Created by BLSMNL00E on 06/08/2022.
//

#ifndef SPDLOG_SAMPLE_HELPER_LOGGER_H
#define SPDLOG_SAMPLE_HELPER_LOGGER_H

#include <spdlog/spdlog.h>

namespace logger {
    template<typename ...Args>
    inline void warn(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    template<typename ...Args>
    inline void critical(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::critical(fmt, std::forward<Args>(args)...);
    }

    template<typename ...Args>
    inline void info(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template<typename ...Args>
    inline void debug(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    template<typename ...Args>
    inline void error(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    template<typename ...Args>
    inline void trace(spdlog::format_string_t<Args...> fmt, Args &&... args) {
        spdlog::trace(fmt, std::forward<Args>(args)...);
    }

    inline void stacktrace() {}
}

#endif //SPDLOG_SAMPLE_HELPER_LOGGER_H
