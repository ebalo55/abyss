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

namespace abyss::crypto::symmetric::stream {
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

#endif //ABYSS_ENCRYPTION_H
