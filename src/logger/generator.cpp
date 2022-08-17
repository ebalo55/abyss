//
// Created by ebalo on 07/08/2022.
//

#include "abyss/logger/generator.h"

#include <utility>

namespace abyss::logger {
    // initialize the 'Settings' class static variables
    generator::instance_t generator::instance_ = nullptr;

    generator::generator() {
        // create the `ABYSS_LOGGER_ALL_CHANNEL` where all other loggers will be appended once created
        this->makeGroup(ABYSS_LOGGER_ALL_CHANNEL, {});
    }

    generator::instance_t generator::getInstance() {
        [[unlikely]]
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<generator>(new generator());
        }
        return instance_;
    }

    bool generator::registerLogger(const logger_ptr &logger) {
        raw_logger_ptr raw_logger = (raw_logger_ptr)*logger;
        if (generator::registered_loggers_.contains(raw_logger->name())) {
            return false;
        }

        // register the logger name in the `registered_names_` vector
        auto insertion_result = generator::registered_loggers_.emplace(raw_logger->name(), logger);
        if (insertion_result.second) {
            registered_names_.push_back(raw_logger->name());
        }

        // append the logger channel to the `ABYSS_LOGGER_ALL_CHANNEL` logger
        if (raw_logger->name() != ABYSS_LOGGER_ALL_CHANNEL) {
            // append all the logging channel to the `ABYSS_LOGGER_ALL_CHANNEL`
            for (const auto &sink: raw_logger->sinks()) {
                group_all_sink_->add_sink(sink);
            }
        }
            // if the logger name is `ABYSS_LOGGER_ALL_CHANNEL` load the sink into the `group_all_sink_` state variable
            // NOTE: this method is safe as an early return is applied on already registered names and the
            //  `ABYSS_LOGGER_ALL_CHANNEL` name is registered at generator startup
        else {
            group_all_sink_ = reinterpret_pointer_cast<spdlog::sinks::dist_sink_mt>(
                    raw_logger->sinks().front()
            );
        }

        return insertion_result.second;
    }

    logger_ptr generator::registerAndReturn(const logger_ptr &logger) {
        if (generator::registerLogger(logger)) {
            return logger;
        }
        return nullptr;
    }

    logger_ptr generator::makeStdoutLogger(const std::string &logger_name) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::stdout_color_mt(logger_name)
        );
        return registerAndReturn(logger);
    }

    logger_ptr generator::makeStderrLogger(const std::string &logger_name) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::stderr_color_mt(logger_name)
        );
        return registerAndReturn(logger);
    }

    logger_ptr
    generator::makeRotatingFileLogger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_filesize,
            size_t max_files
    ) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::rotating_logger_mt(logger_name, filename, max_filesize, max_files)
        );
        return registerAndReturn(logger);
    }

    logger_ptr generator::makeDailyRotatingFileLogger(
            const std::string &logger_name,
            const std::string &filename,
            int hour,
            int minute,
            size_t max_files
    ) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::daily_logger_mt(logger_name, filename, hour, minute, false, max_files)
        );
        return registerAndReturn(logger);
    }

    logger_ptr generator::makeFileLogger(const std::string &logger_name, const std::string &filename) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::basic_logger_mt(logger_name, filename)
        );
        return registerAndReturn(logger);
    }

    logger_ptr generator::makeSyslogLogger(const std::string &logger_name, const std::string &identity) {
#ifdef __linux__
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::syslog_logger_mt(logger_name, identity)
        );
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }

#if includes_systemd()
    logger_ptr Generator::makeSystemdLogger(const std::string &logger_name, const std::string &identity) {
#ifdef __linux__
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::systemd_logger_mt(logger_name, identity)
        );
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }
#endif

    logger_ptr generator::makeGroup(const std::string &logger_name, const std::vector<logger_ptr> &children) {
        // extract all the sinks from each provided logger
        // NOTE: multiple nested sink groups gets automatically parsed as each distributed sink gets added to the list
        //  of the sinks, and it automatically handles the log message spreading
        std::vector<spdlog::sink_ptr> children_sinks = {};
        for (const logger_ptr &child_logger: children) {
            auto sinks = ((raw_logger_ptr)*child_logger)->sinks();

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

    logger_ptr generator::makeWindowsDebugLogger(const std::string &logger_name) {
#ifdef _WIN32
        logger_ptr logger = loggerFactory<spdlog::sinks::msvc_sink_mt>(
                logger_name
        );
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }

    logger_ptr generator::get(const std::string &logger_name) {
        if (generator::exists(logger_name)) {
            return generator::getInstance()->registered_loggers_.at(logger_name);
        }
        return nullptr;
    }

    bool generator::exists(const std::string &logger_name) {
        instance_t current_instance = generator::getInstance();
        return std::count(
                current_instance->registered_names_.begin(),
                current_instance->registered_names_.end(),
                logger_name
        ) == 1;
    }

    std::vector<std::string> generator::list() {
        return generator::getInstance()->registered_names_;
    }

    logger_ptr generator::makeHourlyRotatingFileLogger(
            const std::string &logger_name,
            const std::string &filename,
            size_t max_files
    ) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::hourly_logger_mt(logger_name, filename, false, max_files)
        );
        return registerAndReturn(logger);
    }

#if includes_mongo_db()
    logger_ptr Generator::makeMongoDbLogger(
            const std::string &logger_name,
            const std::string &db,
            const std::string &collection,
            const std::string &connection_uri
    ) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::mongo_logger_mt(logger_name, db, collection, connection_uri)
        );
        return registerAndReturn(logger);
    }
#endif

#if includes_qt()
    logger_ptr Generator::makeQtLogger(const std::string &logger_name, QTextEdit *qt_object) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::qt_logger_mt(logger_name, qt_object)
        );
        return registerAndReturn(logger);
    }
#endif

    logger_ptr generator::makeTcpLogger(const std::string &logger_name, spdlog::sinks::tcp_sink_config config) {
        logger_ptr logger = loggerFactory<spdlog::sinks::tcp_sink_mt, spdlog::sinks::tcp_sink_config>(
                logger_name,
                std::forward<spdlog::sinks::tcp_sink_config>(config)
        );
        return registerAndReturn(logger);
    }

    logger_ptr generator::makeUdpLogger(const std::string &logger_name, const spdlog::sinks::udp_sink_config &config) {
        logger_ptr logger = abyss::logger::logger::make(
                spdlog::udp_logger_mt(logger_name, config)
        );
        return registerAndReturn(logger);
    }

    logger_ptr generator::makeWindowsEventRegistryLogger(const std::string &logger_name, const std::string &source) {
#ifdef _WIN32
        logger_ptr logger = loggerFactory<spdlog::sinks::win_eventlog_sink_mt>(logger_name, source);
        return registerAndReturn(logger);
#else
        return nullptr;
#endif
    }

    template<typename sink_t, typename... sink_args_t>
    requires is_multi_threaded_sink<sink_t>
    logger_ptr generator::loggerFactory(std::string logger_name, sink_args_t &&... args) {
        return abyss::logger::logger::make(
                spdlog::synchronous_factory::template create<sink_t, sink_args_t...>(
                        logger_name,
                        std::forward<sink_args_t>(args)...
                )
        );
    }

} // logger