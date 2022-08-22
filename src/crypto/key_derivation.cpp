//
// Created by ebalo on 22/08/22.
//

#include "abyss/crypto/key_derivation.h"

namespace abyss::crypto::key_derivation {
    std::string make_master_key() {
        std::stringstream ss;
        auto master = new unsigned char[crypto_kdf_KEYBYTES];

        crypto_kdf_keygen(master);
        ss.write(reinterpret_cast<const char *>(master), crypto_kdf_KEYBYTES);

        delete[] master;
        return ss.str();
    }

    std::string
    derive(
            const std::string &master_key,
            size_t subkey,
            short subkey_length,
            const std::string &context
    ) {
        if (subkey_length < crypto_kdf_BYTES_MIN || subkey_length > crypto_kdf_BYTES_MAX) {
            throw exception::key_derivation_requested_size_exception();
        }

        if(context.size() != 8) {
            throw exception::key_derivation_context_size_exception();
        }

        std::stringstream ss;
        auto key = new unsigned char[subkey_length];

        crypto_kdf_derive_from_key(
                key,
                subkey_length,
                subkey,
                context.c_str(),
                reinterpret_cast<const unsigned char *>(master_key.c_str())
        );
        ss.write(reinterpret_cast<const char *>(key), subkey_length);

        delete[] key;
        return ss.str();
    }

    std::string derive(const std::string &master_key, size_t subkey, short subkey_length) {
        return derive(master_key, subkey, subkey_length, "_default");
    }
}