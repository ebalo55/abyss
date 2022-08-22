//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanGenerateMasterDerivationKey) {
    auto master_key = abyss::crypto::key_derivation::make_master_key();
//    std::cout << abyss::crypto::encode::base64(master_key) << std::endl;
    EXPECT_EQ(master_key.size(), crypto_kdf_KEYBYTES);
}

TEST(CryptoTest, CanDeriveFromKey) {
    auto master_key = abyss::crypto::key_derivation::make_master_key();
    auto derived_1 = abyss::crypto::key_derivation::derive(master_key, 1, 32);
    auto derived_1_copy = abyss::crypto::key_derivation::derive(master_key, 1, 32);
    /*std::cout << abyss::crypto::encode::base64(derived_1) << std::endl
              << abyss::crypto::encode::base64(derived_1_copy) << std::endl;*/
    EXPECT_EQ(derived_1, derived_1_copy);
}

TEST(CryptoTest, CanDeriveFromKeyWithDifferentContext) {
    auto master_key = abyss::crypto::key_derivation::make_master_key();
    auto derived_1 = abyss::crypto::key_derivation::derive(master_key, 1, 32);
    auto derived_1_copy = abyss::crypto::key_derivation::derive(master_key, 1, 32, "test_ctx");
    /*std::cout << abyss::crypto::encode::base64(derived_1) << std::endl
              << abyss::crypto::encode::base64(derived_1_copy) << std::endl;*/
    EXPECT_NE(derived_1, derived_1_copy);
}

#endif //ABYSS_HELLO_TEST_CPP
