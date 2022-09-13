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

TEST(CryptoTest, CanGenerateRandomDouble) {
    double test = 0.;
//    std::cout << "test value is: " << test << std::endl
//    << "test memory size is: " << sizeof(test) << std::endl;
    abyss::crypto::random::generate(&test, sizeof(test));
    EXPECT_NE(test, 0.);
//    std::cout << "test value is: " << test << std::endl
//              << "test memory size is: " << sizeof(test) << std::endl;
}

TEST(CryptoTest, CanGenerateRandomLongLong) {
    long long test = 0;
//    std::cout << "test value is: " << test << std::endl
//    << "test memory size is: " << sizeof(test) << std::endl;
    abyss::crypto::random::generate(&test, sizeof(test));
    EXPECT_NE(test, 0);
//    std::cout << "test value is: " << test << std::endl
//              << "test memory size is: " << sizeof(test) << std::endl;
}

TEST(CryptoTest, CanGenerateRandomInt) {
    int test = 0;
//    std::cout << "test value is: " << test << std::endl
//    << "test memory size is: " << sizeof(test) << std::endl;
    abyss::crypto::random::generate(&test, sizeof(test));
    EXPECT_NE(test, 0);
//    std::cout << "test value is: " << test << std::endl
//              << "test memory size is: " << sizeof(test) << std::endl;
}

TEST(CryptoTest, CanGenerateRandomInt8) {
    int test = 0;
//    std::cout << "test value is: " << (int) test << std::endl
//    << "test memory size is: " << sizeof(test) << std::endl;
    abyss::crypto::random::generate(&test, sizeof(test));
    EXPECT_NE(test, 0);
//    std::cout << "test value is: " << (int) test << std::endl
//              << "test memory size is: " << sizeof(test) << std::endl;
}

TEST(CryptoTest, CanGenerateRandomIntMax) {
    intmax_t test = 0;
//    std::cout << "test value is: " << test << std::endl
//              << "test memory size is: " << sizeof(test) << std::endl;
    abyss::crypto::random::generate(&test, sizeof(test));
    EXPECT_NE(test, 0);
//    std::cout << "test value is: " << test << std::endl
//              << "test memory size is: " << sizeof(test) << std::endl;
}

TEST(CryptoTest, CanGenerateRandomIntArray) {
    int test[] = {0, 0, 0, 0};
//    std::cout << "test value is: "
//            << test[0]
//            << ", "
//            << test[1]
//            << ", "
//            << test[2]
//            << ", "
//            << test[3]
//            << ", "
//            << std::endl
//            << "test memory size is: "
//            << sizeof(test)
//            << std::endl;
    abyss::crypto::random::generate(&test, sizeof(test));
    EXPECT_NE(test[0], 0);
    EXPECT_NE(test[1], 0);
    EXPECT_NE(test[2], 0);
    EXPECT_NE(test[3], 0);
//    std::cout << "test value is: "
//              << test[0]
//              << ", "
//              << test[1]
//              << ", "
//              << test[2]
//              << ", "
//              << test[3]
//              << ", "
//              << std::endl
//              << "test memory size is: "
//              << sizeof(test)
//              << std::endl;
}

#endif //ABYSS_HELLO_TEST_CPP
