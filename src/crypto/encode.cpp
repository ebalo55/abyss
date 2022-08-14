//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/encode.h"
#include "abyss/crypto/coder.h"

namespace abyss::crypto::encode {
	std::string hex(const std::string &plain) {
		return coder::getInstance()->encodeHex(plain);
	}
	
	std::string bin(const std::string &encoded, encodings encoding) {
		switch (encoding) {
			case ::binary:
				return encoded;
			case ::hex:
				return coder::getInstance()->decodeHex(encoded);
			case ::base64:
				// forward to the specialized function
				return bin(encoded, encoding, base64_variants::classic);
		}
	}
	
	std::string bin(const std::string &encoded, encodings encoding, base64_variants variant) {
		switch (encoding) {
			case ::binary:
				return encoded;
			case ::hex:
				// forward to the proper implementation containing the decoding lambda
				return bin(encoded, encoding);
			case ::base64:
				break;
		}
	}
	
	std::string base64(std::string plain, base64_variants variant) {
		return nullptr;
	}
	
	std::string base64(std::string plain) {
		return nullptr;
	}
	
	std::string encode(std::string plain, encodings encoding) {
		return nullptr;
	}
	
	std::string encode(std::string plain, encodings encoding, base64_variants variant) {
		return nullptr;
	}
}