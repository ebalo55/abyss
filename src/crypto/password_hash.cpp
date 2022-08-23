//
// Created by ebalo on 22/08/22.
//

#include "abyss/crypto/password_hash.h"

namespace abyss::crypto::hash::password {
    std::string derive_key(const std::string &password, const std::string &salt, unsigned int required_key_length) {
        return derive_key(
                password,
                salt,
                required_key_length,
                operation_limit::_ops_interactive,
                memory_limit::_memory_interactive
        );
    }

    std::string hash(const std::string &password) {
        return hash(password, _ops_interactive, _memory_interactive);
    }

    std::string hash(const std::string &password, operation_limit ops_limit, memory_limit mem_limit) {
        std::stringstream ss;
        auto hash = new char[crypto_pwhash_STRBYTES];

        if (crypto_pwhash_str(
                hash,
                password.c_str(),
                password.size(),
                ops_limit,
                mem_limit
        ) == 0) {
            ss << hash;

            delete[] hash;
            return ss.str();
        }

        delete[] hash;
        throw exception::password_hash_exception();
    }

    bool verify(const std::string &hashed_password, const std::string &password) {
        return crypto_pwhash_str_verify(
                hashed_password.c_str(),
                password.c_str(),
                password.size()
        ) == 0;
    }

    std::string make_salt() {
        return abyss::crypto::random::generate_buffer(crypto_pwhash_SALTBYTES);
    }

    std::string derive_key(
            const std::string &password,
            const std::string &salt,
            unsigned int required_key_length,
            operation_limit ops_limit,
            memory_limit mem_limit
    ) {
        if (required_key_length < crypto_pwhash_BYTES_MIN || required_key_length > crypto_pwhash_BYTES_MAX) {
            throw exception::key_derivation_size_exception();
        }

        std::stringstream ss;
        auto key = new unsigned char[required_key_length];

        if (crypto_pwhash(
                key,
                required_key_length,
                password.c_str(),
                password.size(),
                reinterpret_cast<const unsigned char *const>(salt.c_str()),
                ops_limit,
                mem_limit,
                crypto_pwhash_ALG_DEFAULT
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(key), required_key_length);
            delete[] key;
            return ss.str();
        }

        delete[] key;
        throw exception::key_derivation_exception();
    }
} // password