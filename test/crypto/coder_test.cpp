//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

TEST(CryptoTest, CanEncodeAndDecodeHex) {
    std::string encoded = abyss::crypto::encode::hex("test");
    EXPECT_EQ(encoded, "74657374");
    std::string decoded = abyss::crypto::encode::hex_to_plain(encoded);
    EXPECT_EQ(decoded, "test");
}

TEST(CryptoTest, CanEncodeAndDecodeClassicBase64) {
    std::string encoded = abyss::crypto::encode::base64("test");
    EXPECT_EQ(encoded, "dGVzdA==");
    std::string decoded = abyss::crypto::encode::base64_to_plain(encoded);
    EXPECT_EQ(decoded, "test");
}

TEST(CryptoTest, CanEncodeAndDecodeNoPaddingBase64) {
    std::string encoded = abyss::crypto::encode::base64("test", base64_variants::_no_padding);
    EXPECT_EQ(encoded, "dGVzdA");
    std::string decoded = abyss::crypto::encode::base64_to_plain(encoded, base64_variants::_no_padding);
    EXPECT_EQ(decoded, "test");
}

TEST(CryptoTest, CanEncodeAndDecodeUrlSafeBase64) {
    std::string encoded = abyss::crypto::encode::base64("test", base64_variants::_url_safe);
    EXPECT_EQ(encoded, "dGVzdA==");
    std::string decoded = abyss::crypto::encode::base64_to_plain(encoded, base64_variants::_url_safe);
    EXPECT_EQ(decoded, "test");
}

TEST(CryptoTest, CanEncodeAndDecodeUrlSafeNoPaddingBase64) {
    std::string encoded = abyss::crypto::encode::base64(
            "test",
            base64_variants::_url_safe_no_padding
    );
    EXPECT_EQ(encoded, "dGVzdA");
    std::string decoded = abyss::crypto::encode::base64_to_plain(
            encoded,
            base64_variants::_url_safe_no_padding
    );
    EXPECT_EQ(decoded, "test");
}

#endif //ABYSS_HELLO_TEST_CPP
