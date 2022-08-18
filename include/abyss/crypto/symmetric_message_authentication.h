//
// Created by ebalo on 18/08/22.
//

#ifndef ABYSS_SYMMETRIC_MESSAGE_AUTHENTICATION_H
#define ABYSS_SYMMETRIC_MESSAGE_AUTHENTICATION_H

#include <memory>
#include <sodium.h>
#include <string>
#include <sstream>
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto::symmetric {
    class symmetric_message_authentication {
    private:
        static std::shared_ptr<symmetric_message_authentication> instance_;
        std::stringstream ss_;

        symmetric_message_authentication() = default;

        void cleanStream();

    public:
        static std::shared_ptr<symmetric_message_authentication> getInstance();

        /**
         * Generates a random valid key
         * @return Key
         */
        std::string makeKey();

        /**
         * Compute the authentication tag for the given _message
         * @param message Message whose tag will be computed
         * @param key Key used for tag computation
         * @return Message authentication tag
         */
        std::string computeAuthenticationTag(const std::string &message, const std::string &key);

        /**
         * Verify that the provided authentication tag matches the _message and key
         * @param tag Message authentication tag
         * @param message Message whose tag will be checked
         * @param key Key used for tag computation
         * @return True if verification is successful, false otherwise
         */
        bool verifyAuthenticationTag(const std::string &tag, const std::string &message, const std::string &key);
    };
} // crypto

#endif //ABYSS_SYMMETRIC_MESSAGE_AUTHENTICATION_H
