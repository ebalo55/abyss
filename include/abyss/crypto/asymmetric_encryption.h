//
// Created by ebalo on 18/08/22.
//

#ifndef ABYSS_ASYMMETRIC_ENCRYPTION_H
#define ABYSS_ASYMMETRIC_ENCRYPTION_H

#include <memory>
#include "sodium.h"
#include <string>
#include <sstream>
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"
#include "abyss/crypto/types.h"

namespace abyss::crypto::asymmetric {
    class asymmetric_encryption {
    private:
        static std::shared_ptr<asymmetric_encryption> instance_;
        std::stringstream ss_;

        asymmetric_encryption() = default;

        void cleanStream();

    public:
        static std::shared_ptr<asymmetric_encryption> getInstance();

        /**
         * Generates a random valid keypair
         * @return Keypair
         */
        keypair_t makeKeypair();

        /**
         * Regenerate the public key given the secret key
         * @param secret_key Secret key
         * @return Complete keypair
         */
        keypair_t restorePublicKey(const std::string &secret_key);

        /**
         * Regenerate the public key given the secret key
         * @param partial_keypair Keypair containing secret key only. The public key will be appended to this keypair.
         */
        void restorePublicKey(keypair_t &partial_keypair);

        /**
         * Creates a transitional keypair specifically for the encryption
         * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
         * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
         * @return
         */
        transitional_keypair_t makeEncryptionSharedKeypair(
                const keypair_t &sender_keypair,
                const keypair_t &receiver_keypair
        );

        /**
         * Creates a transitional keypair specifically for the decryption
         * @param sender_keypair Sender keypair, usually a partial keypair is provided during encryption
         * @param receiver_keypair Receiver keypair, usually a complete keypair is provided during encryption
         * @return
         */
        transitional_keypair_t makeDecryptionSharedKeypair(
                const keypair_t &sender_keypair,
                const keypair_t &receiver_keypair
        );

        /**
         * Generates a random valid nonce
         * @return Nonce
         */
        std::string makeNonce();

        /**
         * Encrypts a message with the provided key and nonce.
         * @param message Binary message to encrypt
         * @param nonce Random nonce used in encryption
         * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
         * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
         * @return Encrypted data struct
         */
        encrypted_data_t encryptMessage(
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
        encrypted_data_t encryptMessage(
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
        encrypted_data_t encryptMessage(
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
        encrypted_data_t encryptMessage(
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
        encrypted_data_t encryptMessage(
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
        encrypted_data_t encryptMessage(
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
        std::string decryptMessage(
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
        std::string decryptMessage(
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
        std::string decryptMessage(
                const std::string &message,
                const std::string &nonce,
                const transitional_keypair_t &shared_key_pair
        );

        /**
         * Decrypts a message given nonce.
         * @param data Structured message to decode
         * @return Decoded string
         */
        std::string decryptMessage(const decryption_data_t &data);

        /**
         * Encrypts a message with the provided key and nonce.
         * @param message Binary message to encrypt
         * @param nonce Random nonce used in encryption
         * @param sender_keypair Sender keypair, usually a complete keypair is provided during encryption
         * @param receiver_keypair Receiver keypair, usually a partial keypair is provided during encryption
         * @return Encrypted data struct
         */
        encrypted_data_detached_t encryptMessageDetached(
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
        encrypted_data_detached_t encryptMessageDetached(
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
        encrypted_data_detached_t encryptMessageDetached(
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
        encrypted_data_detached_t encryptMessageDetached(
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
        encrypted_data_detached_t encryptMessageDetached(
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
        encrypted_data_detached_t encryptMessageDetached(
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
        std::string decryptMessageDetached(
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
        std::string decryptMessageDetached(
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
        std::string decryptMessageDetached(
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
        std::string decryptMessageDetached(
                const decryption_data_detached_t &data
        );
    };
} // crypto

#endif //ABYSS_ASYMMETRIC_ENCRYPTION_H
