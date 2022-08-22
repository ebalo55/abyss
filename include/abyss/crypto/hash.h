//
// Created by ebalo on 22/08/22.
//

#ifndef ABYSS_HASH_H
#define ABYSS_HASH_H

#include <sodium.h>
#include <string>
#include <sstream>

#include "abyss/crypto/random.h"
#include "abyss/crypto/types.h"
#include "abyss/crypto/hash_stream.h"

namespace abyss::crypto::hash {
    std::string make_salt();
    std::string make_salt(security_level sec);

    std::string generic_hash(const std::string &message);
    std::string generic_hash(const std::string &message, security_level sec);
    std::string generic_hash(const std::string &message, const std::string &salt);
    std::string generic_hash(const std::string &message, const std::string &salt, security_level sec);
}

#endif //ABYSS_HASH_H
