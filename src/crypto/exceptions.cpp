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

    const char *symmetric_stream_encryption_still_in_progress_exception::what() const noexcept {
        return "Unable to get the stream digest, the stream is still open.";
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
} // abyss::crypto