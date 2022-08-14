//
// Created by BLSMNL00E on 14/08/2022.
//

#include "abyss/crypto/crypto.h"

namespace abyss::crypto {
	void init() {
		if(sodium_init() == -1) {
			throw initialization_exception();
		}
	}
}