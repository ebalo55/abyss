//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_TYPES_H
#define ABYSS_TYPES_H

#include <spdlog/spdlog.h>
#include <memory>
#include <spdlog/sinks/base_sink.h>

namespace abyss::logger {
    typedef std::shared_ptr<spdlog::logger> raw_logger_ptr;
    typedef spdlog::level::level_enum log_level_t;

    struct logging_format_t {
        bool logging_level = true;
        bool log_time = false;
        bool pid = false;
        bool thread_id = false;
    };
    typedef struct logging_format_t logging_format_t;

    template<typename sink_t>
    concept is_multi_threaded_sink = std::is_base_of_v<spdlog::sinks::base_sink<std::mutex>, sink_t>;
}

#endif //ABYSS_TYPES_H
