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

namespace abyss::crypto::symmetric::auth {
    /**
     * Generates a random valid key
     * @return Key
     */
    std::string make_key();

    /**
     * Compute the authentication tag for the given message
     * @param message Message whose tag will be computed
     * @param key Key used for tag computation
     * @return Message authentication tag
     */
    std::string sign(const std::string &message, const std::string &key);

    /**
     * Verify that the provided authentication tag matches the message and key
     * @param tag Message authentication tag
     * @param message Message whose tag will be checked
     * @param key Key used for tag computation
     * @return True if verification is successful, false otherwise
     */
    bool verify(const std::string &tag, const std::string &message, const std::string &key);
} // crypto

#endif //ABYSS_SYMMETRIC_MESSAGE_AUTHENTICATION_H
