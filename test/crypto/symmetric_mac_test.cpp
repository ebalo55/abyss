//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto;

TEST(CryptoTest, CanCreateAndVerifyMac) {
    auto key = abyss::crypto::symmetric_message_authentication::getInstance()->makeKey();
    auto mac = abyss::crypto::symmetric_message_authentication::getInstance()
            ->computeAuthenticationTag("test", key);

    /*std::cout << "key: " << abyss::crypto::encode::base64(key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;*/

    EXPECT_TRUE(abyss::crypto::symmetric_message_authentication::getInstance()
                        ->verifyAuthenticationTag(mac, "test", key));
}


#endif //ABYSS_HELLO_TEST_CPP
