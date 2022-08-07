//
// Created by BLSMNL00E on 07/08/2022.
//

#ifndef SPDLOG_SAMPLE_GENERATOR_H
#define SPDLOG_SAMPLE_GENERATOR_H

#include <spdlog/spdlog.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/sinks/systemd_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>

namespace abyss::logger {
	typedef std::shared_ptr<spdlog::logger> logger_ptr;
	
	class Generator {
	private:
		typedef std::shared_ptr<Generator> instance_t;
		static instance_t instance;
		
		std::unordered_map<std::string, logger_ptr> registered_loggers = { };
		std::vector<std::string> registered_names = { };
		
		Generator();
		
		/**
		 * Registers the provided logger if not exists and returns a pointer to the instance if registration succeeds
		 * @param logger
		 * @return
		 */
		logger_ptr registerAndReturn(const logger_ptr &logger);
	
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

		/**
		 * Create and register a new instance of a multi-threaded systemd logger
		 * @param logger_name
		 * @param identity
		 * @return
		 */
		logger_ptr makeSystemdLogger(const std::string &logger_name, const std::string &identity);

		/**
		 * Create and register a new instance of a multi-threaded distributed logger (group) logging to this channel
		 * means logging to all channels of the group
		 * @param logger_name
		 * @param children
		 * @return
		 */
		logger_ptr makeGroup(const std::string &logger_name, const std::vector<logger_ptr>& children);
		
		/**
		 * Create and register a new instance of a multi-threaded windows debug logger
		 * @param logger_name
		 * @return
		 */
		logger_ptr makeWindowsDebugLogger(const std::string &logger_name);
	};
	
} // logger

#endif //SPDLOG_SAMPLE_GENERATOR_H
