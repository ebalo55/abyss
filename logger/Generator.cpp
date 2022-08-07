//
// Created by BLSMNL00E on 07/08/2022.
//

#include "Generator.h"

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
	
	logger_ptr Generator::makeSystemdLogger(const std::string &logger_name, const std::string &identity) {
#ifdef __linux__
		logger_ptr logger = spdlog::systemd_logger_mt(logger_name, identity);
		return registerAndReturn(logger);
#else
		return nullptr;
#endif
	}
	
	logger_ptr Generator::makeGroup(const std::string &logger_name, const std::vector<logger_ptr> &children) {
		// manually generate the logger using the default factory to allow for easy reuse
		auto factory = std::make_shared<spdlog::synchronous_factory>();
		
		// extract all the sinks from each provided logger
		// NOTE: multiple nested sink groups gets automatically parsed as each distributed sink gets added to the list
		//  of the sinks, and it automatically handles the log message spreading
		std::vector<spdlog::sink_ptr> children_sinks = {};
		for(const logger_ptr& child_logger : children) {
			auto sinks = child_logger->sinks();
			
			// push each sink in the children vector, this enables concatenation of multiple distributed sinks
			for(const spdlog::sink_ptr& sink : sinks) {
				children_sinks.push_back(sink);
			}
		}
		
		// generate the logger instance with all the required children sinks
		logger_ptr logger = factory->create<spdlog::sinks::dist_sink_mt, std::vector<spdlog::sink_ptr>>(
				logger_name,
				// rvalue needed, forwarding it solves the issue
				std::forward<std::vector<spdlog::sink_ptr>>(children_sinks)
		);
		
		return registerAndReturn(logger);
	}
	
	logger_ptr Generator::makeWindowsDebugLogger(const std::string &logger_name) {
#ifdef _WIN32
		// manually generate the logger using the default factory to allow for easy reuse
		auto factory = std::make_shared<spdlog::synchronous_factory>();
		
		logger_ptr logger = factory->create<spdlog::sinks::msvc_sink_mt>(
				logger_name
		);
		return registerAndReturn(logger);
#else
		return nullptr;
#endif
	}
	
} // logger