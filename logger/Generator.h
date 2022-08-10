//
// Created by BLSMNL00E on 07/08/2022.
//

#ifndef SPDLOG_SAMPLE_GENERATOR_H
#define SPDLOG_SAMPLE_GENERATOR_H

#include "macro.h"
#include <spdlog/spdlog.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <type_traits>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/hourly_file_sink.h>
#include <spdlog/sinks/tcp_sink.h>
#include <spdlog/sinks/udp_sink.h>

#ifdef _WIN_32
#include <spdlog/sinks/win_eventlog_sink.h>
#endif

#if includes_mongo_db()
#include <spdlog/sinks/mongo_sink.h>
#endif

#if includes_systemd()
#include <spdlog/sinks/systemd_sink.h>
#endif

#if includes_qt()
#include <spdlog/sinks/qt_sinks.h>
#endif

namespace abyss::logger {
    typedef std::shared_ptr<spdlog::logger> logger_ptr;

    class Generator {
    private:
        typedef std::shared_ptr<Generator> instance_t;
        static instance_t instance;

        std::unordered_map<std::string, logger_ptr> registered_loggers = {};
        std::vector<std::string> registered_names = {};

        Generator();

        /**
         * Registers the provided logger if not exists and returns a pointer to the instance if registration succeeds
         * @param logger
         * @return
         */
        logger_ptr registerAndReturn(const logger_ptr &logger);

        template<typename sink_t, typename... sink_args_t>
        requires std::is_base_of_v<spdlog::sinks::base_sink<std::mutex>, sink_t>
        logger_ptr loggerFactory(std::string logger_name, sink_args_t &&... args);

    public:
        /**
         * Get the singleton instance
         * @return
         */
        static instance_t getInstance();

        /**
         * Register a new instance of a logger and store it in memory for fast non-blocking retrieval.
         * Returns false if the logger name is already registered, otherwise returns true.
         * @param logger
         * @return
         */
        bool registerLogger(const logger_ptr &logger);

        /**
         * Create and register a new instance of a colored multi-threaded stdout logger
         * @param logger_name
         * @return
         */
        logger_ptr makeStdoutLogger(const std::string &logger_name);

        /**
         * Create and register a new instance of a colored multi-threaded stderr logger
         * @param logger_name
         * @return
         */
        logger_ptr makeStderrLogger(const std::string &logger_name);

        /**
         * Create and register a new instance of a multi-threaded rotating file logger
         * @param logger_name
         * @param filename
         * @param max_filesize
         * @param max_files
         * @return
         */
        logger_ptr
        makeRotatingFileLogger(
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
        makeDailyRotatingFileLogger(
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
        logger_ptr makeFileLogger(const std::string &logger_name, const std::string &filename);

        /**
         * Create and register a new instance of a multi-threaded syslog logger
         * @param logger_name
         * @param identity
         * @return
         */
        logger_ptr makeSyslogLogger(const std::string &logger_name, const std::string &identity);

#if includes_systemd()
        /**
         * Create and register a new instance of a multi-threaded systemd logger
         * @param logger_name
         * @param identity
         * @return
         */
        logger_ptr makeSystemdLogger(const std::string &logger_name, const std::string &identity);
#endif

        /**
         * Create and register a new instance of a multi-threaded distributed logger (group) logging to this channel
         * means logging to all channels of the group
         * @param logger_name
         * @param children
         * @return
         */
        logger_ptr makeGroup(const std::string &logger_name, const std::vector<logger_ptr> &children);

        /**
         * Create and register a new instance of a multi-threaded windows debug logger
         * @param logger_name
         * @return
         */
        logger_ptr makeWindowsDebugLogger(const std::string &logger_name);

        /**
         * Create and register a new instance of a multi-threaded distributed logger (group) with duplicate messages
         * filter logging to this channel means logging to all channels of the group
         * @param logger_name
         * @param children
         * @return
         */
        template<class Rep, class Period>
        logger_ptr makeDuplicateFilterGroup(
                const std::string &logger_name,
                const std::vector<logger_ptr> &children,
                std::chrono::duration<Rep, Period> max_skip_duration = std::chrono::seconds(3)
        );

        /**
         * Create and register a new instance of a multi-threaded hourly rotating file logger
         * @param logger_name
         * @param filename
         * @param max_files
         * @return
         */
        logger_ptr makeHourlyRotatingFileLogger(
                const std::string &logger_name,
                const std::string &filename,
                size_t max_files = 0
        );

#if includes_mongo_db()
        /**
         * Create and register a new instance of a multi-threaded mongo DB logger
         * @param logger_name
         * @return
         */
        logger_ptr makeMongoDbLogger(
                const std::string &logger_name,
                const std::string &db,
                const std::string &collection,
                const std::string &connection_uri = "mongodb://localhost:27017"
        );
#endif

#if includes_qt()
        /**
         * Create and register a new instance of a multi-threaded QT logger
         * @param logger_name
         * @param qt_object
         * @return
         */
        logger_ptr makeQtLogger(const std::string &logger_name, QTextEdit *qt_object);
#endif

        /**
         * Create and register a new instance of a multi-threaded TCP logger
         * @param logger_name
         * @param config
         * @return
         */
        logger_ptr makeTcpLogger(const std::string &logger_name, spdlog::sinks::tcp_sink_config config);

        /**
         * Create and register a new instance of a multi-threaded UDP logger
         * @param logger_name
         * @param config
         * @return
         */
        logger_ptr makeUdpLogger(const std::string &logger_name, const spdlog::sinks::udp_sink_config &config);

        /**
         * Create and register a new instance of a multi-threaded UDP logger
         * @param logger_name
          * @param source
         * @return
         */
        logger_ptr makeWindowsEventRegistryLogger(const std::string &logger_name, const std::string &source);

        /**
         * Retrieve the logger instance given its name if exists
         * @param logger_name
         * @return
         */
        static logger_ptr get(const std::string &logger_name);

        /**
         * Checks whether the provided logger name exists and is registered
         * @param logger_name
         * @return
         */
        static bool exists(const std::string &logger_name);

        /**
         * Get the list of all registered logger names
         * @return
         */
        static std::vector<std::string> list();
    };

} // logger

#endif //SPDLOG_SAMPLE_GENERATOR_H
