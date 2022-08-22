//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanCreateAndVerifyAsymmetricMac) {
    auto key = abyss::crypto::asymmetric::auth::make_keypair();
    auto mac = abyss::crypto::asymmetric::auth::sign("test", key);

    /*std::cout << "secret key: " << abyss::crypto::encode::base64(key.secret_key) << std::endl
              << "public key: " << abyss::crypto::encode::base64(key.public_key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;*/


    auto signature_result = abyss::crypto::asymmetric::auth::verify(mac, key);
    EXPECT_TRUE(signature_result.verified);
    EXPECT_EQ(signature_result.message, "test");
}

TEST(CryptoTest, CanCreateAndVerifyAsymmetricMacDetached) {
    auto key = abyss::crypto::asymmetric::auth::make_keypair();
    auto mac = abyss::crypto::asymmetric::auth::sign_detached("test", key);

    /*std::cout << "secret key: " << abyss::crypto::encode::base64(key.secret_key) << std::endl
              << "public key: " << abyss::crypto::encode::base64(key.public_key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;*/

    auto signature_result = abyss::crypto::asymmetric::auth::verify_detached(mac, "test", key);
    EXPECT_TRUE(signature_result);
}


#endif //ABYSS_HELLO_TEST_CPP
