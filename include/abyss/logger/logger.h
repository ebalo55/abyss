//
// Created by ebalo on 07/08/2022.
//

#ifndef SPDLOG_SAMPLE_LOGGER_H
#define SPDLOG_SAMPLE_LOGGER_H

#include "abyss/logger/settings.h"
// helpers indirectly includes Generator.h
#include "abyss/logger/helpers.h"
#include "abyss/logger/version.h"

namespace abyss::logger {
    /**
     * Initialize the instances of the abyss logger setting up all default values
     */
    void init();
}

#endif //SPDLOG_SAMPLE_LOGGER_H
