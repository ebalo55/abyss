//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_RANDOM_H
#define ABYSS_RANDOM_H

#include <sodium.h>
#include <sstream>

namespace abyss::crypto::random {
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
    uint32_t generate(uint32_t
    upper_bound);

    /**
     * Fill in a pointer with the given number of random bytes
     * @param container Pointer where to store the random data
     * @param size Byte size of the pointer memory allocation
     * @return
     */
    template<typename ref>
    void generate(ref* container, size_t size) {
        randombytes_buf(container, size);
    }

    /**
     * Generate a random number between 0 and the upper bound excluded.
     * This method grants a uniform probability distribution.
     * @param upper_bound Upper bound of generation
     * @return
     */
    uint32_t generate_uniform(uint32_t
    upper_bound);

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
} // crypto

#endif //ABYSS_RANDOM_H
