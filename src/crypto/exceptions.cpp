//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/exceptions.h"

namespace abyss::crypto::exception {
    const char *b64_decoding_exception::what() const noexcept {
        return "Unable to decode the provided base64 string.";
    }

    const char *hex_decoding_exception::what() const noexcept {
        return "Unable to decode the provided hex string.";
    }

    const char *initialization_exception::what() const noexcept {
        return "Unable to initialize cryptographic engine.";
    }
} // abyss::crypto