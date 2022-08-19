//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/symmetric_encryption.h"

namespace abyss::crypto::symmetric {
    std::shared_ptr<symmetric_encryption> symmetric_encryption::instance_ = nullptr;

    void symmetric_encryption::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<symmetric_encryption> symmetric_encryption::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<symmetric_encryption>(new symmetric_encryption());
        }
        return instance_;
    }

    encrypted_data_t symmetric_encryption::encryptMessage(const std::string &message) {
        return encryptMessage(message, makeEncryptionKey());
    }

    encrypted_data_t
    symmetric_encryption::encryptMessage(const std::string &message, const std::string &key) {
        return encryptMessage(message, key, makeNonce());
    }

    encrypted_data_t
    symmetric_encryption::encryptMessage(const std::string &message, const std::string &key, const std::string &nonce) {
        cleanStream();

        // create the encryption buffer
        size_t encrypted_size = message.size() + crypto_secretbox_MACBYTES;
        auto encrypted_buf = new unsigned char[encrypted_size];

        if (crypto_secretbox_easy(
                encrypted_buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(encrypted_buf), (long) encrypted_size);
            delete[] encrypted_buf;
            return {ss_.str(), key, nonce};
        }
        delete[] encrypted_buf;
        throw exception::symmetric_message_encryption_exception();
    }

    encrypted_data_t symmetric_encryption::encryptMessage(const encryption_data_t &data) {
        return encryptMessage(data.message, data.key, data.nonce);
    }

    std::string symmetric_encryption::decryptMessage(const decryption_data_t &data) {
        return decryptMessage(data.message, data.key, data.nonce);
    }

    std::string
    symmetric_encryption::decryptMessage(const std::string &message, const std::string &key, const std::string &nonce) {
        cleanStream();

        // create the decryption buffer
        size_t decrypted_size = message.size() - crypto_secretbox_MACBYTES;
        auto decrypted_buf = new unsigned char[decrypted_size];

        if (crypto_secretbox_open_easy(
                decrypted_buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(decrypted_buf), (long) decrypted_size);
            delete[] decrypted_buf;
            return ss_.str();
        }
        delete[] decrypted_buf;
        throw exception::symmetric_message_decryption_exception();
    }

    encrypted_data_detached_t symmetric_encryption::encryptMessageDetached(const std::string &message) {
        return encryptMessageDetached(message, makeEncryptionKey());
    }

    encrypted_data_detached_t
    symmetric_encryption::encryptMessageDetached(const std::string &message, const std::string &key) {
        return encryptMessageDetached(message, key, makeNonce());
    }

    encrypted_data_detached_t
    symmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const std::string &key,
            const std::string &nonce
    ) {
        cleanStream();

        // create the encryption buffer
        auto encrypted_buf = new unsigned char[message.size()];
        auto tag_buf = new unsigned char[crypto_secretbox_MACBYTES];

        if (crypto_secretbox_detached(
                encrypted_buf,
                tag_buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            // store the encrypted _message, delete the buffer and clean the stream
            ss_.write(reinterpret_cast<const char *>(encrypted_buf), (long) message.size());
            std::string encrypted_message = ss_.str();
            delete[] encrypted_buf;
            cleanStream();

            // stream the tag and delete the tag buffer
            ss_.write(reinterpret_cast<const char *>(tag_buf), (long) crypto_secretbox_MACBYTES);
            delete[] tag_buf;
            return {ss_.str(), encrypted_message, key, nonce};
        }
        delete[] encrypted_buf;
        delete[] tag_buf;
        throw exception::symmetric_message_encryption_exception();
    }

    encrypted_data_detached_t symmetric_encryption::encryptMessageDetached(const encryption_data_t &data) {
        return encryptMessageDetached(data.message, data.key, data.nonce);
    }

    std::string symmetric_encryption::makeEncryptionKey() {
        cleanStream();

        // creates the keygen
        auto key_buf = new unsigned char[crypto_secretbox_KEYBYTES];
        crypto_secretbox_keygen(key_buf);

        // insert the keygen in the stream and clean memory
        ss_.write(reinterpret_cast<const char *>(key_buf), (long) crypto_secretbox_KEYBYTES);
        delete[] key_buf;

        // store the keygen as string and clean the stream
        std::string key = ss_.str();
        cleanStream();

        return key;
    }

    std::string symmetric_encryption::makeNonce() {
        return random::generate_buffer(crypto_secretbox_NONCEBYTES);
    }

    std::string symmetric_encryption::decryptMessageDetached(const decryption_data_detached_t &data) {
        return decryptMessageDetached(
                data.authentication_tag,
                data.message,
                data.key,
                data.nonce
        );
    }

    std::string
    symmetric_encryption::decryptMessageDetached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &key,
            const std::string &nonce
    ) {
        cleanStream();

        // create the decryption buffer
        size_t decrypted_size = message.size();
        auto decrypted_buf = new unsigned char[decrypted_size];

        if (crypto_secretbox_open_detached(
                decrypted_buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                reinterpret_cast<const unsigned char *>(authentication_tag.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(decrypted_buf), (long) decrypted_size);
            delete[] decrypted_buf;
            return ss_.str();
        }
        delete[] decrypted_buf;
        throw exception::symmetric_message_decryption_exception();
    }

} // crypto