//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto;

TEST(CryptoTest, CanGenerateArbitraryHighNumber) {
    uint32_t v = abyss::crypto::random::generate();
    EXPECT_LE(v, 0xffffffff);
    EXPECT_GE(v, 0);
}

TEST(CryptoTest, CanGenerateNonUniformRandomNumber) {
    uint32_t v = abyss::crypto::random::generate(128);
    EXPECT_LE(v, 128);
    EXPECT_GE(v, 0);
}

TEST(CryptoTest, CanGenerateUniformRandomNumber) {
    uint32_t v = abyss::crypto::random::generate(128);
    EXPECT_LE(v, 128);
    EXPECT_GE(v, 0);
}

TEST(CryptoTest, CanGenerateRandomBuffer) {
    std::string nonce = abyss::crypto::random::generate_buffer(36);
    std::string nonce_1 = abyss::crypto::random::generate_buffer(36);
    EXPECT_NE(nonce, nonce_1);
    EXPECT_EQ(nonce.size(), 36);
    EXPECT_EQ(nonce_1.size(), 36);
}

#endif //ABYSS_HELLO_TEST_CPP
