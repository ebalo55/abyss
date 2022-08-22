//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/encode.h"

namespace abyss::crypto::encode {
    std::string hex(const std::string &plain) {
        std::stringstream ss;

        size_t hex_size = plain.size() * 2 + 1;
        char *hex = new char[hex_size];
        sodium_bin2hex(
                hex,
                hex_size,
                reinterpret_cast<const unsigned char *const>(plain.c_str()),
                plain.size()
        );
        ss << hex;
        delete[] hex;
        return ss.str();
    }

    std::string hex_to_plain(const std::string &hex) {
        std::stringstream ss;

        // computes the plain size of the hexed string which is __hex_char_number__ /2 +1
        size_t plain_size = hex.size() / 2;
        auto *plain = new unsigned char[plain_size];

        // decode the hexed string and check if the decoding was successful, if it is return the decoded string
        // otherwise throws a hex_decoding_exception
        if (sodium_hex2bin(
                plain,
                plain_size,
                hex.c_str(),
                hex.size(),
                nullptr,
                nullptr,
                nullptr
        ) == 0) {
            // avoid writing characters near the buffer as directly pushing in the stream
            ss.write(reinterpret_cast<const char *>(plain), (long) plain_size);
            delete[] plain;
            return ss.str();
        }
        delete[] plain;
        throw exception::hex_decoding_exception();
    }

    std::string decode(const std::string &encoded, encodings encoding) {
        switch (encoding) {
            default:
            case _binary:
                return encoded;
            case _hex:
                return hex_to_plain(encoded);
            case _base64:
                return base64_to_plain(encoded);
        }
    }

    std::string decode(const std::string &encoded, encodings encoding, base64_variants variant) {
        switch (encoding) {
            default:
            case _binary:
                return encoded;
            case _hex:
                return hex_to_plain(encoded);
            case _base64:
                return base64_to_plain(encoded, variant);
        }
    }

    std::string base64(const std::string &plain, base64_variants variant) {
        std::stringstream ss;

        size_t encoded_size = sodium_base64_encoded_len(plain.size(), variant);
        char *b64 = new char[encoded_size];

        sodium_bin2base64(
                b64,
                encoded_size,
                reinterpret_cast<const unsigned char *const>(plain.c_str()),
                plain.size(),
                variant
        );

        ss << b64;
        delete[] b64;
        return ss.str();
    }

    std::string base64(const std::string &plain) {
        return base64(plain, base64_variants::_classic);
    }

    std::string encode(const std::string &plain, encodings encoding) {
        switch (encoding) {
            default:
            case _binary:
                return plain;
            case _hex:
                return hex(plain);
            case _base64:
                return base64(plain);
        }
    }

    std::string encode(const std::string &plain, encodings encoding, base64_variants variant) {
        switch (encoding) {
            default:
            case _binary:
                return plain;
            case _hex:
                return hex(plain);
            case _base64:
                return base64(plain, variant);
        }
    }

    std::string base64_to_plain(const std::string &b64, base64_variants variant) {
        std::stringstream ss;

        auto a = (size_t) std::ceil((double) b64.size() / 4.);
        size_t plain_size = a * 3;
        auto *plain = new unsigned char[plain_size];
        size_t real_size;

        // decode the encoded string and check if the decoding was successful, if it is return the decoded string
        // otherwise throws a b64_decoding_exception
        if (sodium_base642bin(
                plain,
                plain_size,
                b64.c_str(),
                b64.size(),
                nullptr,
                &real_size,
                nullptr,
                variant
        ) == 0) {
            ss.write(reinterpret_cast<const char *>(plain), (long) real_size);
            delete[] plain;
            return ss.str();
        }

        delete[] plain;
        throw exception::b64_decoding_exception();
    }

    std::string base64_to_plain(const std::string &b64) {
        return base64_to_plain(b64, base64_variants::_classic);
    }
}