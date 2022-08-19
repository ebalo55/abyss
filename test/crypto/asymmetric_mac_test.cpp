//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto::asymmetric;

TEST(CryptoTest, CanCreateAndVerifyMac) {
    auto key = asymmetric_message_authentication::getInstance()->makeKeypair();
    auto mac = asymmetric_message_authentication::getInstance()
            ->signMessage("test", key);

    /**
     * TODO: complete asymmetric mac test
     * TODO: start hashing implementation
     * TODO: start password hashing implementation
     * TODO: start key derivation implementation
     * TODO: start key exchange implementation
     */

    std::cout << "secret key: " << abyss::crypto::encode::base64(key.secret_key) << std::endl
              << "public key: " << abyss::crypto::encode::base64(key.public_key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;

    EXPECT_TRUE(symmetric_message_authentication::getInstance()
                        ->verifyAuthenticationTag(mac, "test", key));
}


#endif //ABYSS_HELLO_TEST_CPP
