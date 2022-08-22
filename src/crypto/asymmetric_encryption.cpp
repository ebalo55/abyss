//
// Created by ebalo on 18/08/22.
//

#include "abyss/crypto/asymmetric_encryption.h"

namespace abyss::crypto::asymmetric::message {
    keypair_t make_keypair() {
        std::stringstream ss;
        auto public_key_buf = new unsigned char[crypto_box_PUBLICKEYBYTES];
        auto secret_key_buf = new unsigned char[crypto_box_SECRETKEYBYTES];

        crypto_box_keypair(public_key_buf, secret_key_buf);

        // cast buf to string
        ss.write(reinterpret_cast<const char *>(public_key_buf), (long) crypto_box_PUBLICKEYBYTES);
        std::string public_key = ss.str();
        delete[] public_key_buf;
        ss.str("");

        // cast buf to string
        ss.write(reinterpret_cast<const char *>(secret_key_buf), (long) crypto_box_SECRETKEYBYTES);
        std::string secret_key = ss.str();
        delete[] secret_key_buf;
        ss.str("");

        return {.public_key = public_key, .secret_key = secret_key};
    }

    transitional_keypair_t make_encryption_shared_keypair(
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return {.public_key = receiver_keypair.public_key, .secret_key = sender_keypair.secret_key};
    }

    transitional_keypair_t make_decryption_shared_keypair(
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return {.public_key = sender_keypair.public_key, .secret_key = receiver_keypair.secret_key};
    }

    std::string make_nonce() {
        return random::generate_buffer(crypto_box_NONCEBYTES);
    }

    encrypted_data_t encrypt(
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encrypt(message, nonce, sender_keypair.secret_key, receiver_keypair.public_key);
    }

    encrypted_data_t encrypt(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        std::stringstream ss;
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
            ss.write(reinterpret_cast<const char *>(buf), (long) encrypted_size);
            delete[] buf;
            return {
                    .message = ss.str(),
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

    encrypted_data_t encrypt(
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return encrypt(message, nonce, shared_key_pair.secret_key, shared_key_pair.public_key);
    }

    encrypted_data_t encrypt(
            const std::string &message,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encrypt(message, make_nonce(), sender_keypair, receiver_keypair);
    }

    encrypted_data_t
    encrypt(
            const std::string &message,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return encrypt(message, make_nonce(), sender_secret_key, receiver_public_key);
    }

    encrypted_data_t
    encrypt(const std::string &message, const transitional_keypair_t &shared_key_pair) {
        return encrypt(message, make_nonce(), shared_key_pair);
    }

    std::string decrypt(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_public_key,
            const std::string &receiver_secret_key
    ) {
        std::stringstream ss;

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
            ss.write(reinterpret_cast<const char *>(buf), (long) plain_size);
            delete[] buf;
            return ss.str();
        }

        delete[] buf;
        throw exception::asymmetric_decryption_exception();
    }

    std::string decrypt(
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return decrypt(message, nonce, sender_keypair.public_key, receiver_keypair.secret_key);
    }

    std::string decrypt(
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return decrypt(message, nonce, shared_key_pair.public_key, shared_key_pair.secret_key);
    }

    std::string decrypt(const decryption_data_t &data) {
        return decrypt(data.message, data.nonce, data.keypair);
    }

    keypair_t restore_public_key(const std::string &secret_key) {
        std::stringstream ss;
        auto public_key = new unsigned char[crypto_box_PUBLICKEYBYTES];
        crypto_scalarmult_base(public_key, reinterpret_cast<const unsigned char *>(secret_key.c_str()));

        ss.write(reinterpret_cast<const char *>(public_key), (long) crypto_box_PUBLICKEYBYTES);
        delete[] public_key;
        return {.public_key = ss.str(), .secret_key = secret_key};
    }

    void restore_public_key(keypair_t &partial_keypair) {
        partial_keypair = restore_public_key(partial_keypair.secret_key);
    }

    encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encrypt_detached(message, nonce, sender_keypair.secret_key, receiver_keypair.public_key);
    }

    encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        std::stringstream ss;
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
            ss.write(reinterpret_cast<const char *>(buf), (long) message.size());
            delete[] buf;
            std::string encrypted_msg = ss.str();

            // stream and clear the mac
            ss.str("");
            ss.write(reinterpret_cast<const char *>(mac), (long) crypto_box_MACBYTES);
            delete[] mac;

            return {
                    .authentication_tag = ss.str(),
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

    encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return encrypt_detached(message, nonce, shared_key_pair.secret_key, shared_key_pair.public_key);
    }

    encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return encrypt_detached(message, make_nonce(), sender_keypair, receiver_keypair);
    }

    encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const std::string &sender_secret_key,
            const std::string &receiver_public_key
    ) {
        return encrypt_detached(message, make_nonce(), sender_secret_key, receiver_public_key);
    }

    encrypted_data_detached_t encrypt_detached(
            const std::string &message,
            const transitional_keypair_t &shared_key_pair
    ) {
        return encrypt_detached(message, make_nonce(), shared_key_pair);
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const std::string &sender_public_key,
            const std::string &receiver_secret_key
    ) {
        std::stringstream ss;
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
            ss.write(reinterpret_cast<const char *>(buf), (long) message.size());
            delete[] buf;
            return ss.str();
        }

        delete[] buf;
        throw exception::asymmetric_decryption_exception();
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const keypair_t &sender_keypair,
            const keypair_t &receiver_keypair
    ) {
        return decrypt_detached(
                authentication_tag,
                message,
                nonce,
                sender_keypair.public_key,
                receiver_keypair.secret_key
        );
    }

    std::string decrypt_detached(
            const std::string &authentication_tag,
            const std::string &message,
            const std::string &nonce,
            const transitional_keypair_t &shared_key_pair
    ) {
        return decrypt_detached(
                authentication_tag,
                message,
                nonce,
                shared_key_pair.public_key,
                shared_key_pair.secret_key
        );
    }

    std::string decrypt_detached(const decryption_data_detached_t &data) {
        return decrypt_detached(data.authentication_tag, data.message, data.nonce, data.keypair);
    }
} // crypto