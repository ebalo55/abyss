//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanExchangeKeyAndStartSymmetricEncryptionWithSharedKeys) {
    auto keypair_client = abyss::crypto::key_exchange::make_keypair();
    auto keypair_server = abyss::crypto::key_exchange::make_keypair();
    auto client_session_keys = abyss::crypto::key_exchange::create_client_session(
            keypair_client,
            keypair_server.public_key
    );
    auto server_session_keys = abyss::crypto::key_exchange::create_server_session(
            keypair_server,
            keypair_client.public_key
    );

    auto nonce = abyss::crypto::symmetric::message::make_nonce();
    auto encrypted_from_client_to_server = abyss::crypto::symmetric::message::encrypt(
            "test",
            client_session_keys.sending_key,
            nonce
    );
    auto decrypted_from_client_to_server = abyss::crypto::symmetric::message::decrypt(
            encrypted_from_client_to_server.message,
            server_session_keys.receiving_key,
            nonce
    );

    /*std::cout
            << "client public key: "
            << abyss::crypto::encode::base64(keypair_client.public_key)
            << std::endl
            << "client secret key: "
            << abyss::crypto::encode::base64(keypair_client.secret_key)
            << std::endl
            << "server public key: "
            << abyss::crypto::encode::base64(keypair_server.public_key)
            << std::endl
            << "server secret key: "
            << abyss::crypto::encode::base64(keypair_server.secret_key)
            << std::endl
            << "client shared session key - sending: "
            << abyss::crypto::encode::base64(client_session_keys.sending_key)
            << std::endl
            << "client shared session key - receiving: "
            << abyss::crypto::encode::base64(client_session_keys.receiving_key)
            << std::endl
            << "server shared session key - sending: "
            << abyss::crypto::encode::base64(server_session_keys.sending_key)
            << std::endl
            << "server shared session key - receiving: "
            << abyss::crypto::encode::base64(server_session_keys.receiving_key)
            << std::endl;*/

    EXPECT_EQ(decrypted_from_client_to_server, "test");
}

#endif //ABYSS_HELLO_TEST_CPP
