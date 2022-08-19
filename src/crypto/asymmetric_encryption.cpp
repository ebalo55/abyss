//
// Created by ebalo on 18/08/22.
//

#include "abyss/crypto/asymmetric_encryption.h"

namespace abyss::crypto::asymmetric {
    std::shared_ptr<asymmetric_encryption> asymmetric_encryption::instance_ = nullptr;

    void asymmetric_encryption::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<asymmetric_encryption> asymmetric_encryption::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<asymmetric_encryption>(new asymmetric_encryption());
        }
        return instance_;
    }

    keypair_t asymmetric_encryption::makeKeypair() {
        auto public_key_buf = new unsigned char[crypto_box_PUBLICKEYBYTES];
        auto secret_key_buf = new unsigned char[crypto_box_SECRETKEYBYTES];

        crypto_box_keypair(public_key_buf, secret_key_buf);

        // cast buf to string
        cleanStream();
        ss_.write(reinterpret_cast<const char *>(public_key_buf), (long) crypto_box_PUBLICKEYBYTES);
        std::string public_key = ss_.str();
        delete[] public_key_buf;

        // cast buf to string
        cleanStream();
        ss_.write(reinterpret_cast<const char *>(secret_key_buf), (long) crypto_box_SECRETKEYBYTES);
        std::string secret_key = ss_.str();
        delete[] secret_key_buf;
        cleanStream();
        return {.public_key = public_key, .secret_key = secret_key};
    }

    transitional_keypair_t asymmetric_encryption::makeEncryptionSharedKeypair(
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return {.public_key = receiver_keypair.public_key, .secret_key = sender_keypair.secret_key};
    }

    transitional_keypair_t asymmetric_encryption::makeDecryptionSharedKeypair(
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return {.public_key = sender_keypair.public_key, .secret_key = receiver_keypair.secret_key};
    }

    std::string asymmetric_encryption::makeNonce() {
        return random::generate_buffer(crypto_box_noncebytes());
    }

    encrypted_data_t asymmetric_encryption::encryptMessage(
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encryptMessage(message, nonce, sender_keypair.secret_key, receiver_keypair.public_key);
    }

    encrypted_data_t asymmetric_encryption::encryptMessage(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        cleanStream();
        size_t encrypted_size = message.size() + crypto_box_MACBYTES;
        auto buf = new unsigned char[encrypted_size];

        if (crypto_box_easy(
                buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(receiver_public_key.c_str()),
                reinterpret_cast<const unsigned char *>(sender_secret_key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(buf), (long) encrypted_size);
            delete[] buf;
            return {
                    .message = ss_.str(),
                    .nonce = nonce,
                    .keypair = {
                            .public_key = receiver_public_key,
                            .secret_key = sender_secret_key
                    }
            };
        }

        delete[] buf;
        throw exception::asymmetric_encryption_exception();
    }

    encrypted_data_t asymmetric_encryption::encryptMessage(
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return encryptMessage(message, nonce, shared_key_pair.secret_key, shared_key_pair.public_key);
    }

    encrypted_data_t asymmetric_encryption::encryptMessage(
            const std::string &message,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encryptMessage(message, makeNonce(), sender_keypair, receiver_keypair);
    }

    encrypted_data_t
    asymmetric_encryption::encryptMessage(
            const std::string &message,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return encryptMessage(message, makeNonce(), sender_secret_key, receiver_public_key);
    }

    encrypted_data_t
    asymmetric_encryption::encryptMessage(const std::string &message, const transitional_keypair_t &shared_key_pair) {
        return encryptMessage(message, makeNonce(), shared_key_pair);
    }

    std::string asymmetric_encryption::decryptMessage(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_public_key,
            const std::string &receiver_secret_key
    ) {
        cleanStream();

        size_t plain_size = message.size() - crypto_box_MACBYTES;
        auto buf = new unsigned char[plain_size];

        if (crypto_box_open_easy(
                buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(sender_public_key.c_str()),
                reinterpret_cast<const unsigned char *>(receiver_secret_key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(buf), (long) plain_size);
            delete[] buf;
            return ss_.str();
        }

        delete[] buf;
        throw exception::asymmetric_decryption_exception();
    }

    std::string asymmetric_encryption::decryptMessage(
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return decryptMessage(message, nonce, sender_keypair.public_key, receiver_keypair.secret_key);
    }

    std::string asymmetric_encryption::decryptMessage(
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return decryptMessage(message, nonce, shared_key_pair.public_key, shared_key_pair.secret_key);
    }

    std::string asymmetric_encryption::decryptMessage(const decryption_data_t &data) {
        return decryptMessage(data.message, data.nonce, data.keypair);
    }

    keypair_t asymmetric_encryption::restorePublicKey(const std::string &secret_key) {
        cleanStream();
        auto public_key = new unsigned char[crypto_box_PUBLICKEYBYTES];
        crypto_scalarmult_base(public_key, reinterpret_cast<const unsigned char *>(secret_key.c_str()));

        ss_.write(reinterpret_cast<const char *>(public_key), (long) crypto_box_PUBLICKEYBYTES);
        delete[] public_key;
        return {.public_key = ss_.str(), .secret_key = secret_key};
    }

    void asymmetric_encryption::restorePublicKey(keypair_t &partial_keypair) {
        partial_keypair = restorePublicKey(partial_keypair.secret_key);
    }

    encrypted_data_detached_t asymmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encryptMessageDetached(message, nonce, sender_keypair.secret_key, receiver_keypair.public_key);
    }

    encrypted_data_detached_t asymmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        cleanStream();
        auto buf = new unsigned char[message.size()];
        auto mac = new unsigned char[crypto_box_MACBYTES];

        if (crypto_box_detached(
                buf,
                mac,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(receiver_public_key.c_str()),
                reinterpret_cast<const unsigned char *>(sender_secret_key.c_str())
        ) == 0) {
            // stream and clear the encrypted text
            ss_.write(reinterpret_cast<const char *>(buf), (long) message.size());
            delete[] buf;
            std::string encrypted_msg = ss_.str();

            // stream and clear the mac
            cleanStream();
            ss_.write(reinterpret_cast<const char *>(mac), (long) crypto_box_MACBYTES);
            delete[] mac;

            return {
                    .authentication_tag = ss_.str(),
                    .message = encrypted_msg,
                    .nonce = nonce,
                    .keypair = {
                            .public_key = receiver_public_key,
                            .secret_key = sender_secret_key
                    }
            };
        }

        delete[] buf;
        delete[] mac;
        throw exception::asymmetric_encryption_exception();
    }

    encrypted_data_detached_t asymmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return encryptMessageDetached(message, nonce, shared_key_pair.secret_key, shared_key_pair.public_key);
    }

    encrypted_data_detached_t asymmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encryptMessageDetached(message, makeNonce(), sender_keypair, receiver_keypair);
    }

    encrypted_data_detached_t asymmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return encryptMessageDetached(message, makeNonce(), sender_secret_key, receiver_public_key);
    }

    encrypted_data_detached_t asymmetric_encryption::encryptMessageDetached(
            const std::string &message,
            const transitional_keypair_t &shared_key_pair
    ) {
        return encryptMessageDetached(message, makeNonce(), shared_key_pair);
    }

    std::string asymmetric_encryption::decryptMessageDetached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_public_key,
            const std::string &receiver_secret_key
    ) {
        cleanStream();

        auto buf = new unsigned char[message.size()];

        if (crypto_box_open_detached(
                buf,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                reinterpret_cast<const unsigned char *>(authentication_tag.c_str()),
                message.size(),
                reinterpret_cast<const unsigned char *>(nonce.c_str()),
                reinterpret_cast<const unsigned char *>(sender_public_key.c_str()),
                reinterpret_cast<const unsigned char *>(receiver_secret_key.c_str())
        ) == 0) {
            ss_.write(reinterpret_cast<const char *>(buf), (long) message.size());
            delete[] buf;
            return ss_.str();
        }

        delete[] buf;
        throw exception::asymmetric_decryption_exception();
    }

    std::string asymmetric_encryption::decryptMessageDetached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return decryptMessageDetached(
                authentication_tag,
                message,
                nonce,
                sender_keypair.public_key,
                receiver_keypair.secret_key
        );
    }

    std::string asymmetric_encryption::decryptMessageDetached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return decryptMessageDetached(
                authentication_tag,
                message,
                nonce,
                shared_key_pair.public_key,
                shared_key_pair.secret_key
        );
    }

    std::string asymmetric_encryption::decryptMessageDetached(const decryption_data_detached_t &data) {
        return decryptMessageDetached(data.authentication_tag, data.message, data.nonce, data.keypair);
    }
} // crypto