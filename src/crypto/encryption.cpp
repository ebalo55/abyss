//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/encryption.h"

namespace abyss::crypto::symmetric::message {
    encrypted_data_t encrypt(const std::string &message) {
        return symmetric_encryption::getInstance()->encryptMessage(message);
    }

    encrypted_data_t encrypt(const std::string &message, const std::string &key) {
        return symmetric_encryption::getInstance()->encryptMessage(message, key);
    }

    encrypted_data_t encrypt(const std::string &message, const std::string &key, const std::string &nonce) {
        return symmetric_encryption::getInstance()->encryptMessage(message, key, nonce);
    }

    encrypted_data_t encrypt(const encryption_data_t &data) {
        return symmetric_encryption::getInstance()->encryptMessage(data);
    }

    encrypted_data_detached_t encrypt_detached(const std::string &message) {
        return symmetric_encryption::getInstance()->encryptMessageDetached(message);
    }

    encrypted_data_detached_t encrypt_detached(const std::string &message, const std::string &key) {
        return symmetric_encryption::getInstance()->encryptMessageDetached(message, key);
    }

    encrypted_data_detached_t
    encrypt_detached(const std::string &message, const std::string &key, const std::string &nonce) {
        return symmetric_encryption::getInstance()->encryptMessageDetached(message, key, nonce);
    }

    encrypted_data_detached_t encrypt_detached(const encryption_data_t &data) {
        return symmetric_encryption::getInstance()->encryptMessageDetached(data);
    }

    std::string decrypt(const decryption_data_t &data) {
        return symmetric_encryption::getInstance()->decryptMessage(data);
    }

    std::string decrypt(const std::string &message, const std::string &key, const std::string &nonce) {
        return symmetric_encryption::getInstance()->decryptMessage(message, key, nonce);
    }

    std::string decrypt_detached(const decryption_data_detached_t &data) {
        return symmetric_encryption::getInstance()->decryptMessageDetached(data);
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &key,
            const std::string &nonce
    ) {
        return symmetric_encryption::getInstance()->decryptMessageDetached(authentication_tag, message, key, nonce);
    }
}