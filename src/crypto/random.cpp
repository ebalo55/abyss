//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/random.h"

namespace abyss::crypto::random {
    uint32_t generate() {
        return random_generator::getInstance()->generate();
    }

    uint32_t generate(uint32_t upper_bound) {
        return random_generator::getInstance()->generate(upper_bound);
    }

    uint32_t generate_uniform(uint32_t upper_bound) {
        return random_generator::getInstance()->generate_uniform(upper_bound);
    }

    void generate_buffer(std::string &buffer, size_t size) {
        return random_generator::getInstance()->generate_buffer(buffer, size);
    }

    std::string generate_buffer(size_t size) {
        return random_generator::getInstance()->generate_buffer(size);
    }
} // crypto