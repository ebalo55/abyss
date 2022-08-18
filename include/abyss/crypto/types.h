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
}

#endif //ABYSS_TYPES_H
