//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/pad.h"

namespace abyss::crypto::pad {
	std::string pad(const std::string &plain, size_t block_size) {
		return padder::getInstance()->pad(plain, block_size);
	}
	
	std::string unpad(const std::string &padded, size_t block_size) {
		return padder::getInstance()->unpad(padded, block_size);
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