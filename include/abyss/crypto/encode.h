//
// Created by ebalo on 14/08/2022.
//

#ifndef ABYSS_ENCODE_H
#define ABYSS_ENCODE_H

#include <string>
#include <sstream>
#include "abyss/crypto/encodings.h"
#include <memory>
#include <string>
#include <sstream>
#include <cmath>
#include "abyss/crypto/encodings.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto::encode {
    /**
     * Encode a binary string to hex
     * @param plain Binary string to encode
     * @return
     */
    std::string hex(const std::string &plain);

    /**
     * Decode a binary string to hex
     * @param plain Hex string to decode
     * @return
     */
    std::string hex_to_plain(const std::string &hex);

    /**
     * Decode an encoded string into a binary one
     * @param encoded Encoded string
     * @param encoding Encoding algorithm
     * @return
     */
    std::string decode(const std::string &encoded, encodings encoding);

    /**
     * Decode an encoded string into a binary one
     * @param encoded Encoded string
     * @param encoding Encoding algorithm
     * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
     * @return
     */
    std::string decode(const std::string &encoded, encodings encoding, base64_variants variant);

    /**
     * Encode a binary string to base64
     * @param plain Binary string to encode
     * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
     * @return
     */
    std::string base64(const std::string &plain, base64_variants variant);

    /**
     * Encode a binary string to base64
     * @param plain Binary string to encode
     * @return
     */
    std::string base64(const std::string &plain);

    /**
     * Decode a base64 string to binary
     * @param b64 Base64 string to decode
     * @return
     */
    std::string base64_to_plain(const std::string &b64);

    /**
     * Decode a base64 string to binary
     * @param b64 Base64 string to decode
     * @param variant Base64 algorithm variant
     * @return
     */
    std::string base64_to_plain(const std::string &b64, base64_variants variant);

    /**
     * All in one encoding function, from binary to the defined encoding
     * @param plain Binary string to encode
     * @param encoding Encoding algorithm
     * @return
     */
    std::string encode(const std::string &plain, encodings encoding);

    /**
     * All in one encoding function, from binary to the defined encoding
     * @param plain Binary string to encode
     * @param encoding Encoding algorithm
     * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
     * @return
     */
    std::string encode(const std::string &plain, encodings encoding, base64_variants variant);
}

#endif //ABYSS_ENCODE_H
