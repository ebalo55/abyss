//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"


TEST(CryptoTest, CanEncryptAndDecryptSingleMessagesUsingSymmetricEncryption) {
    auto encrypted_message = abyss::crypto::symmetric::message::encrypt("test");
    /*std::cout << "key: " << abyss::crypto::encode::_base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::_base64(encrypted_message.nonce) << std::endl
              << "_message: " << abyss::crypto::encode::_base64(encrypted_message._message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric::message::decrypt(encrypted_message);
    EXPECT_EQ(decrypted_message, "test");
}

TEST(CryptoTest, CanEncryptAndDecryptSingleMessagesUsingSymmetricEncryptionDetached) {
    auto encrypted_message = abyss::crypto::symmetric::message::encrypt_detached("test");
    /*std::cout << "key: " << abyss::crypto::encode::_base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::_base64(encrypted_message.nonce) << std::endl
              << "mac: " << abyss::crypto::encode::_base64(encrypted_message.authentication_tag) << std::endl
              << "_message: " << abyss::crypto::encode::_base64(encrypted_message._message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric::message::decrypt_detached(encrypted_message);
    EXPECT_EQ(decrypted_message, "test");
}

TEST(CryptoTest, CanEncryptAndDecryptBinarySingleMessagesUsingSymmetricEncryption) {
    std::string binary_string = abyss::crypto::random::generate_buffer(128);
    auto encrypted_message = abyss::crypto::symmetric::message::encrypt(binary_string);
    /*std::cout << "key: " << abyss::crypto::encode::_base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::_base64(encrypted_message.nonce) << std::endl
              << "_message: " << abyss::crypto::encode::_base64(encrypted_message._message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric::message::decrypt(encrypted_message);
    EXPECT_EQ(decrypted_message, binary_string);
}

TEST(CryptoTest, CanEncryptAndDecryptBinarySingleMessagesUsingSymmetricEncryptionDetached) {
    std::string binary_string = abyss::crypto::random::generate_buffer(128);
    auto encrypted_message = abyss::crypto::symmetric::message::encrypt_detached(binary_string);
    /*std::cout << "key: " << abyss::crypto::encode::_base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::_base64(encrypted_message.nonce) << std::endl
              << "mac: " << abyss::crypto::encode::_base64(encrypted_message.authentication_tag) << std::endl
              << "_message: " << abyss::crypto::encode::_base64(encrypted_message._message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric::message::decrypt_detached(encrypted_message);
    EXPECT_EQ(decrypted_message, binary_string);
}


#endif //ABYSS_HELLO_TEST_CPP
