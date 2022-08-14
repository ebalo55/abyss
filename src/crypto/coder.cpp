//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/coder.h"

namespace abyss::crypto {
	std::shared_ptr<coder> coder::instance_ = nullptr;
	
	std::shared_ptr<coder> coder::getInstance() {
		if (instance_ == nullptr) {
			instance_ = std::shared_ptr<coder>(new coder());
		}
		return instance_;
	}
	
	std::string coder::encodeHex(const std::string &plain) {
		cleanStream();
		
		size_t hex_size = plain.size() * 2 + 1;
		char *hex = new char[hex_size];
		sodium_bin2hex(
				hex,
				hex_size,
				reinterpret_cast<const unsigned char *const>(plain.c_str()),
				plain.size()
		);
		ss_ << hex;
		return ss_.str();
	}
	
	std::string coder::decodeHex(const std::string &hex) {
		cleanStream();
		
		// computes the plain size of the hexed string which is __hex_char_number__ /2 +1
		size_t plain_size = hex.size() / 2 + 1;
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
			ss_ << plain;
			return ss_.str();
		}
		throw exceptions::hex_decoding_exception();
	}
	
	std::string coder::decode(const std::string &encoded, encodings encoding) {
		cleanStream();
		
		return std::string();
	}
	
	std::string coder::decode(const std::string &encoded, encodings encoding, base64_variants variant) {
		cleanStream();
		
		return std::string();
	}
	
	std::string coder::encodeBase64(const std::string &plain, base64_variants variant) {
		cleanStream();
		
		size_t encoded_size = sodium_base64_encoded_len(plain.size(), variant);
		char *b64 = new char[encoded_size];
		
		sodium_bin2base64(
				b64,
				encoded_size,
				reinterpret_cast<const unsigned char *const>(plain.c_str()),
				plain.size(),
				variant
		);
		
		ss_ << b64;
		return ss_.str();
	}
	
	std::string coder::encodeBase64(const std::string &plain) {
		cleanStream();
		return encodeBase64(plain, base64_variants::classic);
	}
	
	std::string coder::encode(const std::string &plain, encodings encoding) {
		cleanStream();
		
		return std::string();
	}
	
	std::string coder::encode(const std::string &plain, encodings encoding, base64_variants variant) {
		cleanStream();
		
		return std::string();
	}
	
	void coder::cleanStream() {
		ss_.clear();
	}
	
	std::string coder::decodeBase64(const std::string &b64, base64_variants variant) {
		cleanStream();
		
		size_t plain_size = b64.size() / 4 * 3;
		auto *plain = new unsigned char[plain_size];
		
		// decode the encoded string and check if the decoding was successful, if it is return the decoded string
		// otherwise throws a b64_decoding_exception
		if(sodium_base642bin(
				plain,
				plain_size,
				b64.c_str(),
				b64.size(),
				nullptr,
				nullptr,
				nullptr,
				variant
				) == 0) {
			ss_ << plain;
			return ss_.str();
		}
		
		throw exceptions::b64_decoding_exception();
	}
	
	std::string coder::decodeBase64(const std::string &b64) {
		cleanStream();
		return decodeBase64(b64, base64_variants::classic);
	}
}