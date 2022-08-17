//
// Created by ebalo on 14/08/2022.
//

#ifndef ABYSS_CODER_H
#define ABYSS_CODER_H

#include <memory>
#include <string>
#include <sstream>
#include <cmath>
#include "abyss/crypto/encodings.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto {
	class coder {
	private:
		static std::shared_ptr<coder> instance_;
		std::stringstream ss_;
		
		coder() = default;
		
		void cleanStream();
	
	public:
		static std::shared_ptr<coder> getInstance();
		
		/**
		 * Encode a binary string to hex
		 * @param plain Binary string to encode
		 * @return
		 */
		std::string encodeHex(const std::string &plain);
		
		/**
		 * Decode an hex string to binary
		 * @param plain Hexed string to decode
		 * @return
		 */
		std::string decodeHex(const std::string &hex);
		
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
		std::string encodeBase64(const std::string& plain, base64_variants variant);
		
		/**
		 * Encode a binary string to base64
		 * @param plain Binary string to encode
		 * @return
		 */
		std::string encodeBase64(const std::string& plain);
		
		/**
		 * Encode a binary string to base64
		 * @param plain Binary string to encode
		 * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
		 * @return
		 */
		std::string decodeBase64(const std::string& b64, base64_variants variant);
		
		/**
		 * Encode a binary string to base64
		 * @param plain Binary string to encode
		 * @return
		 */
		std::string decodeBase64(const std::string& b64);
		
		/**
		 * All in one encoding function, from binary to the defined encoding
		 * @param plain Binary string to encode
		 * @param encoding Encoding algorithm
		 * @return
		 */
		std::string encode(const std::string& plain, encodings encoding);
		
		/**
		 * All in one encoding function, from binary to the defined encoding
		 * @param plain Binary string to encode
		 * @param encoding Encoding algorithm
		 * @param variant Base64 algorithm variant, applied only if base64 is selected as encoding algorithm
		 * @return
		 */
		std::string encode(const std::string& plain, encodings encoding, base64_variants variant);
	};
}

#endif //ABYSS_CODER_H
