//
// Created by ebalo on 18/08/22.
//

#include "abyss/crypto/asymmetric_message_authentication.h"

namespace abyss::crypto::asymmetric {
    std::shared_ptr<asymmetric_message_authentication> asymmetric_message_authentication::instance_ = nullptr;

    void asymmetric_message_authentication::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<asymmetric_message_authentication> asymmetric_message_authentication::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<asymmetric_message_authentication>(new asymmetric_message_authentication());
        }
        return instance_;
    }

    keypair_t asymmetric_message_authentication::makeKeypair() {
        auto public_key_buf = new unsigned char[crypto_sign_PUBLICKEYBYTES];
        auto secret_key_buf = new unsigned char[crypto_sign_SECRETKEYBYTES];

        crypto_sign_keypair(public_key_buf, secret_key_buf);

        // cast buf to string
        cleanStream();
        ss_.write(reinterpret_cast<const char *>(public_key_buf), (long) crypto_sign_PUBLICKEYBYTES);
        std::string public_key = ss_.str();
        delete[] public_key_buf;
        cleanStream();

        // cast buf to string
        ss_.write(reinterpret_cast<const char *>(secret_key_buf), (long) crypto_sign_SECRETKEYBYTES);
        std::string secret_key = ss_.str();
        delete[] secret_key_buf;
        cleanStream();

        return {.public_key = public_key, .secret_key = secret_key};
    }

    std::string
    asymmetric_message_authentication::signMessage(const std::string &message, const std::string &secret_key) {
        cleanStream();

        size_t message_size = message.size() + crypto_sign_BYTES;
        auto signed_message = new unsigned char[message_size];

        if (crypto_sign(
                signed_message,
                nullptr,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(secret_key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(signed_message), (long) message_size);
            delete[] signed_message;
            return ss_.str();
        }

        delete[] signed_message;
        throw exception::asymmetric_mac_exception();
    }

    signature_data_t asymmetric_message_authentication::verifyMessage(
            const std::string &message,
            const std::string &public_key
    ) {
        cleanStream();

        size_t message_size = message.size() - crypto_sign_BYTES;
        auto unsigned_message = new unsigned char[message_size];

        if (crypto_sign_open(
                unsigned_message,
                nullptr,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(public_key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(unsigned_message), (long) message_size);
            delete[] unsigned_message;
            return {
                    .verified = true,
                    .message = ss_.str()
            };
        }

        delete[] unsigned_message;
        return {
                .verified = false,
                .message = ""
        };
    }

    std::string
    asymmetric_message_authentication::signMessageDetached(const std::string &message, const std::string &secret_key) {
        cleanStream();

        auto tag = new unsigned char[crypto_sign_BYTES];

        if (crypto_sign_detached(
                tag,
                nullptr,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(secret_key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(tag), (long) crypto_sign_BYTES);
            delete[] tag;
            return ss_.str();
        }

        delete[] tag;
        throw exception::asymmetric_mac_exception();
    }

    bool asymmetric_message_authentication::verifyMessageDetached(
            const std::string &tag,
            const std::string &message,
            const std::string &public_key
    ) {
        return crypto_sign_verify_detached(
                reinterpret_cast<const unsigned char *>(tag.c_str()),
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(public_key.c_str())
        ) == 0;
    }

    std::string
    asymmetric_message_authentication::signMessage(const std::string &message, const keypair_t &sender_keypair) {
        return signMessage(message, sender_keypair.secret_key);
    }

    signature_data_t
    asymmetric_message_authentication::verifyMessage(const std::string &message, const keypair_t &receiver_keypair) {
        return verifyMessage(message, receiver_keypair.public_key);
    }

    std::string asymmetric_message_authentication::signMessageDetached(
            const std::string &message,
            const keypair_t &sender_keypair
    ) {
        return signMessageDetached(message, sender_keypair.secret_key);
    }

    bool asymmetric_message_authentication::verifyMessageDetached(
            const std::string &tag,
            const std::string &message,
            const keypair_t &receiver_keypair
    ) {
        return verifyMessageDetached(tag, message, receiver_keypair.public_key);
    }
} // asymmetric