//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/random_generator.h"

namespace abyss::crypto {
    std::shared_ptr<random_generator> random_generator::instance_ = nullptr;

    void random_generator::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<random_generator> random_generator::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<random_generator>(new random_generator());
        }
        return instance_;
    }

    uint32_t random_generator::generate() {
        return randombytes_random();
    }

    uint32_t random_generator::generate(uint32_t upper_bound) {
        return randombytes_random() % upper_bound;
    }

    uint32_t random_generator::generate_uniform(uint32_t upper_bound) {
        return randombytes_uniform(upper_bound);
    }

    std::string random_generator::generate_buffer(size_t size) {
        cleanStream();

        auto buf = new char[size];
        randombytes_buf(buf, size);

        ss_.write(buf, (long)size);
        delete[] buf;
        return ss_.str();
    }

    void random_generator::generate_buffer(std::string &buffer, size_t size) {
        cleanStream();

        buffer = generate_buffer(size);
    }
} // crypto