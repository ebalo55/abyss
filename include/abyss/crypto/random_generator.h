//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_RANDOM_GENERATOR_H
#define ABYSS_RANDOM_GENERATOR_H

#include <memory>
#include <sodium.h>
#include <string>
#include <sstream>

namespace abyss::crypto {
    class random_generator {
    private:
        static std::shared_ptr<random_generator> instance_;
        std::stringstream ss_;

        random_generator() = default;

        void cleanStream();

    public:
        static std::shared_ptr<random_generator> getInstance();

        /**
         * Generate a random number between 0 and 4.294.967.295 included
         * @return
         */
        uint32_t generate();

        /**
         * Generate a random number between 0 and the upper bound excluded
         * @param upper_bound Upper bound of generation
         * @return
         */
        uint32_t generate(uint32_t upper_bound);

        /**
         * Generate a random number between 0 and the upper bound excluded.
         * This method grants a uniform probability distribution.
         * @param upper_bound Upper bound of generation
         * @return
         */
        uint32_t generate_uniform(uint32_t upper_bound);

        /**
         * Generates an unpredictable sequence of bytes into buf
         * @param buf String where to generate the buffer
         * @param size Buffer size
         */
        void generate_buffer(std::string &buffer, size_t size);

        /**
         * Generates an unpredictable sequence of bytes into buf
         * @param buf String where to generate the buffer
         * @param size Buffer size
         */
        std::string generate_buffer(size_t size);
    };
}

#endif //ABYSS_RANDOM_GENERATOR_H
