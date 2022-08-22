//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/encryption.h"

namespace abyss::crypto::symmetric::message {
    std::string make_encryption_key() {
        return symmetric_encryption::getInstance()->makeEncryptionKey();
    }

    std::string make_nonce() {
        return symmetric_encryption::getInstance()->makeNonce();
    }

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

namespace abyss::crypto::symmetric::auth {
    std::string make_key() {
        return symmetric_message_authentication::getInstance()->makeKey();
    }

    std::string compute(const std::string &message, const std::string &key) {
        return symmetric_message_authentication::getInstance()->computeAuthenticationTag(message, key);
    }

    bool
    verify(const std::string &tag, const std::string &message, const std::string &key) {
        return symmetric_message_authentication::getInstance()->verifyAuthenticationTag(tag, message, key);
    }
}

namespace abyss::crypto::symmetric::stream {
    std::string make_encryption_key() {
        return symmetric_stream::makeEncryptionKey();
    }

    std::shared_ptr<symmetric_stream> make_encryption_stream(const std::string &key) {
        return symmetric_stream::makeEncryptionStream(key);
    }

    std::shared_ptr<symmetric_stream>
    make_decryption_stream(const std::string &header, const std::string &key) {
        return symmetric_stream::makeDecryptionStream(header, key);
    }
}

namespace abyss::crypto::asymmetric::message {
    abyss::crypto::asymmetric::keypair_t make_keypair() {
        return asymmetric_encryption::getInstance()->makeKeypair();
    }

    abyss::crypto::asymmetric::keypair_t
    restore_public_key(const std::string &secret_key) {
        return asymmetric_encryption::getInstance()->restorePublicKey(secret_key);
    }

    void restore_public_key(abyss::crypto::asymmetric::keypair_t &partial_keypair) {
        asymmetric_encryption::getInstance()->restorePublicKey(partial_keypair);
    }

    abyss::crypto::asymmetric::transitional_keypair_t make_encryption_shared_keypair(
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->makeEncryptionSharedKeypair(sender_keypair, receiver_keypair);
    }

    abyss::crypto::asymmetric::transitional_keypair_t make_decryption_shared_keypair(
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->makeDecryptionSharedKeypair(sender_keypair, receiver_keypair);
    }

    std::string make_nonce() {
        return asymmetric_encryption::getInstance()->makeNonce();
    }

    abyss::crypto::asymmetric::encrypted_data_t encrypt(
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessage(message, nonce, sender_keypair, receiver_keypair);
    }

    abyss::crypto::asymmetric::encrypted_data_t encrypt(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return asymmetric_encryption::getInstance()->encryptMessage(
                message,
                nonce,
                sender_secret_key,
                receiver_public_key
        );
    }

    abyss::crypto::asymmetric::encrypted_data_t encrypt(
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::transitional_keypair_t &shared_key_pair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessage(message, nonce, shared_key_pair);
    }

    abyss::crypto::asymmetric::encrypted_data_t encrypt(
            const std::string &message,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessage(message, sender_keypair, receiver_keypair);
    }

    abyss::crypto::asymmetric::encrypted_data_t encrypt(
            const std::string &message,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return asymmetric_encryption::getInstance()->encryptMessage(message, sender_secret_key, receiver_public_key);
    }

    abyss::crypto::asymmetric::encrypted_data_t encrypt(
            const std::string &message,
            const abyss::crypto::asymmetric::transitional_keypair_t &shared_key_pair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessage(message, shared_key_pair);
    }

    std::string decrypt(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_public_key,
            const std::string &receiver_secret_key
    ) {
        return asymmetric_encryption::getInstance()->decryptMessage(
                message,
                nonce,
                sender_public_key,
                receiver_secret_key
        );
    }

    std::string decrypt(
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->decryptMessage(message, nonce, sender_keypair, receiver_keypair);
    }

    std::string decrypt(
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::transitional_keypair_t &shared_key_pair
    ) {
        return asymmetric_encryption::getInstance()->decryptMessage(message, nonce, shared_key_pair);
    }

    std::string decrypt(const abyss::crypto::asymmetric::decryption_data_t &data) {
        return asymmetric_encryption::getInstance()->decryptMessage(data);
    }

    abyss::crypto::asymmetric::encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessageDetached(
                message,
                nonce,
                sender_keypair,
                receiver_keypair
        );
    }

    abyss::crypto::asymmetric::encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return asymmetric_encryption::getInstance()->encryptMessageDetached(
                message,
                nonce,
                sender_secret_key,
                receiver_public_key
        );
    }

    abyss::crypto::asymmetric::encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::transitional_keypair_t &shared_key_pair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessageDetached(message, nonce, shared_key_pair);
    }

    abyss::crypto::asymmetric::encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessageDetached(message, sender_keypair, receiver_keypair);
    }

    abyss::crypto::asymmetric::encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return asymmetric_encryption::getInstance()->encryptMessageDetached(
                message,
                sender_secret_key,
                receiver_public_key
        );
    }

    abyss::crypto::asymmetric::encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const abyss::crypto::asymmetric::transitional_keypair_t &shared_key_pair
    ) {
        return asymmetric_encryption::getInstance()->encryptMessageDetached(message, shared_key_pair);
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_public_key,
            const std::string &receiver_secret_key
    ) {
        return asymmetric_encryption::getInstance()->decryptMessageDetached(
                authentication_tag,
                message,
                nonce,
                sender_public_key,
                receiver_secret_key
        );
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_encryption::getInstance()->decryptMessageDetached(
                authentication_tag,
                message,
                nonce,
                sender_keypair,
                receiver_keypair
        );
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const abyss::crypto::asymmetric::transitional_keypair_t &shared_key_pair
    ) {
        return asymmetric_encryption::getInstance()->decryptMessageDetached(
                authentication_tag,
                message,
                nonce,
                shared_key_pair
        );
    }

    std::string
    decrypt_detached(const abyss::crypto::asymmetric::decryption_data_detached_t &data) {
        return asymmetric_encryption::getInstance()->decryptMessageDetached(data);
    }
}

namespace abyss::crypto::asymmetric::auth {
    keypair_t make_key() {
        return asymmetric_message_authentication::getInstance()->makeKeypair();
    }

    std::string sign(const std::string &message, const std::string &secret_key) {
        return asymmetric_message_authentication::getInstance()->signMessage(message, secret_key);
    }

    std::string sign(
            const std::string &message,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair
    ) {
        return asymmetric_message_authentication::getInstance()->signMessage(message, sender_keypair);
    }

    abyss::crypto::asymmetric::signature_data_t
    verify(const std::string &message, const std::string &public_key) {
        return asymmetric_message_authentication::getInstance()->verifyMessage(message, public_key);
    }

    abyss::crypto::asymmetric::signature_data_t verify(
            const std::string &message,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_message_authentication::getInstance()->verifyMessage(message, receiver_keypair);
    }

    std::string sign_detached(
            const std::string &message,
            const abyss::crypto::asymmetric::keypair_t &sender_keypair
    ) {
        return asymmetric_message_authentication::getInstance()->signMessageDetached(message, sender_keypair);
    }

    std::string sign_detached(const std::string &message, const std::string &secret_key) {
        return asymmetric_message_authentication::getInstance()->signMessageDetached(message, secret_key);
    }

    bool verify_detached(
            const std::string &tag,
            const std::string &message,
            const abyss::crypto::asymmetric::keypair_t &receiver_keypair
    ) {
        return asymmetric_message_authentication::getInstance()->verifyMessageDetached(tag, message, receiver_keypair);
    }

    bool verify_detached(
            const std::string &tag,
            const std::string &message,
            const std::string &public_key
    ) {
        return asymmetric_message_authentication::getInstance()->verifyMessageDetached(tag, message, public_key);
    }
}