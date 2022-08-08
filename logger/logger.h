//
// Created by BLSMNL00E on 07/08/2022.
//

#ifndef SPDLOG_SAMPLE_LOGGER_H
#define SPDLOG_SAMPLE_LOGGER_H

#define INCLUDE_QT_SINK 0

#include "Settings.h"
// helpers indirectly includes Generator.h
#include "helpers.h"

namespace abyss::logger {
	/**
	 * Initialize the instances of the abyss logger actually setting up all default values
	 */
	void init() {
		Settings::getInstance();
		Generator::getInstance();
	}
}
#endif //SPDLOG_SAMPLE_LOGGER_H
