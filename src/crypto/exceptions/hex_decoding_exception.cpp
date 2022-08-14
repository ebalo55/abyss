//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/exceptions/hex_decoding_exception.h"

namespace abyss::crypto::exceptions {
		const char *hex_decoding_exception::what() const noexcept {
			return "Unable to decode the provided hex string.";
		}
} // abyss::crypto