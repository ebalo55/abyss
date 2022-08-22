//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/pad.h"

namespace abyss::crypto::pad {
    std::string pad(const std::string &plain, size_t block_size) {
        std::stringstream ss;

        // add the block size to the size of the string in order to always allow for the padding of the string
        size_t plain_size = plain.size() + block_size;

        // create and fill the buffer
        auto buf = new unsigned char[plain_size];
        plain.copy(reinterpret_cast<char *>(buf), plain.size());

        size_t real_length;

        if (sodium_pad(
                &real_length,
                buf,
                plain.size(),
                block_size,
                plain_size
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(buf), (long) real_length);
            delete[] buf;
            return ss.str();
        }
        delete[] buf;
        throw exception::padding_exception();
    }

    std::string unpad(const std::string &padded, size_t block_size) {
        std::stringstream ss;
        size_t real_length;

        if (sodium_unpad(
                &real_length,
                reinterpret_cast<const unsigned char *>(padded.c_str()),
                padded.size(),
                block_size
        ) == 0) {
            ss.write(padded.c_str(), (long) real_length);
            return ss.str();
        }
        throw exception::padding_exception();
    }

    std::string pad_4(const std::string &plain) {
        return pad(plain, 4);
    }

    std::string unpad_4(const std::string &padded) {
        return unpad(padded, 4);
    }

    std::string pad_8(const std::string &plain) {
        return pad(plain, 8);
    }

    std::string unpad_8(const std::string &padded) {
        return unpad(padded, 8);
    }

    std::string pad_16(const std::string &plain) {
        return pad(plain, 16);
    }

    std::string unpad_16(const std::string &padded) {
        return unpad(padded, 16);
    }

    std::string pad_32(const std::string &plain) {
        return pad(plain, 32);
    }

    std::string unpad_32(const std::string &padded) {
        return unpad(padded, 32);
    }

    std::string pad_64(const std::string &plain) {
        return pad(plain, 64);
    }

    std::string unpad_64(const std::string &padded) {
        return unpad(padded, 64);
    }


}