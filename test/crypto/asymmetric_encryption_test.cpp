//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanEncryptAndDecryptSingleMessagesUsingAsymmetricEncryption) {
    auto sender_kp = abyss::crypto::asymmetric::message::make_keypair();
    auto receiver_kp = abyss::crypto::asymmetric::message::make_keypair();

    auto encrypted_message = abyss::crypto::asymmetric::message::encrypt("test", sender_kp, receiver_kp);

    /*std::cout << "sender secret key: " << abyss::crypto::encode::base64(encrypted_message.keypair.secret_key) << std::endl
              << "receiver public key: " << abyss::crypto::encode::base64(encrypted_message.keypair.public_key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::asymmetric::message::decrypt(encrypted_message);
    EXPECT_EQ(decrypted_message, "test");
}

TEST(CryptoTest, CanEncryptAndDecryptSingleMessagesUsingAsymmetricEncryptionDetached) {
    auto sender_kp = abyss::crypto::asymmetric::message::make_keypair();
    auto receiver_kp = abyss::crypto::asymmetric::message::make_keypair();

    auto encrypted_message = abyss::crypto::asymmetric::message::encrypt_detached("test", sender_kp, receiver_kp);

    /*std::cout << "sender secret key: " << abyss::crypto::encode::base64(encrypted_message.keypair.secret_key) << std::endl
              << "receiver public key: " << abyss::crypto::encode::base64(encrypted_message.keypair.public_key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "mac: " << abyss::crypto::encode::base64(encrypted_message.authentication_tag) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::asymmetric::message::decrypt_detached(encrypted_message);
    EXPECT_EQ(decrypted_message, "test");
}

TEST(CryptoTest, CanEncryptAndDecryptBinarySingleMessagesUsingAsymmetricEncryption) {
    auto sender_kp = abyss::crypto::asymmetric::message::make_keypair();
    auto receiver_kp = abyss::crypto::asymmetric::message::make_keypair();

    std::string binary_string = abyss::crypto::random::generate_buffer(128);

    auto encrypted_message = abyss::crypto::asymmetric::message::encrypt(binary_string, sender_kp, receiver_kp);

    /*std::cout << "sender secret key: " << abyss::crypto::encode::base64(encrypted_message.keypair.secret_key) << std::endl
              << "receiver public key: " << abyss::crypto::encode::base64(encrypted_message.keypair.public_key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::asymmetric::message::decrypt(encrypted_message);
    EXPECT_EQ(decrypted_message, binary_string);
}

TEST(CryptoTest, CanEncryptAndDecryptBinarySingleMessagesUsingAsymmetricEncryptionDetached) {
    auto sender_kp = abyss::crypto::asymmetric::message::make_keypair();
    auto receiver_kp = abyss::crypto::asymmetric::message::make_keypair();

    std::string binary_string = abyss::crypto::random::generate_buffer(128);

    auto encrypted_message = abyss::crypto::asymmetric::message::encrypt_detached(binary_string, sender_kp, receiver_kp);

    /*std::cout << "sender secret key: " << abyss::crypto::encode::base64(encrypted_message.keypair.secret_key) << std::endl
              << "receiver public key: " << abyss::crypto::encode::base64(encrypted_message.keypair.public_key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "mac: " << abyss::crypto::encode::base64(encrypted_message.authentication_tag) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::asymmetric::message::decrypt_detached(encrypted_message);
    EXPECT_EQ(decrypted_message, binary_string);
}


#endif //ABYSS_HELLO_TEST_CPP
