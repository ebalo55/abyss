//
// Created by ebalo on 22/08/22.
//

#ifndef ABYSS_HASH_H
#define ABYSS_HASH_H

#include <sodium.h>
#include <string>
#include <sstream>

#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"
#include "abyss/crypto/types.h"
#include "abyss/crypto/hash_stream.h"
#include "abyss/crypto/password_hash.h"

namespace abyss::crypto::hash {
    /**
     * Generates a random salt that can be used in password hashing
     * @return
     */
    std::string make_salt();

    /**
     * Generates a random salt that can be used in password hashing
     * @param sec Define the security level (length) of the salt to generate
     * @return
     */
    std::string make_salt(security_level sec);

    /**
     * Compute a safe and secure hash given a binary message.
     * Notes:
     * <ul>
     *  <li>This method **should not** be used for password hashing</li>
     *  <li>This method is memory intensive</li>
     *  <li>As of libsodium 1.0.18 blake2b is used</li>
     * </ul>
     * @param message Binary message too hash
     * @return Hash
     */
    std::string generic_hash(const std::string &message);

    /**
     * Compute a safe and secure hash given a binary message.
     * Notes:
     * <ul>
     *  <li>This method **should not** be used for password hashing</li>
     *  <li>This method is memory intensive</li>
     *  <li>As of libsodium 1.0.18 blake2b is used</li>
     * </ul>
     * @param message Binary message too hash
     * @param sec Define the security level (length) of the salt to generate
     * @return Hash
     */
    std::string generic_hash(const std::string &message, security_level sec);

    /**
     * Compute a safe and secure hash given a binary message.
     * Notes:
     * <ul>
     *  <li>This method **should not** be used for password hashing</li>
     *  <li>This method is memory intensive</li>
     *  <li>As of libsodium 1.0.18 blake2b is used</li>
     * </ul>
     * @param message Binary message too hash
     * @param salt Salt to further randomize the hash value
     * @return Hash
     */
    std::string generic_hash(const std::string &message, const std::string &salt);

    /**
     * Compute a safe and secure hash given a binary message.
     * Notes:
     * <ul>
     *  <li>This method **should not** be used for password hashing</li>
     *  <li>This method is memory intensive</li>
     *  <li>As of libsodium 1.0.18 blake2b is used</li>
     * </ul>
     * @param message Binary message too hash
     * @param salt Salt to further randomize the hash value
     * @param sec Define the security level (length) of the salt to generate
     * @return Hash
     */
    std::string generic_hash(const std::string &message, const std::string &salt, security_level sec);
}

#endif //ABYSS_HASH_H
