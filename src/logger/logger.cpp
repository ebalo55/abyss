//
// Created by ebalo on 11/08/22.
//

#include "abyss/logger/logger.h"

namespace abyss::logger {
    void init() {
        settings::getInstance();
        generator::getInstance();
    }
}