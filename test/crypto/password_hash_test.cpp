//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"
#include <chrono>

auto salt = abyss::crypto::hash::password::make_salt();

TEST(CryptoTest, CanDeriveAnArbitraryLengthKeyUsingPasswordFunctionAndDefaultSettings) {
    auto derived_key = abyss::crypto::hash::password::derive_key(
            "test",
            salt,
            128
    );
//    std::cout << "derived key: " << abyss::crypto::encode::base64(derived_key) << std::endl;
    EXPECT_EQ(derived_key.size(), 128);
}

TEST(CryptoTest, CanDeriveAnArbitraryLengthKeyUsingPasswordFunctionAndFastestSettings) {
    auto derived_key = abyss::crypto::hash::password::derive_key(
            "test",
            salt,
            128,
            abyss::crypto::hash::password::_ops_min,
            abyss::crypto::hash::password::_memory_min
    );
//    std::cout << "derived key: " << abyss::crypto::encode::base64(derived_key) << std::endl;
    EXPECT_EQ(derived_key.size(), 128);
}

TEST(CryptoTest, CanHashPasswordWithDefaultSettings) {
    auto hash = abyss::crypto::hash::password::hash(
            "test"
    );
//    std::cout << "hash: " << hash << std::endl;
    EXPECT_TRUE(abyss::crypto::hash::password::verify(hash, "test"));
}

TEST(CryptoTest, CanHashPasswordWithDefaultFastestSettings) {
    auto start = std::chrono::high_resolution_clock::now();
    auto hash = abyss::crypto::hash::password::hash(
            "test",
            abyss::crypto::hash::password::_ops_min,
            abyss::crypto::hash::password::_memory_min
    );
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    /*std::cout << "hash: " << hash << std::endl
              << "hash duration: " << duration.count() << "ms" << std::endl;*/
    EXPECT_TRUE(abyss::crypto::hash::password::verify(hash, "test"));
}

#endif //ABYSS_HELLO_TEST_CPP
