//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto;

TEST(CryptoTest, CanEncryptAndDecryptSingleMessagesUsingSymmetricEncryption) {
    auto encrypted_message = abyss::crypto::symmetric_encryption::getInstance()->encryptMessage("test");
    /*std::cout << "key: " << abyss::crypto::encode::base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric_encryption::getInstance()
            ->decryptMessage(encrypted_message);
    EXPECT_EQ(decrypted_message, "test");
}

TEST(CryptoTest, CanEncryptAndDecryptSingleMessagesUsingSymmetricEncryptionDetached) {
    auto encrypted_message = abyss::crypto::symmetric_encryption::getInstance()->encryptMessageDetached("test");
    /*std::cout << "key: " << abyss::crypto::encode::base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "mac: " << abyss::crypto::encode::base64(encrypted_message.authentication_tag) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric_encryption::getInstance()
            ->decryptMessageDetached(encrypted_message);
    EXPECT_EQ(decrypted_message, "test");
}

TEST(CryptoTest, CanEncryptAndDecryptBinarySingleMessagesUsingSymmetricEncryption) {
    std::string binary_string = abyss::crypto::random::generate_buffer(128);
    auto encrypted_message = abyss::crypto::symmetric_encryption::getInstance()
            ->encryptMessage(binary_string);
    /*std::cout << "key: " << abyss::crypto::encode::base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric_encryption::getInstance()
            ->decryptMessage(encrypted_message);
    EXPECT_EQ(decrypted_message, binary_string);
}

TEST(CryptoTest, CanEncryptAndDecryptBinarySingleMessagesUsingSymmetricEncryptionDetached) {
    std::string binary_string = abyss::crypto::random::generate_buffer(128);
    auto encrypted_message = abyss::crypto::symmetric_encryption::getInstance()
            ->encryptMessageDetached(binary_string);
    /*std::cout << "key: " << abyss::crypto::encode::base64(encrypted_message.key) << std::endl
              << "nonce: " << abyss::crypto::encode::base64(encrypted_message.nonce) << std::endl
              << "mac: " << abyss::crypto::encode::base64(encrypted_message.authentication_tag) << std::endl
              << "message: " << abyss::crypto::encode::base64(encrypted_message.message) << std::endl;*/

    auto decrypted_message = abyss::crypto::symmetric_encryption::getInstance()
            ->decryptMessageDetached(encrypted_message);
    EXPECT_EQ(decrypted_message, binary_string);
}


#endif //ABYSS_HELLO_TEST_CPP
