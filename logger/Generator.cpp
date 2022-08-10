//
// Created by BLSMNL00E on 07/08/2022.
//

#include "Generator.h"

#include <utility>

namespace abyss::logger {
    // initialize the 'Settings' class static variables
    Generator::instance_t Generator::instance = nullptr;

    Generator::Generator() {
        // todo: make a logger named 'all' containing all other registered loggers
    }

    Generator::instance_t Generator::getInstance() {
        [[unlikely]]
        if (instance == nullptr) {
            instance = std::shared_ptr<Generator>(new Generator());
        }
        return instance;
    }

    bool Generator::registerLogger(const logger_ptr &logger) {
        if (Generator::registered_loggers.contains(logger->name())) {
            return false;
        }

        auto insertion_result = Generator::registered_loggers.emplace(logger->name(), logger);
        if (insertion_result.second) {
            registered_names.push_back(logger->name());
        }

        return insertion_result.second;
    }

    logger_ptr Generator::registerAndReturn(const logger_ptr &logger) {
        if (Generator::registerLogger(logger)) {
            return logger;
        }
        return nullptr;
    }

    logger_ptr Generator::makeStdoutLogger(const std::string &logger_name) {
        logger_ptr logger = spdlog::stdout_color_mt(logger_name);
        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeStderrLogger(const std::string &logger_name) {
        logger_ptr logger = spdlog::stderr_color_mt(logger_name);
        return registerAndReturn(logger);
    }

    logger_ptr
    Generator::makeRotatingFileLogger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_filesize,
            size_t max_files
    ) {
        logger_ptr logger = spdlog::rotating_logger_mt(logger_name, filename, max_filesize, max_files);
        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeDailyRotatingFileLogger(
            const std::string &logger_name,
            const std::string &filename,
            int hour,
            int minute,
            size_t max_files
    ) {
        logger_ptr logger = spdlog::daily_logger_mt(logger_name, filename, hour, minute, false, max_files);
        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeFileLogger(const std::string &logger_name, const std::string &filename) {
        logger_ptr logger = spdlog::basic_logger_mt(logger_name, filename);
        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeSyslogLogger(const std::string &logger_name, const std::string &identity) {
#ifdef __linux__
        logger_ptr logger = spdlog::syslog_logger_mt(logger_name, identity);
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }

#if includes_systemd()
    logger_ptr Generator::makeSystemdLogger(const std::string &logger_name, const std::string &identity) {
#ifdef __linux__
        logger_ptr logger = spdlog::systemd_logger_mt(logger_name, identity);
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }
#endif

    logger_ptr Generator::makeGroup(const std::string &logger_name, const std::vector<logger_ptr> &children) {
        // extract all the sinks from each provided logger
        // NOTE: multiple nested sink groups gets automatically parsed as each distributed sink gets added to the list
        //  of the sinks, and it automatically handles the log message spreading
        std::vector<spdlog::sink_ptr> children_sinks = {};
        for (const logger_ptr &child_logger: children) {
            auto sinks = child_logger->sinks();

            // push each sink in the children vector, this enables concatenation of multiple distributed sinks
            for (const spdlog::sink_ptr &sink: sinks) {
                children_sinks.push_back(sink);
            }
        }

        // generate the logger instance with all the required children sinks
        logger_ptr logger = loggerFactory<spdlog::sinks::dist_sink_mt, std::vector<spdlog::sink_ptr>>(
                logger_name,
                // rvalue needed, forwarding it solves the issue
                std::forward<std::vector<spdlog::sink_ptr>>(children_sinks)
        );

        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeWindowsDebugLogger(const std::string &logger_name) {
#ifdef _WIN32
        logger_ptr logger = loggerFactory<spdlog::sinks::msvc_sink_mt>(
                logger_name
        );
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }

    template<class Rep, class Period>
    logger_ptr
    Generator::makeDuplicateFilterGroup(
            const std::string &logger_name,
            const std::vector<logger_ptr> &children,
            std::chrono::duration<Rep, Period> max_skip_duration
    ) {
        // extract all the sinks from each provided logger
        // NOTE: multiple nested sink groups gets automatically parsed as each distributed sink gets added to the list
        //  of the sinks, and it automatically handles the log message spreading
        std::vector<spdlog::sink_ptr> children_sinks = {};
        for (const logger_ptr &child_logger: children) {
            auto sinks = child_logger->sinks();

            // push each sink in the children vector, this enables concatenation of multiple distributed sinks
            for (const spdlog::sink_ptr &sink: sinks) {
                children_sinks.push_back(sink);
            }
        }

        // generate the logger instance with all the required children sinks
        logger_ptr logger = loggerFactory<spdlog::sinks::dup_filter_sink_mt, std::chrono::duration<Rep, Period>, std::vector<spdlog::sink_ptr>>(
                logger_name,
                5,
                // rvalue needed, forwarding it solves the issue
                std::forward<std::vector<spdlog::sink_ptr>>(children_sinks)
        );

        return registerAndReturn(logger);
    }

    logger_ptr Generator::get(const std::string &logger_name) {
        if (Generator::exists(logger_name)) {
            return Generator::getInstance()->registered_loggers.at(logger_name);
        }
        return nullptr;
    }

    bool Generator::exists(const std::string &logger_name) {
        instance_t current_instance = Generator::getInstance();
        return std::count(
                current_instance->registered_names.begin(),
                current_instance->registered_names.end(),
                logger_name
        ) == 1;
    }

    std::vector<std::string> Generator::list() {
        return Generator::getInstance()->registered_names;
    }

    logger_ptr Generator::makeHourlyRotatingFileLogger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_files
    ) {
        logger_ptr logger = spdlog::hourly_logger_mt(logger_name, filename, false, max_files);
        return registerAndReturn(logger);
    }

#if includes_mongo_db()
    logger_ptr Generator::makeMongoDbLogger(
            const std::string &logger_name,
            const std::string &db,
            const std::string &collection,
            const std::string &connection_uri
    ) {
        logger_ptr logger = spdlog::mongo_logger_mt(logger_name, db, collection, connection_uri);
        return registerAndReturn(logger);
    }
#endif

#if includes_qt()
    logger_ptr Generator::makeQtLogger(const std::string &logger_name, QTextEdit *qt_object) {
        logger_ptr logger = spdlog::qt_logger_mt(logger_name, qt_object);
        return registerAndReturn(logger);
    }
#endif

    logger_ptr Generator::makeTcpLogger(const std::string &logger_name, spdlog::sinks::tcp_sink_config config) {
        logger_ptr logger = loggerFactory<spdlog::sinks::tcp_sink_mt, spdlog::sinks::tcp_sink_config>(
                logger_name,
                std::forward<spdlog::sinks::tcp_sink_config>(config)
        );
        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeUdpLogger(const std::string &logger_name, const spdlog::sinks::udp_sink_config &config) {
        logger_ptr logger = spdlog::udp_logger_mt(logger_name, config);
        return registerAndReturn(logger);
    }

    logger_ptr Generator::makeWindowsEventRegistryLogger(const std::string &logger_name, const std::string &source) {
#ifdef _WIN32
        logger_ptr logger = loggerFactory<spdlog::sinks::win_eventlog_sink_mt>(logger_name, source);
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }

    template<typename sink_t, typename... sink_args_t>
    requires std::is_base_of_v<spdlog::sinks::base_sink<std::mutex>, sink_t>
    logger_ptr Generator::loggerFactory(std::string logger_name, sink_args_t &&... args) {
        return spdlog::synchronous_factory::template create<sink_t, sink_args_t...>(
                logger_name,
                std::forward<sink_args_t>(args)...
        );
    }

} // logger