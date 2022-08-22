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
    std::string make_salt();
    std::string derive_key(const std::string &password, const std::string &salt, unsigned required_key_length);
    std::string derive_key(const std::string &password, const std::string &salt, unsigned required_key_length, operation_limit ops_limit, memory_limit mem_limit);
    std::string hash(const std::string &password);
    std::string hash(const std::string &password, operation_limit ops_limit, memory_limit mem_limit);
    bool verify(const std::string &hashed_password, const std::string &password);
} // password

#endif //ABYSS_PASSWORD_HASH_H
