//
// Created by ebalo on 22/08/22.
//

#include "abyss/crypto/key_exchange.h"

namespace abyss::crypto::key_exchange {
    keypair_t make_keypair() {
        std::stringstream ss;
        auto public_key_buf = new unsigned char[crypto_box_PUBLICKEYBYTES];
        auto secret_key_buf = new unsigned char[crypto_box_SECRETKEYBYTES];

        crypto_kx_keypair(public_key_buf, secret_key_buf);

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

    exchanged_keypair_t create_client_session(
            const std::string &client_secret_key,
            const std::string &client_public_key,
            const std::string &server_public_key
    ) {
        std::stringstream ss;
        auto receiving_key = new unsigned char[crypto_kx_SESSIONKEYBYTES];
        auto sending_key = new unsigned char[crypto_kx_SESSIONKEYBYTES];

        if (crypto_kx_client_session_keys(
                receiving_key,
                sending_key,
                reinterpret_cast<const unsigned char *>(client_public_key.c_str()),
                reinterpret_cast<const unsigned char *>(client_secret_key.c_str()),
                reinterpret_cast<const unsigned char *>(server_public_key.c_str())
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(receiving_key), crypto_kx_SESSIONKEYBYTES);
            std::string receiving_k = ss.str();
            ss.str("");
            delete[] receiving_key;

            ss.write(reinterpret_cast<const char *>(sending_key), crypto_kx_SESSIONKEYBYTES);
            std::string sending_k = ss.str();
            ss.str("");
            delete[] sending_key;

            return {
                .receiving_key = receiving_k,
                .sending_key = sending_k
            };
        }

        delete[] receiving_key;
        delete[] sending_key;
        throw exception::key_exchange_invalid_server_public_key_exception();
    }

    exchanged_keypair_t
    create_client_session(const keypair_t &client_keypair, const std::string &server_public_key) {
        return create_client_session(client_keypair.secret_key, client_keypair.public_key, server_public_key);
    }

    exchanged_keypair_t create_server_session(
            const std::string &server_secret_key,
            const std::string &server_public_key,
            const std::string &client_public_key
    ) {
        std::stringstream ss;
        auto receiving_key = new unsigned char[crypto_kx_SESSIONKEYBYTES];
        auto sending_key = new unsigned char[crypto_kx_SESSIONKEYBYTES];

        if (crypto_kx_server_session_keys(
                receiving_key,
                sending_key,
                reinterpret_cast<const unsigned char *>(server_public_key.c_str()),
                reinterpret_cast<const unsigned char *>(server_secret_key.c_str()),
                reinterpret_cast<const unsigned char *>(client_public_key.c_str())
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(receiving_key), crypto_kx_SESSIONKEYBYTES);
            std::string receiving_k = ss.str();
            ss.str("");
            delete[] receiving_key;

            ss.write(reinterpret_cast<const char *>(sending_key), crypto_kx_SESSIONKEYBYTES);
            std::string sending_k = ss.str();
            ss.str("");
            delete[] sending_key;

            return {
                    .receiving_key = receiving_k,
                    .sending_key = sending_k
            };
        }

        delete[] receiving_key;
        delete[] sending_key;
        throw exception::key_exchange_invalid_client_public_key_exception();
    }

    exchanged_keypair_t
    create_server_session(const keypair_t &server_keypair, const std::string &client_public_key) {
        return create_server_session(server_keypair.secret_key, server_keypair.public_key, client_public_key);
    }
} // key_exchange