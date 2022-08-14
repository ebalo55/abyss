//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/crypto.h"
#include "abyss/crypto/coder.h"

namespace abyss::crypto {
	void init() {
		if(sodium_init() == -1) {
			throw exceptions::initialization_exception();
		}
		coder::getInstance();
	}
}