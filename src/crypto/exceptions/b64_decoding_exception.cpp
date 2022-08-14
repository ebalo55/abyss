//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/exceptions/b64_decoding_exception.h"

namespace abyss::crypto::exceptions {
		const char *b64_decoding_exception::what() const noexcept {
			return "Unable to decode the provided base64 string.";
		}
} // abyss::crypto