//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/encode.h"

namespace abyss::crypto::encode {
	std::string hex(const std::string& plain) {
		size_t hex_size = plain.size() *2 +1;
		char hex[hex_size];
		sodium_bin2hex(
				hex,
				hex_size,
				reinterpret_cast<const unsigned char *const>(plain.c_str()),
				plain.size()
				);
		return std::string{hex};
	}
	
	std::string bin(std::string encoded, encodings encoding) {
		return nullptr;
	}
	
	std::string bin(std::string encoded, encodings encoding, base64_variants variant) {
		return nullptr;
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