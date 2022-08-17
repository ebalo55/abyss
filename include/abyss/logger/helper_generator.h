//
// Created by ebalo on 07/08/2022.
//

#ifndef SPDLOG_SAMPLE_HELPER_GENERATOR_H
#define SPDLOG_SAMPLE_HELPER_GENERATOR_H

#include "abyss/logger/generator.h"

namespace abyss::logger {
    /**
     * Retrieve the logger instance given its name if exists
     * @param logger_name
     * @return
     */
    logger_ptr get(const std::string &logger_name);

    /**
     * Checks whether the provided logger name exists and is registered
     * @param logger_name
     * @return
     */
    bool exists(const std::string &logger_name);

    /**
     * Get the list of all registered logger names
     * @return
     */
    std::vector<std::string> list();

    /**
     * Register a new instance of a logger and store it in memory for fast non-blocking retrieval.
     * Returns false if the logger name is already registered, otherwise returns true.
     * @param logger
     * @return
     */
    bool register_logger(const logger_ptr &logger);

    /**
     * Create and register a new instance of a colored multi-threaded stdout logger
     * @param logger_name
     * @return
     */
    logger_ptr make_stdout_logger(const std::string &logger_name);

    /**
     * Create and register a new instance of a colored multi-threaded stderr logger
     * @param logger_name
     * @return
     */
    logger_ptr make_stderr_logger(const std::string &logger_name);

    /**
     * Create and register a new instance of a multi-threaded rotating file logger
     * @param logger_name
     * @param filename
     * @param max_filesize
     * @param max_files
     * @return
     */
    logger_ptr
    make_rotating_file_logger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_filesize,
            size_t max_files
    );

    /**
     * Create and register a new instance of a multi-threaded timed rotating file logger
     * @param logger_name
     * @param filename
     * @param hour
     * @param minute
     * @param max_files
     * @return
     */
    logger_ptr
    make_daily_rotating_file_logger(
            const std::string &logger_name,
            const std::string &filename,
            int hour,
            int minute,
            size_t max_files = 0
    );

    /**
     * Create and register a new instance of a multi-threaded file logger
     * @param logger_name
     * @param filename
     * @return
     */
    logger_ptr make_file_logger(const std::string &logger_name, const std::string &filename);

    /**
     * Create and register a new instance of a multi-threaded syslog logger
     * @param logger_name
     * @param identity
     * @return
     */
    logger_ptr make_syslog_logger(const std::string &logger_name, const std::string &identity);

    /**
     * Create and register a new instance of a multi-threaded systemd logger
     * @param logger_name
     * @param identity
     * @return
     */
    logger_ptr make_systemd_logger(const std::string &logger_name, const std::string &identity);

    /**
     * Create and register a new instance of a multi-threaded distributed logger (group) logging to this channel
     * means logging to all channels of the group
     * @param logger_name
     * @param children
     * @return
     */
    logger_ptr make_group(const std::string &logger_name, const std::vector<logger_ptr> &children);

    /**
     * Create and register a new instance of a multi-threaded windows debug logger
     * @param logger_name
     * @return
     */
    logger_ptr make_windows_debug_logger(const std::string &logger_name);

    /**
     * Create and register a new instance of a multi-threaded hourly rotating file logger
     * @param logger_name
     * @param filename
     * @param max_files
     * @return
     */
    logger_ptr make_hourly_rotating_file_logger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_files = 0
    );

    /**
     * Create and register a new instance of a multi-threaded mongo DB logger
     * @param logger_name
     * @return
     */
    logger_ptr make_mongo_db_logger(
            const std::string &logger_name,
            const std::string &db,
            const std::string &collection,
            const std::string &connection_uri = "mongodb://localhost:27017"
    );

#if includes_qt()
    /**
     * Create and register a new instance of a multi-threaded QT logger
     * @param logger_name
     * @param qt_object
     * @return
     */
    logger_ptr make_qt_logger(const std::string &logger_name, QTextEdit *qt_object);
#endif

    /**
     * Create and register a new instance of a multi-threaded TCP logger
     * @param logger_name
     * @param config
     * @return
     */
    logger_ptr make_tcp_logger(const std::string &logger_name, const spdlog::sinks::tcp_sink_config &config);

    /**
     * Create and register a new instance of a multi-threaded UDP logger
     * @param logger_name
     * @param config
     * @return
     */
    logger_ptr make_udp_logger(const std::string &logger_name, const spdlog::sinks::udp_sink_config &config);

    /**
     * Create and register a new instance of a multi-threaded UDP logger
     * @param logger_name
     * @param source
     * @return
     */
    logger_ptr make_windows_event_registry_logger(const std::string &logger_name, const std::string &source);
}

#endif //SPDLOG_SAMPLE_HELPER_GENERATOR_H
