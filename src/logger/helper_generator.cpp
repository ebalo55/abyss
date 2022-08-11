//
// Created by ebalo on 11/08/22.
//
#include "abyss/logger/helper_generator.h"

namespace abyss::logger {
    logger_ptr get(const std::string &logger_name) {
        return Generator::get(logger_name);
    }

    bool exists(const std::string &logger_name) {
        return Generator::exists(logger_name);
    }

    std::vector<std::string> list() {
        return Generator::list();
    }

    bool register_logger(const logger_ptr &logger) {
        return Generator::getInstance()->registerLogger(logger);
    }

    logger_ptr make_stdout_logger(const std::string &logger_name) {
        return Generator::getInstance()->makeStdoutLogger(logger_name);
    }

    logger_ptr make_stderr_logger(const std::string &logger_name) {
        return Generator::getInstance()->makeStderrLogger(logger_name);
    }

    logger_ptr
    make_rotating_file_logger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_filesize,
            size_t max_files
    ) {
        return Generator::getInstance()->makeRotatingFileLogger(logger_name, filename, max_filesize, max_files);
    }

    logger_ptr
    make_daily_rotating_file_logger(
            const std::string &logger_name,
            const std::string &filename,
            int hour,
            int minute,
            size_t max_files
    ) {
        return Generator::getInstance()->makeDailyRotatingFileLogger(logger_name, filename, hour, minute, max_files);
    }

    logger_ptr make_file_logger(const std::string &logger_name, const std::string &filename) {
        return Generator::getInstance()->makeFileLogger(logger_name, filename);
    }

    logger_ptr make_syslog_logger(const std::string &logger_name, const std::string &identity) {
        return Generator::getInstance()->makeSyslogLogger(logger_name, identity);
    }

    logger_ptr make_systemd_logger(const std::string &logger_name, const std::string &identity) {
#if includes_systemd()
        return Generator::getInstance()->makeSystemdLogger(logger_name, identity);
#else
        return nullptr;
#endif
    }

    logger_ptr make_group(const std::string &logger_name, const std::vector<logger_ptr> &children) {
        return Generator::getInstance()->makeGroup(logger_name, children);
    }

    logger_ptr make_windows_debug_logger(const std::string &logger_name) {
        return Generator::getInstance()->makeWindowsDebugLogger(logger_name);
    }

    template<class Rep, class Period>
    logger_ptr make_duplicate_filter_group(
            const std::string &logger_name,
            const std::vector<logger_ptr> &children,
            std::chrono::duration<Rep, Period> max_skip_duration
    ) {
        return Generator::getInstance()->makeDuplicateFilterGroup(logger_name, children, max_skip_duration);
    }

    logger_ptr make_hourly_rotating_file_logger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_files
    ) {
        return Generator::getInstance()->makeHourlyRotatingFileLogger(logger_name, filename, max_files);
    }

    logger_ptr makeMongoDbLogger(
            const std::string &logger_name,
            const std::string &db,
            const std::string &collection,
            const std::string &connection_uri
    ) {
#if includes_mongo_db()
        return Generator::getInstance()->makeMongoDbLogger(logger_name, db, collection, connection_uri);
#else
        return nullptr;
#endif
    }

#if includes_qt()
    logger_ptr make_qt_logger(const std::string &logger_name, QTextEdit *qt_object) {
        return Generator::getInstance()->makeQtLogger(logger_name, qt_object);
    }
#endif

    logger_ptr make_tcp_logger(const std::string &logger_name, const spdlog::sinks::tcp_sink_config &config) {
        return Generator::getInstance()->makeTcpLogger(logger_name, config);
    }

    logger_ptr make_udp_logger(const std::string &logger_name, const spdlog::sinks::udp_sink_config &config) {
        return Generator::getInstance()->makeUdpLogger(logger_name, config);
    }

    logger_ptr make_windows_event_registry_logger(const std::string &logger_name, const std::string &source) {
        return Generator::getInstance()->makeWindowsEventRegistryLogger(logger_name, source);
    }
}