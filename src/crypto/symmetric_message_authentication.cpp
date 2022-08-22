//
// Created by ebalo on 18/08/22.
//

#include "abyss/crypto/symmetric_message_authentication.h"

namespace abyss::crypto::symmetric::auth {
    std::string make_key() {
        std::stringstream ss;

        // creates the keygen
        auto key_buf = new unsigned char[crypto_auth_KEYBYTES];
        crypto_auth_keygen(key_buf);

        // insert the keygen in the stream and clean memory
        ss.write(reinterpret_cast<const char *>(key_buf), (long) crypto_auth_KEYBYTES);
        delete[] key_buf;

        // store the keygen as string and clean the stream
        std::string key = ss.str();
        ss.str("");

        return key;
    }

    std::string
    sign(const std::string &message, const std::string &key) {
        std::stringstream ss;
        auto mac = new unsigned char[crypto_auth_BYTES];

        if (crypto_auth(
                mac,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(mac), (long) crypto_auth_BYTES);
            delete[] mac;
            return ss.str();
        }

        delete[] mac;
        throw exception::symmetric_mac_exception();
    }

    bool verify(
            const std::string &tag,
            const std::string &message,
            const std::string &key
    ) {
        return crypto_auth_verify(
                reinterpret_cast<const unsigned char *>(tag.c_str()),
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0;
    }
} // crypto