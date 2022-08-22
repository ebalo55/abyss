//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/random.h"

namespace abyss::crypto::random {
    uint32_t generate() {
        return randombytes_random();
    }

    uint32_t generate(uint32_t upper_bound) {
        return randombytes_random() % upper_bound;
    }

    uint32_t generate_uniform(uint32_t upper_bound) {
        return randombytes_uniform(upper_bound);
    }

    std::string generate_buffer(size_t size) {
        std::stringstream ss;

        auto buf = new char[size];
        randombytes_buf(buf, size);

        ss.write(buf, (long) size);
        delete[] buf;
        return ss.str();
    }

    void generate_buffer(std::string &buffer, size_t size) {
        buffer = generate_buffer(size);
    }
} // crypto