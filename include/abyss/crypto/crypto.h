//
// Created by ebalo on 14/08/2022.
//

#ifndef ABYSS_CRYPTO_H
#define ABYSS_CRYPTO_H

#include <sodium.h>
#include <exception>
#include "abyss/crypto/exceptions.h"
#include "abyss/crypto/version.h"
#include "abyss/crypto/encodings.h"
#include "abyss/crypto/encode.h"
#include "abyss/crypto/pad.h"
#include "abyss/crypto/random.h"
#include "abyss/crypto/encryption.h"

namespace abyss::crypto {
	/**
	 * Initialize instances of abyss::crypto and all required values/engines
	 */
	void init();
}

#endif //ABYSS_CRYPTO_H
