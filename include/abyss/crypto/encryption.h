//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_ENCRYPTION_H
#define ABYSS_ENCRYPTION_H

#include "abyss/crypto/symmetric_encryption.h"
#include "abyss/crypto/symmetric_stream.h"

namespace abyss::crypto {
    namespace symmetric {
        namespace message {
            /**
             * Generates a random valid encryption key
             * @return Encryption key
             */
            std::string make_encryption_key();

            /**
             * Generates a random valid nonce
             * @return Nonce
             */
            std::string make_nonce();

            /**
             * Encrypts a message with a random key and a random nonce.
             * @param message Binary message to encrypt
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const std::string &message);

            /**
             * Encrypts a message with the provided key and a random nonce.
             * @param message Binary message to encrypt
             * @param key Key used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const std::string &message, const std::string &key);

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const std::string &message, const std::string &key, const std::string &nonce);

            /**
             * Encrypts a message with the provided key and nonce.
             * @param data Encryption struct with all required data fields
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const encryption_data_t &data);

            /**
             * Encrypts a message with a random key and a random nonce.
             * Stores the authentication tag separately from the message
             * @param message Binary message to encrypt
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(const std::string &message);

            /**
             * Encrypts a message with the provided key and a random nonce.
             * Stores the authentication tag separately from the message
             * @param message Binary message to encrypt
             * @param key Key used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(const std::string &message, const std::string &key);

            /**
             * Encrypts a message with the provided key and nonce.
             * Stores the authentication tag separately from the message
             * @param message Binary message to encrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_detached_t
            encrypt_detached(const std::string &message, const std::string &key, const std::string &nonce);

            /**
             * Encrypts a message with the provided key and nonce.
             * Stores the authentication tag separately from the message
             * @param data Encryption struct with all required data fields
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(const encryption_data_t &data);

            /**
             * Decrypts a message given nonce and key.
             * @param message Decryption struct with all required data fields
             * @return Decoded string
             */
            std::string decrypt(const decryption_data_t &data);

            /**
             * Decrypts a message given nonce and key.
             * @param message Binary message to decrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Decoded string
             */
            std::string decrypt(const std::string &message, const std::string &key, const std::string &nonce);

            /**
             * Decrypts a message given nonce and key.
             * Stores the authentication tag separately from the message
             * @param message Decryption struct with all required data fields
             * @return Decoded string
             */
            std::string decrypt_detached(const decryption_data_detached_t &data);

            /**
             * Decrypts a message given nonce and key.
             * Stores the authentication tag separately from the message
             * @param authentication_tag Authentication tag used to avoid tampering
             * @param message Binary message to decrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Decoded string
             */
            std::string decrypt_detached(
                    const std::string &authentication_tag,
                    const std::string &message,
                    const std::string &key,
                    const std::string &nonce
            );
        }
        namespace stream {
            /**
             * Generates a random valid encryption key
             * @return Encryption key
             */
            std::string make_encryption_key();

            /**
             * Create an instance of the encryption stream loading the given key
             * @param key Key used in encryption
             * @return Symmetric stream working in encryption mode
             */
            static std::shared_ptr<symmetric_stream> make_encryption_stream(const std::string &key);

            /**
             * Create an instance of the decryption stream loading the given key
             * @param header Header returned by the encryption process
             * @param key Key used in encryption
             * @return Symmetric stream working in decryption mode
             */
            static std::shared_ptr<symmetric_stream>
            make_decryption_stream(const std::string &header, const std::string &key);
        }
    }

    namespace asymmetric {
        // TODO: fill with asymmetric functions
    }
}

#endif //ABYSS_ENCRYPTION_H
