//
// Created by ebalo on 22/08/22.
//

#ifndef ABYSS_PASSWORD_HASH_H
#define ABYSS_PASSWORD_HASH_H

#include <sstream>
#include <string>
#include <sodium.h>

#include "abyss/crypto/types.h"
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto::hash::password {
    /**
     * Generates a random salt that can be used in password hashing
     * @return
     */
    std::string make_salt();

    /**
     * Derive a secure key from a password and a salt
     * @param password Plaintext password from whose derivation should start
     * @param salt Salt for key derivation
     * @param required_key_length Key length required
     * @return Derived binary key
     */
    std::string derive_key(const std::string &password, const std::string &salt, unsigned required_key_length);

    /**
     * Derive a secure key from a password and a salt
     * @param password Plaintext password from whose derivation should start
     * @param salt Salt for key derivation
     * @param required_key_length Key length required
     * @param ops_limit Define the heaviness of cpu cycle, the heaviest the securest
     * @param mem_limit Define the allocated memory for derivation, the largest the securest
     * @return Derived binary key
     */
    std::string derive_key(
            const std::string &password,
            const std::string &salt,
            unsigned required_key_length,
            operation_limit ops_limit,
            memory_limit mem_limit
    );

    /**
     * Create an ascii verifiable hash given a plaintext password
     * @param password Plaintext password to hash
     * @return Ascii verifiable hash
     */
    std::string hash(const std::string &password);

    /**
     * Create an ascii verifiable hash given a plaintext password
     * @param password Plaintext password to hash
     * @param ops_limit Define the heaviness of cpu cycle, the heaviest the securest
     * @param mem_limit Define the allocated memory for derivation, the largest the securest
     * @return Ascii verifiable hash
     */
    std::string hash(const std::string &password, operation_limit ops_limit, memory_limit mem_limit);

    /**
     * Verifies a password hash with a plaintext password
     * @param hashed_password Hashed password with the @code abyss::crypto::hash::password::hash(...) @endcode method
     * @param password Plaintext password needing verification
     * @return True if password matches the hash, false otherwise
     */
    bool verify(const std::string &hashed_password, const std::string &password);
} // password

#endif //ABYSS_PASSWORD_HASH_H
