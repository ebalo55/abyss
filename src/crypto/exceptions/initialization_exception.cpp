//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/exceptions/initialization_exception.h"

namespace abyss::crypto {
		const char *initialization_exception::what() const noexcept {
			return "Unable to initialize cryptographic engine.";
		}
} // abyss::crypto