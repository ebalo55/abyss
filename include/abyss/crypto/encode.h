//
// Created by BLSMNL00E on 14/08/2022.
//

#ifndef ABYSS_ENCODE_H
#define ABYSS_ENCODE_H

#include <string>
#include "abyss/crypto/encodings.h"

namespace abyss::crypto::encode {
	/**
	 * Encode a binary string to hex
	 * @param plain Binary string to encode
	 * @return
	 */
	std::string hex(const std::string& plain);
	
	/**
	 * Decode an encoded string into a binary one
	 * @param encoded Encoded string
	 * @param encoding Encoding algorithm
	 * @return
	 */
	std::string bin(std::string encoded, encodings encoding);
	
	/**
	 * Decode an encoded string into a binary one
	 * @param encoded Encoded string
	 * @param encoding Encoding algorithm
	 * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
	 * @return
	 */
	std::string bin(std::string encoded, encodings encoding, base64_variants variant);
	
	/**
	 * Encode a binary string to base64
	 * @param plain Binary string to encode
	 * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
	 * @return
	 */
	std::string base64(std::string plain, base64_variants variant);
	
	/**
	 * Encode a binary string to base64
	 * @param plain Binary string to encode
	 * @return
	 */
	std::string base64(std::string plain);
	
	/**
	 * All in one encoding function, from binary to the defined encoding
	 * @param plain Binary string to encode
	 * @param encoding Encoding algorithm
	 * @return
	 */
	std::string encode(std::string plain, encodings encoding);
	
	/**
	 * All in one encoding function, from binary to the defined encoding
	 * @param plain Binary string to encode
	 * @param encoding Encoding algorithm
	 * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
	 * @return
	 */
	std::string encode(std::string plain, encodings encoding, base64_variants variant);
}

#endif //ABYSS_ENCODE_H
