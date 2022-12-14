//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_HASH_STREAM_H
#define ABYSS_HASH_STREAM_H

#include <memory>
#include <sodium.h>
#include <string>
#include <sstream>
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"
#include "abyss/crypto/types.h"

namespace abyss::crypto::hash {
    class hash_stream {
    private:
        std::stringstream ss_;

        crypto_generichash_state state_;
        unsigned hash_size_ = 0;

        void init_state(const std::string &key, security_level sec);
    public:
        explicit hash_stream(const std::string &key);
        hash_stream(const std::string &key, security_level sec);
        explicit hash_stream(security_level sec);
        hash_stream();

        /**
         * Closes the current stream returning an hashed message.
         * @return
         */
        std::string closeStream();

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const std::string &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const int &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const float &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const double &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const unsigned int &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const long &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const unsigned long &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const long long &message);

        /**
         * Write a message to the stream
         * @param message Message to hash
         * @return True if hash stream succeeded, false otherwise
         */
        bool write(const unsigned long long &message);
    };
}

#endif //ABYSS_HASH_STREAM_H
