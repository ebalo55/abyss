//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanCreateAndVerifyMac) {
    auto key = abyss::crypto::symmetric::auth::make_key();
    auto mac = abyss::crypto::symmetric::auth::sign("test", key);

    /*std::cout << "key: " << abyss::crypto::encode::base64(key) << std::endl
              << "mac: " << abyss::crypto::encode::base64(mac) << std::endl
              << "message: " << abyss::crypto::encode::base64("test") << std::endl;*/

    EXPECT_TRUE(abyss::crypto::symmetric::auth::verify(mac, "test", key));
}


#endif //ABYSS_HELLO_TEST_CPP
