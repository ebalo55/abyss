//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_ENCRYPTION_H
#define ABYSS_ENCRYPTION_H

#include "abyss/crypto/symmetric_encryption.h"
#include "abyss/crypto/symmetric_stream.h"
#include "abyss/crypto/symmetric_message_authentication.h"
#include "abyss/crypto/types.h"
#include "abyss/crypto/asymmetric_encryption.h"

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
             * Encrypts a _message with a random key and a random nonce.
             * @param message Binary _message to encrypt
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const std::string &message);

            /**
             * Encrypts a _message with the provided key and a random nonce.
             * @param message Binary _message to encrypt
             * @param key Key used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const std::string &message, const std::string &key);

            /**
             * Encrypts a _message with the provided key and nonce.
             * @param message Binary _message to encrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const std::string &message, const std::string &key, const std::string &nonce);

            /**
             * Encrypts a _message with the provided key and nonce.
             * @param data Encryption struct with all required data fields
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(const encryption_data_t &data);

            /**
             * Encrypts a _message with a random key and a random nonce.
             * Stores the authentication tag separately from the _message
             * @param message Binary _message to encrypt
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(const std::string &message);

            /**
             * Encrypts a _message with the provided key and a random nonce.
             * Stores the authentication tag separately from the _message
             * @param message Binary _message to encrypt
             * @param key Key used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(const std::string &message, const std::string &key);

            /**
             * Encrypts a _message with the provided key and nonce.
             * Stores the authentication tag separately from the _message
             * @param message Binary _message to encrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Encrypted data struct
             */
            encrypted_data_detached_t
            encrypt_detached(const std::string &message, const std::string &key, const std::string &nonce);

            /**
             * Encrypts a _message with the provided key and nonce.
             * Stores the authentication tag separately from the _message
             * @param data Encryption struct with all required data fields
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(const encryption_data_t &data);

            /**
             * Decrypts a _message given nonce and key.
             * @param message Decryption struct with all required data fields
             * @return Decoded string
             */
            std::string decrypt(const decryption_data_t &data);

            /**
             * Decrypts a _message given nonce and key.
             * @param message Binary _message to decrypt
             * @param key Key used in encryption
             * @param nonce Random nonce used in encryption
             * @return Decoded string
             */
            std::string decrypt(const std::string &message, const std::string &key, const std::string &nonce);

            /**
             * Decrypts a _message given nonce and key.
             * Stores the authentication tag separately from the _message
             * @param message Decryption struct with all required data fields
             * @return Decoded string
             */
            std::string decrypt_detached(const decryption_data_detached_t &data);

            /**
             * Decrypts a _message given nonce and key.
             * Stores the authentication tag separately from the _message
             * @param authentication_tag Authentication tag used to avoid tampering
             * @param message Binary _message to decrypt
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
            std::shared_ptr<symmetric_stream> make_encryption_stream(const std::string &key);

            /**
             * Create an instance of the decryption stream loading the given key
             * @param header Header returned by the encryption process
             * @param key Key used in encryption
             * @return Symmetric stream working in decryption mode
             */
            std::shared_ptr<symmetric_stream>
            make_decryption_stream(const std::string &header, const std::string &key);
        }

        namespace auth {
            /**
             * Generates a random valid key
             * @return Key
             */
            std::string make_key();

            /**
             * Compute the authentication tag for the given _message
             * @param message Message whose tag will be computed
             * @param key Key used for tag computation
             * @return Message authentication tag
             */
            std::string compute(const std::string &message, const std::string &key);

            /**
             * Verify that the provided authentication tag matches the _message and key
             * @param tag Message authentication tag
             * @param message Message whose tag will be checked
             * @param key Key used for tag computation
             * @return True if verification is successful, false otherwise
             */
            bool verify(const std::string &tag, const std::string &message, const std::string &key);
        }
    }

    namespace asymmetric {
        // TODO: fill with asymmetric functions
    }
}

#endif //ABYSS_ENCRYPTION_H
