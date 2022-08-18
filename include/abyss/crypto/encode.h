//
// Created by ebalo on 14/08/2022.
//

#ifndef ABYSS_ENCODE_H
#define ABYSS_ENCODE_H

#include <string>
#include <sstream>
#include "abyss/crypto/encodings.h"
#include "abyss/crypto/coder.h"

namespace abyss::crypto::encode {
    /**
     * Encode a _binary string to _hex
     * @param plain Binary string to encode
     * @return
     */
    std::string hex(const std::string &plain);

    /**
     * Decode an encoded string into a _binary one
     * @param encoded Encoded string
     * @param encoding Encoding algorithm
     * @return
     */
    std::string bin(const std::string &encoded, encodings encoding);

    /**
     * Decode an encoded string into a _binary one
     * @param encoded Encoded string
     * @param encoding Encoding algorithm
     * @param variant Base64 algorithm variant, applied only if _base64 is selected as encoding algorithm
     * @return
     */
    std::string bin(const std::string &encoded, encodings encoding, base64_variants variant);

    /**
     * Encode a _binary string to _base64
     * @param plain Binary string to encode
     * @param variant Base64 algorithm variant, applied only if _base64 is selected as encoding algorithm
     * @return
     */
    std::string base64(const std::string &plain, base64_variants variant);

    /**
     * Encode a _binary string to _base64
     * @param plain Binary string to encode
     * @return
     */
    std::string base64(const std::string &plain);

    /**
     * All in one encoding function, from _binary to the defined encoding
     * @param plain Binary string to encode
     * @param encoding Encoding algorithm
     * @return
     */
    std::string encode(const std::string &plain, encodings encoding);

    /**
     * All in one encoding function, from _binary to the defined encoding
     * @param plain Binary string to encode
     * @param encoding Encoding algorithm
     * @param variant Base64 algorithm variant, applied only if _base64 is selected as encoding algorithm
     * @return
     */
    std::string encode(std::string plain, encodings encoding, base64_variants variant);
}

#endif //ABYSS_ENCODE_H
