//
// Created by ebalo on 14/08/2022.
//

#include "abyss/crypto/exceptions.h"
#include <fmt/format.h>
#include <sodium/crypto_pwhash.h>

namespace abyss::crypto::exception {
    const char *b64_decoding_exception::what() const noexcept {
        return "Unable to decode the provided _base64 string.";
    }

    const char *hex_decoding_exception::what() const noexcept {
        return "Unable to decode the provided _hex string.";
    }

    const char *initialization_exception::what() const noexcept {
        return "Unable to initialize cryptographic engine.";
    }

    const char *padding_exception::what() const noexcept {
        return "Unable to pad the string to the given block size.";
    }

    const char *symmetric_message_encryption_exception::what() const noexcept {
        return "Unable to encrypt the message.";
    }

    const char *symmetric_message_decryption_exception::what() const noexcept {
        return "Unable to decrypt the message.";
    }

    const char *symmetric_stream_encryption_exception::what() const noexcept {
        return "Unable to encrypt the stream.";
    }

    const char *symmetric_stream_encryption_closed_exception::what() const noexcept {
        return "Unable to push encrypted data to the stream, the stream is closed.";
    }

    const char *symmetric_stream_decryption_exception::what() const noexcept {
        return "Unable to decrypt the stream.";
    }

    const char *symmetric_stream_decryption_closed_exception::what() const noexcept {
        return "Unable to push decrypted data to the stream, the stream is closed.";
    }

    const char *symmetric_stream_decryption_invalid_header_closed_exception::what() const noexcept {
        return "Unable to decrypt stream, invalid header detected";
    }

    const char *symmetric_mac_exception::what() const noexcept {
        return "Unable to compute the authentication tag.";
    }

    const char *asymmetric_encryption_exception::what() const noexcept {
        return "Unable to encrypt the message.";
    }

    const char *asymmetric_decryption_exception::what() const noexcept {
        return "Unable to decrypt the message.";
    }

    const char *asymmetric_mac_exception::what() const noexcept {
        return "Unable to compute the authentication tag.";
    }

    const char *generic_hash_exception::what() const noexcept {
        return "Unable to compute the generic hash, this is commonly due to an out of memory error.";
    }

    const char *key_derivation_exception::what() const noexcept {
        return "Unable to compute the derived key, this is commonly due to an out of memory error.";
    }

    const char *key_derivation_size_exception::what() const noexcept {
        return "Invalid key size requested for derivation, the value must be between crypto_pwhash_BYTES_MIN and crypto_pwhash_BYTES_MAX.";
    }

    const char *password_hash_exception::what() const noexcept {
        return "Unable to compute the hashed password, this is commonly due to an out of memory error.";
    }

    const char *key_derivation_context_size_exception::what() const noexcept {
        return "Unable to derive a key, context size must be exactly 8 chars.";
    }

    const char *key_derivation_requested_size_exception::what() const noexcept {
        return "Unable to derive a key, requested size must be between crypto_kdf_BYTES_MIN and crypto_kdf_BYTES_MAX.";
    }
} // abyss::crypto