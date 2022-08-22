//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/hash_stream.h"

namespace abyss::crypto::hash {
    hash_stream::hash_stream(const std::string &key) {
        init_state(key, average);
    }

    hash_stream::hash_stream() {
        init_state("", average);
    }

    hash_stream::hash_stream(const std::string &key, security_level sec) {
        init_state(key, sec);
    }

    hash_stream::hash_stream(security_level sec) {
        init_state("", sec);
    }

    void hash_stream::init_state(const std::string &key, security_level sec) {
        switch (sec) {
            case minimum:
                hash_size_ = crypto_generichash_BYTES_MIN;
                break;
            case average:
                hash_size_ = crypto_generichash_BYTES;
                break;
            case maximum:
                hash_size_ = crypto_generichash_BYTES_MAX;
                break;
        }

        // initialize the encryption mode of the class
        crypto_generichash_init(
                &state_,
                reinterpret_cast<const unsigned char *>(key.c_str()),
                key.size(),
                hash_size_
        );
    }

    std::string hash_stream::closeStream() {
        std::stringstream ss;
        auto hash = new unsigned char[hash_size_];

        crypto_generichash_final(&state_, hash, hash_size_);
        ss.write(reinterpret_cast<const char *>(hash), hash_size_);
        return ss.str();
    }

    bool hash_stream::write(const int &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const float &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const double &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const unsigned int &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const long &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const unsigned long &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const long long int &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const unsigned long long int &message) {
        return write(std::to_string(message));
    }

    bool hash_stream::write(const std::string &message) {
        return crypto_generichash_update(
                &state_,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size()
        ) == 0;
    }
}