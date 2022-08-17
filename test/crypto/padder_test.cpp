//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto;

TEST(CryptoTest, CanPadAndUnpadStrings) {
    std::string padded = abyss::crypto::padder::getInstance()->pad("test", 16);
    EXPECT_EQ(abyss::crypto::encode::hex(padded), "74657374800000000000000000000000");
    std::string unpadded = abyss::crypto::padder::getInstance()->unpad(padded, 16);
    EXPECT_EQ(unpadded, "test");
}

#endif //ABYSS_HELLO_TEST_CPP
