//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/encode.h"

namespace abyss::crypto::encode {
    std::string hex(const std::string &plain) {
        return coder::getInstance()->encodeHex(plain);
    }

    std::string decode(const std::string &encoded, encodings encoding) {
        return coder::getInstance()->decode(encoded, encoding);
    }

    std::string decode(const std::string &encoded, encodings encoding, base64_variants variant) {
        return coder::getInstance()->decode(encoded, encoding, variant);
    }

    std::string base64(const std::string &plain, base64_variants variant) {
        return coder::getInstance()->encodeBase64(plain, variant);
    }

    std::string base64(const std::string &plain) {
        return coder::getInstance()->encodeBase64(plain);
    }

    std::string encode(const std::string &plain, encodings encoding) {
        return coder::getInstance()->encode(plain, encoding);
    }

    std::string encode(std::string plain, encodings encoding, base64_variants variant) {
        return coder::getInstance()->encode(plain, encoding, variant);
    }
}