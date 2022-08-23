//
// Created by ebalo on 22/08/22.
//

#ifndef ABYSS_KEY_EXCHANGE_H
#define ABYSS_KEY_EXCHANGE_H

#include <sstream>
#include <string>
#include <sodium.h>

#include "abyss/crypto/types.h"
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto::key_exchange {
    /**
     * Generates a random valid keypair
     * @return Keypair
     */
    keypair_t make_keypair();

    /**
     * Compute two shared keys using the server's public key and the client's secret key.
     * @param client_secret_key Client secret key
     * @param client_public_key Client public key
     * @param server_public_key Server public key
     * @return Shared keypair, the appropriate key can be used to send/receive messages from the server using the
     *  symmetric API
     */
    exchanged_keypair_t create_client_session(
            const std::string &client_secret_key,
            const std::string &client_public_key,
            const std::string &server_public_key
    );

    /**
     * Compute two shared keys using the server's public key and the client's secret key.
     * @param client_keypair Client keypair
     * @param server_public_key Server public key
     * @return Shared keypair, the appropriate key can be used to send/receive messages from the server using the
     *  symmetric API
     */
    exchanged_keypair_t create_client_session(
            const keypair_t &client_keypair,
            const std::string &server_public_key
    );

    /**
     * Compute two shared keys using the client's public key and the server's secret key.
     * @param server_secret_key Server secret key
     * @param server_public_key Server public key
     * @param client_public_key Client public key
     * @return Shared keypair, the appropriate key can be used to send/receive messages from the server using the
     *  symmetric API
     */
    exchanged_keypair_t create_server_session(
            const std::string &server_secret_key,
            const std::string &server_public_key,
            const std::string &client_public_key
    );

    /**
     * Compute two shared keys using the client's public key and the server's secret key.
     * @param server_keypair Server keypair
     * @param client_public_key Client public key
     * @return Shared keypair, the appropriate key can be used to send/receive messages from the server using the
     *  symmetric API
     */
    exchanged_keypair_t create_server_session(
            const keypair_t &server_keypair,
            const std::string &client_public_key
    );
} // key_exchange

#endif //ABYSS_KEY_EXCHANGE_H
