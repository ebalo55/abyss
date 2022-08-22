//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/crypto.h"

namespace abyss::crypto {
    void init() {
        if (sodium_init() == -1) {
            throw exception::initialization_exception();
        }
    }
}