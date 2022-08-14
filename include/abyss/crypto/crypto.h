//
// Created by BLSMNL00E on 14/08/2022.
//

#ifndef ABYSS_CRYPTO_H
#define ABYSS_CRYPTO_H

#include <sodium.h>
#include <exception>
#include "abyss/crypto/exceptions/initialization_exception.h"
#include "abyss/crypto/version.h"
#include "abyss/crypto/encodings.h"
#include "abyss/crypto/encode.h"

namespace abyss::crypto {
	/**
	 * Initialize instances of abyss::crypto and all required values/engines
	 */
	void init();
}

#endif //ABYSS_CRYPTO_H
