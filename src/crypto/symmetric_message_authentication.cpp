//
// Created by ebalo on 18/08/22.
//

#include "abyss/crypto/symmetric_message_authentication.h"

namespace abyss::crypto::symmetric {
    std::shared_ptr<symmetric_message_authentication> symmetric_message_authentication::instance_ = nullptr;

    void symmetric_message_authentication::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<symmetric_message_authentication> symmetric_message_authentication::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<symmetric_message_authentication>(new symmetric_message_authentication());
        }
        return instance_;
    }

    std::string symmetric_message_authentication::makeKey() {
        cleanStream();

        // creates the keygen
        auto key_buf = new unsigned char[crypto_auth_keybytes()];
        crypto_auth_keygen(key_buf);

        // insert the keygen in the stream and clean memory
        ss_.write(reinterpret_cast<const char *>(key_buf), (long) crypto_auth_keybytes());
        delete[] key_buf;

        // store the keygen as string and clean the stream
        std::string key = ss_.str();
        cleanStream();

        return key;
    }

    std::string
    symmetric_message_authentication::computeAuthenticationTag(const std::string &message, const std::string &key) {
        cleanStream();
        auto mac = new unsigned char[crypto_auth_bytes()];

        if (crypto_auth(
                mac,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(mac), (long) crypto_auth_bytes());
            delete[] mac;
            return ss_.str();
        }

        delete[] mac;
        throw exception::symmetric_mac_exception();
    }

    bool symmetric_message_authentication::verifyAuthenticationTag(
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