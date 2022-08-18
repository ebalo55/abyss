//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/crypto/crypto.h"

using namespace abyss::crypto;

TEST(CryptoTest, CanEncryptAndDecryptStreamUsingSymmetricEncryption) {
    auto encryption_key = abyss::crypto::symmetric_stream::makeEncryptionKey();
    auto encryption_stream = abyss::crypto::symmetric_stream::makeEncryptionStream(encryption_key);
    auto header = encryption_stream->header();

    std::string m1 = "This is one of the chunk ",
            m2 = "that should be encoded...\n",
            m3 = "Hopefully everything goes well, even with some number? ",
            c1, c2, c3, c4;

    c1 = encryption_stream->write(m1);
    c2 = encryption_stream->write(m2, symmetric_stream_tag::rekey);
    c3 = encryption_stream->write(m3);
    c4 = encryption_stream->closeStream();

    std::cout << "key: " << abyss::crypto::encode::base64(encryption_key) << std::endl
              << "header: " << abyss::crypto::encode::base64(header) << std::endl
              << "messages: " << std::endl
              << "\t[0]: " << abyss::crypto::encode::base64(c1) << std::endl
              << "\t[1]: " << abyss::crypto::encode::base64(c2) << std::endl
              << "\t[2]: " << abyss::crypto::encode::base64(c3) << std::endl
              << "\t[3]: " << abyss::crypto::encode::base64(c4) << std::endl;

    auto decryption_stream = abyss::crypto::symmetric_stream::makeDecryptionStream(header, encryption_key);

    std::string p1 = decryption_stream->write(c1);
    EXPECT_EQ(decryption_stream->lastTag(), symmetric_stream_tag::message);
    EXPECT_TRUE(decryption_stream->isStreamOpen());

    std::string p2 = decryption_stream->write(c2);
    EXPECT_EQ(decryption_stream->lastTag(), symmetric_stream_tag::rekey);
    EXPECT_TRUE(decryption_stream->isStreamOpen());

    std::string p3 = decryption_stream->write(c3);
    EXPECT_EQ(decryption_stream->lastTag(), symmetric_stream_tag::message);
    EXPECT_TRUE(decryption_stream->isStreamOpen());

    std::string p4 = decryption_stream->write(c4);
    EXPECT_EQ(decryption_stream->lastTag(), symmetric_stream_tag::stream_end);
    EXPECT_FALSE(decryption_stream->isStreamOpen());

    EXPECT_EQ(p1, m1);
    EXPECT_EQ(p2, m2);
    EXPECT_EQ(p3, m3);
    EXPECT_EQ(p4, "");
}


#endif //ABYSS_HELLO_TEST_CPP
