//
// Created by ebalo on 18/08/22.
//

#ifndef ABYSS_ASYMMETRIC_MESSAGE_AUTHENTICATION_H
#define ABYSS_ASYMMETRIC_MESSAGE_AUTHENTICATION_H

#include <memory>
#include "sodium.h"
#include <string>
#include <sstream>
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"
#include "abyss/crypto/types.h"

namespace abyss::crypto::asymmetric::auth {
        /**
         * Generates a random valid keypair
         * @return Key
         */
        keypair_t make_keypair();

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
} // asymmetric

#endif //ABYSS_ASYMMETRIC_MESSAGE_AUTHENTICATION_H
