//
// Created by ebalo on 18/08/22.
//

#ifndef ABYSS_TYPES_H
#define ABYSS_TYPES_H

namespace abyss::crypto::symmetric {
    struct encryption_data {
        std::string message;
        std::string key;
        std::string nonce;
    };
    typedef struct encryption_data encryption_data_t;
    typedef struct encryption_data encrypted_data_t;
    typedef struct encryption_data decryption_data_t;

    struct encryption_data_detached {
        std::string authentication_tag;
        std::string message;
        std::string key;
        std::string nonce;
    };
    typedef struct encryption_data_detached encrypted_data_detached_t;
    typedef struct encryption_data_detached decryption_data_detached_t;

    enum symmetric_stream_tag {
        _message = crypto_secretstream_xchacha20poly1305_TAG_MESSAGE,
        _stream_end = crypto_secretstream_xchacha20poly1305_TAG_FINAL,
        _message_end = crypto_secretstream_xchacha20poly1305_TAG_PUSH,
        _rekey = crypto_secretstream_xchacha20poly1305_TAG_REKEY
    };
}

namespace abyss::crypto::asymmetric {
    struct keypair {
        std::string public_key;
        std::string secret_key;
    };
    typedef struct keypair keypair_t;
    typedef struct keypair transitional_keypair_t;

    struct encryption_data {
        std::string message;
        std::string nonce;
        keypair_t keypair;
    };
    typedef struct encryption_data encrypted_data_t;
    typedef struct encryption_data decryption_data_t;

    struct encryption_data_detached {
        std::string authentication_tag;
        std::string message;
        std::string nonce;
        keypair_t keypair;
    };
    typedef struct encryption_data_detached encrypted_data_detached_t;
    typedef struct encryption_data_detached decryption_data_detached_t;

    struct signature_data {
        bool verified;
        std::string message;
    };
    typedef struct signature_data signature_data_t;
}

namespace abyss::crypto::hash {
    enum security_level {
        minimum,
        average,
        maximum,
    };
}

namespace abyss::crypto::hash::password {
    enum operation_limit {
        /**
         * Recommended for online operations.
         * Requires 64 MiB of dedicated RAM.
         */
        _ops_interactive = crypto_pwhash_OPSLIMIT_INTERACTIVE,
        _ops_max = crypto_pwhash_OPSLIMIT_MAX,
        _ops_min = crypto_pwhash_OPSLIMIT_MIN,
        /**
         * Requires 256 MiB of dedicated RAM.
         * Takes about 0.7 seconds on a 2.8 GHz Core i7 CPU
         */
        _ops_moderate = crypto_pwhash_OPSLIMIT_MODERATE,
        /**
         * Recommended for highly sensitive data and non-interactive operations.
         * Requires 1024 MiB of dedicated RAM.
         * Takes about 3.5 seconds on a 2.8 GHz Core i7 CPU
         */
        _ops_sensitive = crypto_pwhash_OPSLIMIT_SENSITIVE,
    };

    enum memory_limit {
        /**
         * Recommended for online operations.
         * Requires 64 MiB of dedicated RAM.
         */
        _memory_interactive = crypto_pwhash_MEMLIMIT_INTERACTIVE,
        _memory_max = crypto_pwhash_MEMLIMIT_MAX,
        _memory_min = crypto_pwhash_MEMLIMIT_MIN,
        /**
         * Requires 256 MiB of dedicated RAM.
         * Takes about 0.7 seconds on a 2.8 GHz Core i7 CPU
         */
        _memory_moderate = crypto_pwhash_MEMLIMIT_MODERATE,
        /**
         * Recommended for highly sensitive data and non-interactive operations.
         * Requires 1024 MiB of dedicated RAM.
         * Takes about 3.5 seconds on a 2.8 GHz Core i7 CPU
         */
        _memory_sensitive = crypto_pwhash_MEMLIMIT_SENSITIVE,
    };
}

#endif //ABYSS_TYPES_H
