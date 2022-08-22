//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/symmetric_encryption.h"

namespace abyss::crypto::symmetric::message {
    encrypted_data_t encrypt(const std::string &message) {
        return encrypt(message, make_key());
    }

    encrypted_data_t
    encrypt(const std::string &message, const std::string &key) {
        return encrypt(message, key, make_nonce());
    }

    encrypted_data_t
    encrypt(const std::string &message, const std::string &key, const std::string &nonce) {
        std::stringstream ss;

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
            ss.write(reinterpret_cast<const char *>(encrypted_buf), (long) encrypted_size);
            delete[] encrypted_buf;
            return {ss.str(), key, nonce};
        }

        delete[] encrypted_buf;
        throw exception::symmetric_message_encryption_exception();
    }

    encrypted_data_t encrypt(const encryption_data_t &data) {
        return encrypt(data.message, data.key, data.nonce);
    }

    std::string decrypt(const decryption_data_t &data) {
        return decrypt(data.message, data.key, data.nonce);
    }

    std::string
    decrypt(const std::string &message, const std::string &key, const std::string &nonce) {
        std::stringstream ss;

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
            ss.write(reinterpret_cast<const char *>(decrypted_buf), (long) decrypted_size);
            delete[] decrypted_buf;
            return ss.str();
        }

        delete[] decrypted_buf;
        throw exception::symmetric_message_decryption_exception();
    }

    encrypted_data_detached_t encrypt_detached(const std::string &message) {
        return encrypt_detached(message, make_key());
    }

    encrypted_data_detached_t
    encrypt_detached(const std::string &message, const std::string &key) {
        return encrypt_detached(message, key, make_nonce());
    }

    encrypted_data_detached_t
    encrypt_detached(
            const std::string &message,
            const std::string &key,
            const std::string &nonce
    ) {
        std::stringstream ss;

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
            ss.write(reinterpret_cast<const char *>(encrypted_buf), (long) message.size());
            std::string encrypted_message = ss.str();
            delete[] encrypted_buf;
            ss.str("");

            // stream the tag and delete the tag buffer
            ss.write(reinterpret_cast<const char *>(tag_buf), (long) crypto_secretbox_MACBYTES);
            delete[] tag_buf;
            return {ss.str(), encrypted_message, key, nonce};
        }
        delete[] encrypted_buf;
        delete[] tag_buf;
        throw exception::symmetric_message_encryption_exception();
    }

    encrypted_data_detached_t encrypt_detached(const encryption_data_t &data) {
        return encrypt_detached(data.message, data.key, data.nonce);
    }

    std::string make_key() {
        std::stringstream ss;

        // creates the keygen
        auto key_buf = new unsigned char[crypto_secretbox_KEYBYTES];
        crypto_secretbox_keygen(key_buf);

        // insert the keygen in the stream and clean memory
        ss.write(reinterpret_cast<const char *>(key_buf), (long) crypto_secretbox_KEYBYTES);
        delete[] key_buf;

        // store the keygen as string and clean the stream
        std::string key = ss.str();
        ss.str("");

        return key;
    }

    std::string make_nonce() {
        return random::generate_buffer(crypto_secretbox_NONCEBYTES);
    }

    std::string decrypt_detached(const decryption_data_detached_t &data) {
        return decrypt_detached(
                data.authentication_tag,
                data.message,
                data.key,
                data.nonce
        );
    }

    std::string
    decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &key,
            const std::string &nonce
    ) {
        std::stringstream ss;

        // create the decryption buffer
        auto decrypted_buf = new unsigned char[message.size()];

        if (crypto_secretbox_open_detached(
                decrypted_buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                reinterpret_cast<const unsigned char *>(authentication_tag.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(decrypted_buf), (long) message.size());
            delete[] decrypted_buf;
            return ss.str();
        }

        delete[] decrypted_buf;
        throw exception::symmetric_message_decryption_exception();
    }

} // crypto