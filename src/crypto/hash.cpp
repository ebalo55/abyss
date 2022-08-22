//
// Created by ebalo on 22/08/22.
//

#include "abyss/crypto/hash.h"

namespace abyss::crypto::hash {
    std::string generic_hash(const std::string &message) {
        return generic_hash(message, "", average);
    }

    std::string generic_hash(const std::string &message, const std::string &salt) {
        return generic_hash(message, salt, average);
    }

    std::string make_salt() {
        return make_salt(average);
    }

    std::string make_salt(security_level sec) {
        switch (sec) {
            case minimum:
                return abyss::crypto::random::generate_buffer(crypto_generichash_KEYBYTES_MIN);
            default:
            case average:
                return abyss::crypto::random::generate_buffer(crypto_generichash_KEYBYTES);
            case maximum:
                return abyss::crypto::random::generate_buffer(crypto_generichash_KEYBYTES_MAX);
        }
    }

    std::string generic_hash(const std::string &message, security_level sec) {
        return generic_hash(message, "", sec);
    }

    std::string generic_hash(const std::string &message, const std::string &salt, security_level sec) {
        std::stringstream ss;

        unsigned hash_size;
        switch (sec) {
            case minimum:
                hash_size = crypto_generichash_BYTES_MIN;
                break;
            default:
            case average:
                hash_size = crypto_generichash_BYTES;
                break;
            case maximum:
                hash_size = crypto_generichash_BYTES_MAX;
                break;
        }

        auto hash = new unsigned char[hash_size];

        if(crypto_generichash(
                hash,
                hash_size,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(salt.c_str()),
                salt.size()
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(hash), hash_size);
            delete[] hash;

            return ss.str();
        }

        delete[] hash;
        throw exception::generic_hash_exception();
    }
}