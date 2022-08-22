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
#include "abyss/crypto/asymmetric_message_authentication.h"

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
            std::string sign(const std::string &message, const std::string &key);

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
        namespace message {
            /**
             * Generates a random valid keypair
             * @return Keypair
             */
            keypair_t make_keypair();

            /**
             * Regenerate the public key given the secret key
             * @param secret_key Secret key
             * @return Complete keypair
             */
            keypair_t restore_public_key(const std::string &secret_key);

            /**
             * Regenerate the public key given the secret key
             * @param partial_keypair Keypair containing secret key only. The public key will be appended to this keypair.
             */
            void restore_public_key(keypair_t &partial_keypair);

            /**
             * Creates a transitional keypair specifically for the encryption
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return
             */
            transitional_keypair_t make_encryption_shared_keypair(
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Creates a transitional keypair specifically for the decryption
             * @param sender_keypair Sender keypair, usually a partial keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a complete keypair is provided during encryption
             * @return
             */
            transitional_keypair_t make_decryption_shared_keypair(
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Generates a random valid nonce
             * @return Nonce
             */
            std::string make_nonce();

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param nonce Random nonce used in encryption
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(
                    const std::string &message,
                    const std::string &nonce,
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param nonce Random nonce used in encryption
             * @param sender_keypair Sender secret key
             * @param receiver_keypair Receiver public key
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(
                    const std::string &message,
                    const std::string &nonce,
                    const std::string &sender_secret_key,
                    const std::string &receiver_public_key
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param nonce Random nonce used in encryption
             * @param shared_key_pair Shared keypair computed using @code makeEncryptionSharedKeypair(...) @endcode
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(
                    const std::string &message,
                    const std::string &nonce,
                    const transitional_keypair_t &shared_key_pair
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(
                    const std::string &message,
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param sender_keypair Sender secret key
             * @param receiver_keypair Receiver public key
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(
                    const std::string &message,
                    const std::string &sender_secret_key,
                    const std::string &receiver_public_key
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param shared_key_pair Shared keypair computed using @code makeEncryptionSharedKeypair(...) @endcode
             * @return Encrypted data struct
             */
            encrypted_data_t encrypt(
                    const std::string &message,
                    const transitional_keypair_t &shared_key_pair
            );

            /**
             * Decrypts a message given nonce.
             * @param message Binary message to decrypt
             * @param nonce Random nonce used in encryption
             * @param sender_public_key Sender keypair public key
             * @param receiver_secret_key Receiver keypair secret key
             * @return Decoded string
             */
            std::string decrypt(
                    const std::string &message,
                    const std::string &nonce,
                    const std::string &sender_public_key,
                    const std::string &receiver_secret_key
            );

            /**
             * Decrypts a message given nonce.
             * @param message Binary message to decrypt
             * @param nonce Random nonce used in encryption
             * @param sender_keypair Sender keypair, usually a partial keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a complete keypair is provided during encryption
             * @return Decoded string
             */
            std::string decrypt(
                    const std::string &message,
                    const std::string &nonce,
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Decrypts a message given nonce.
             * @param message Binary message to decrypt
             * @param nonce Random nonce used in encryption
             * @param shared_key_pair Shared keypair computed using @code makeDecryptionSharedKeypair(...) @endcode
             * @return Decoded string
             */
            std::string decrypt(
                    const std::string &message,
                    const std::string &nonce,
                    const transitional_keypair_t &shared_key_pair
            );

            /**
             * Decrypts a message given nonce.
             * @param data Structured message to decode
             * @return Decoded string
             */
            std::string decrypt(const decryption_data_t &data);

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param nonce Random nonce used in encryption
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(
                    const std::string &message,
                    const std::string &nonce,
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param nonce Random nonce used in encryption
             * @param sender_keypair Sender secret key
             * @param receiver_keypair Receiver public key
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(
                    const std::string &message,
                    const std::string &nonce,
                    const std::string &sender_secret_key,
                    const std::string &receiver_public_key
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param nonce Random nonce used in encryption
             * @param shared_key_pair Shared keypair computed using @code makeEncryptionSharedKeypair(...) @endcode
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(
                    const std::string &message,
                    const std::string &nonce,
                    const transitional_keypair_t &shared_key_pair
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(
                    const std::string &message,
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param sender_keypair Sender secret key
             * @param receiver_keypair Receiver public key
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(
                    const std::string &message,
                    const std::string &sender_secret_key,
                    const std::string &receiver_public_key
            );

            /**
             * Encrypts a message with the provided key and nonce.
             * @param message Binary message to encrypt
             * @param shared_key_pair Shared keypair computed using @code makeEncryptionSharedKeypair(...) @endcode
             * @return Encrypted data struct
             */
            encrypted_data_detached_t encrypt_detached(
                    const std::string &message,
                    const transitional_keypair_t &shared_key_pair
            );

            /**
             * Decrypts a message given nonce.
             * @param authentication_tag Authentication tag used to avoid tampering
             * @param message Binary message to decrypt
             * @param nonce Random nonce used in encryption
             * @param sender_public_key Sender keypair public key
             * @param receiver_secret_key Receiver keypair secret key
             * @return Decoded string
             */
            std::string decrypt_detached(
                    const std::string &authentication_tag,
                    const std::string &message,
                    const std::string &nonce,
                    const std::string &sender_public_key,
                    const std::string &receiver_secret_key
            );

            /**
             * Decrypts a message given nonce.
             * @param authentication_tag Authentication tag used to avoid tampering
             * @param message Binary message to decrypt
             * @param nonce Random nonce used in encryption
             * @param sender_keypair Sender keypair, usually a partial keypair is provided during encryption
             * @param receiver_keypair Receiver keypair, usually a complete keypair is provided during encryption
             * @return Decoded string
             */
            std::string decrypt_detached(
                    const std::string &authentication_tag,
                    const std::string &message,
                    const std::string &nonce,
                    const keypair_t &sender_keypair,
                    const keypair_t &receiver_keypair
            );

            /**
             * Decrypts a message given nonce.
             * @param authentication_tag Authentication tag used to avoid tampering
             * @param message Binary message to decrypt
             * @param nonce Random nonce used in encryption
             * @param shared_key_pair Shared keypair computed using @code makeDecryptionSharedKeypair(...) @endcode
             * @return Decoded string
             */
            std::string decrypt_detached(
                    const std::string &authentication_tag,
                    const std::string &message,
                    const std::string &nonce,
                    const transitional_keypair_t &shared_key_pair
            );

            /**
             * Decrypts a message given nonce.
             * @param data Structured message to decode
             * @return Decoded string
             */
            std::string decrypt_detached(
                    const decryption_data_detached_t &data
            );
        }

        namespace auth {
            /**
             * Generates a random valid keypair
             * @return Key
             */
            keypair_t make_key();

            /**
             * Compute the authentication tag for the given message and return the combination of the message and the
             * authentication tag.
             * @param message Message whose tag will be computed
             * @param key Key used for tag computation
             * @return Message authentication tag
             */
            std::string sign(const std::string &message, const std::string &secret_key);

            /**
             * Compute the authentication tag for the given message and return the combination of the message and the
             * authentication tag.
             * @param message Message whose tag will be computed
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @return Message authentication tag
             */
            std::string sign(const std::string &message, const keypair_t &sender_keypair);

            /**
             * Verify that the provided combination of message + authentication tag matches the message and key
             * @param message Message whose tag will be checked
             * @param public_key Key used for tag verification
             * @return True if verification is successful, false otherwise
             */
            signature_data_t verify(const std::string &message, const std::string &public_key);

            /**
             * Verify that the provided combination of message + authentication tag matches the message and key
             * @param message Message whose tag will be checked
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return Structured confirmation data, .verified must be checked inside the returned struct
             */
            signature_data_t verify(const std::string &message, const keypair_t &receiver_keypair);

            /**
             * Compute the authentication tag for the given message
             * @param message Message whose tag will be computed
             * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
             * @return Message authentication tag
             */
            std::string sign_detached(const std::string &message, const keypair_t &sender_keypair);

            /**
             * Compute the authentication tag for the given message
             * @param message Message whose tag will be computed
             * @param secret_key Key used for tag computation
             * @return Message authentication tag
             */
            std::string sign_detached(const std::string &message, const std::string &secret_key);

            /**
             * Verify that the provided authentication tag matches the message and key
             * @param tag Message authentication tag
             * @param message Message whose tag will be checked
             * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
             * @return True if verification is successful, false otherwise
             */
            bool verify_detached(
                    const std::string &tag,
                    const std::string &message,
                    const keypair_t &receiver_keypair
            );

            /**
             * Verify that the provided authentication tag matches the message and key
             * @param tag Message authentication tag
             * @param message Message whose tag will be checked
             * @param public_key Key used for tag verification
             * @return True if verification is successful, false otherwise
             */
            bool verify_detached(
                    const std::string &tag,
                    const std::string &message,
                    const std::string &public_key
            );
        }
    }
}

#endif //ABYSS_ENCRYPTION_H
