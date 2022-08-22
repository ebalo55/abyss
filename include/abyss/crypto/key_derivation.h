//
// Created by ebalo on 22/08/22.
//

#ifndef ABYSS_KEY_DERIVATION_H
#define ABYSS_KEY_DERIVATION_H

#include <sstream>
#include <string>
#include <sodium.h>

#include "abyss/crypto/types.h"
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto::key_derivation {
    /**
     * Generates a random secure master key that can be used in key derivation
     * @return
     */
    std::string make_master_key();

    /**
     * Derive the given subkey from the master_key
     * @param master_key Master key, starting point for subkey derivation
     * @param subkey Subkey index to derive
     * @param subkey_length Subkey length in chars, between 16 and 64 included
     * @param context 8 char string used to isolate application contexts
     * @return
     */
    std::string derive(const std::string& master_key, size_t subkey, short subkey_length, const std::string& context);

    /**
     * Derive the given subkey from the master_key
     * @param master_key Master key, starting point for subkey derivation
     * @param subkey Subkey index to derive
     * @param subkey_length Subkey length in chars, between 16 and 64 included
     * @return
     */
    std::string derive(const std::string& master_key, size_t subkey, short subkey_length);
}

#endif //ABYSS_KEY_DERIVATION_H
