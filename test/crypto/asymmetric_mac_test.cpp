//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto::asymmetric;

TEST(CryptoTest, CanCreateAndVerifyAsymmetricMac) {
    auto key = asymmetric_message_authentication::getInstance()->makeKeypair();
    auto mac = asymmetric_message_authentication::getInstance()
            ->signMessage("test", key);

    /*std::cout << "secret key: " << abyss::crypto::encode::base64(key.secret_key) << std::endl
              << "public key: " << abyss::crypto::encode::base64(key.public_key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;*/


    auto signature_result = asymmetric_message_authentication::getInstance()
            ->verifyMessage(mac, key);
    EXPECT_TRUE(signature_result.verified);
    EXPECT_EQ(signature_result.message, "test");
}

TEST(CryptoTest, CanCreateAndVerifyAsymmetricMacDetached) {
    auto key = asymmetric_message_authentication::getInstance()->makeKeypair();
    auto mac = asymmetric_message_authentication::getInstance()
            ->signMessageDetached("test", key);

    /*std::cout << "secret key: " << abyss::crypto::encode::base64(key.secret_key) << std::endl
              << "public key: " << abyss::crypto::encode::base64(key.public_key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;*/

    auto signature_result = asymmetric_message_authentication::getInstance()
            ->verifyMessageDetached(mac, "test", key);
    EXPECT_TRUE(signature_result);
}


#endif //ABYSS_HELLO_TEST_CPP
