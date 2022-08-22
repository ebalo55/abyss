//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanGenerateDefaultSizeSalt) {
    auto salt = abyss::crypto::hash::make_salt();
//    std::cout << abyss::crypto::encode::base64(salt) << std::endl;
    EXPECT_EQ(salt.size(), crypto_generichash_KEYBYTES);
}

TEST(CryptoTest, CanGenerateLowSecuritySalt) {
    auto salt = abyss::crypto::hash::make_salt(abyss::crypto::hash::minimum);
//    std::cout << abyss::crypto::encode::base64(salt) << std::endl;
    EXPECT_EQ(salt.size(), crypto_generichash_KEYBYTES_MIN);
}

TEST(CryptoTest, CanGenerateHighSecuritySalt) {
    auto salt = abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum);
//    std::cout << abyss::crypto::encode::base64(salt) << std::endl;
    EXPECT_EQ(salt.size(), crypto_generichash_KEYBYTES_MAX);
}

TEST(CryptoTest, CanHashWithDefaultValues) {
    auto h1 = abyss::crypto::hash::generic_hash("test");
//    std::cout << abyss::crypto::encode::base64(h1) << std::endl;
    EXPECT_EQ(h1.size(), crypto_generichash_BYTES);

    auto h2 = abyss::crypto::hash::generic_hash("test");
    EXPECT_EQ(h2, h1);
}

TEST(CryptoTest, CanHashWithManuallyDefinedKey) {
    auto h1 = abyss::crypto::hash::generic_hash("test", "this is a key");
//    std::cout << abyss::crypto::encode::base64(h1) << std::endl;
    EXPECT_EQ(h1.size(), crypto_generichash_BYTES);

    auto h2 = abyss::crypto::hash::generic_hash("test", "this is a key");
    EXPECT_EQ(h2, h1);
}

TEST(CryptoTest, CanHashWithRandomKey) {
    auto h1 = abyss::crypto::hash::generic_hash("test", abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum));
//    std::cout << abyss::crypto::encode::base64(h1) << std::endl;
    EXPECT_EQ(h1.size(), crypto_generichash_BYTES);

    auto h2 = abyss::crypto::hash::generic_hash("test", abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum));
    EXPECT_NE(h2, h1);

    auto h3 = abyss::crypto::hash::generic_hash("test", abyss::crypto::random::generate_buffer(128));
    EXPECT_NE(h3, h1);
}

TEST(CryptoTest, CanHashWithLowSecurityLevel) {
    auto h1 = abyss::crypto::hash::generic_hash(
            "test",
            abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum),
            abyss::crypto::hash::minimum
    );
//    std::cout << abyss::crypto::encode::base64(h1) << std::endl;
    EXPECT_EQ(h1.size(), crypto_generichash_BYTES_MIN);

    auto h2 = abyss::crypto::hash::generic_hash(
            "test",
            abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum),
            abyss::crypto::hash::minimum
    );
    EXPECT_NE(h2, h1);
    EXPECT_EQ(h2.size(), crypto_generichash_BYTES_MIN);
}

TEST(CryptoTest, CanHashWithHighSecurityLevel) {
    auto h1 = abyss::crypto::hash::generic_hash(
            "test",
            abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum),
            abyss::crypto::hash::maximum
    );
//    std::cout << abyss::crypto::encode::base64(h1) << std::endl;
    EXPECT_EQ(h1.size(), crypto_generichash_BYTES_MAX);

    auto h2 = abyss::crypto::hash::generic_hash(
            "test",
            abyss::crypto::hash::make_salt(abyss::crypto::hash::maximum),
            abyss::crypto::hash::maximum
    );
    EXPECT_NE(h2, h1);
    EXPECT_EQ(h2.size(), crypto_generichash_BYTES_MAX);
}

TEST(CryptoTest, CanHashStream) {
    abyss::crypto::hash::hash_stream h_stream(abyss::crypto::hash::make_salt());
    h_stream.write("this is a ");
    h_stream.write("test stream ");
    h_stream.write("that will be hashed in steps");
    auto stepped_hash = h_stream.closeStream();

    auto h1 = abyss::crypto::hash::generic_hash("this is a test stream that will be hashed in steps");
    /*std::cout << abyss::crypto::encode::base64(stepped_hash) << std::endl;
    std::cout << abyss::crypto::encode::base64(h1) << std::endl;*/
    EXPECT_EQ(h1.size(), crypto_generichash_BYTES);
    EXPECT_EQ(stepped_hash.size(), crypto_generichash_BYTES);
    EXPECT_NE(stepped_hash, h1);
}

#endif //ABYSS_HELLO_TEST_CPP
