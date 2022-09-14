//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/symmetric_stream.h"

namespace abyss::crypto::symmetric {
    symmetric_stream::symmetric_stream(const std::string &key)
            : is_operating_in_encryption_mode_(true), is_stream_open_(true) {
        // initialize the encryption mode of the class
        crypto_secretstream_xchacha20poly1305_init_push(
                &state_,
                encryption_header_,
                reinterpret_cast<const unsigned char *>(key.c_str())
        );
    }

    symmetric_stream::symmetric_stream(
            const std::string &header,
            const std::string &key
    ) : is_operating_in_encryption_mode_(false) {
        // initialize the decryption mode of the class, in case the header is invalid the creation of the class fails
        if (crypto_secretstream_xchacha20poly1305_init_pull(
                &state_,
                reinterpret_cast<const unsigned char *>(header.c_str()),
                reinterpret_cast<const unsigned char *>(key.c_str())
        ) != 0) {
            throw exception::symmetric_stream_decryption_invalid_header_closed_exception();
        }

        is_stream_open_ = true;
    }

    void symmetric_stream::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::string symmetric_stream::makeEncryptionKey() {
        std::stringstream ss;

        // creates the keygen
        auto key_buf = new unsigned char[crypto_secretstream_xchacha20poly1305_KEYBYTES];
        crypto_secretstream_xchacha20poly1305_keygen(key_buf);

        // insert the keygen in the stream and clean memory
        ss.write(reinterpret_cast<const char *>(key_buf), (long) crypto_secretstream_xchacha20poly1305_KEYBYTES);
        delete[] key_buf;

        return ss.str();
    }

    std::string symmetric_stream::closeStream() {
        if (is_operating_in_encryption_mode_) {
            return write("", symmetric_stream_tag::_stream_end);
        }
        return "";
    }

    std::string symmetric_stream::closeMessage() {
        if (is_operating_in_encryption_mode_) {
            return write("", symmetric_stream_tag::_message_end);
        }
        return "";
    }

    std::string
    symmetric_stream::encryptPushingToStream(const std::string &message, symmetric_stream_tag tag) {
        cleanStream();

        if (!is_stream_open_) {
            throw exception::symmetric_stream_encryption_closed_exception();
        }

        // initialize the chunk
        size_t chunk_size = message.size() + crypto_secretstream_xchacha20poly1305_ABYTES;
        auto chunk = new unsigned char[chunk_size];

        if (crypto_secretstream_xchacha20poly1305_push(
                &state_,
                chunk,
                nullptr,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                nullptr,
                0,
                tag
        ) == 0) {
            // close the stream immediately if a _message is marked with an ending tag
            if (tag == symmetric_stream_tag::_stream_end) {
                is_stream_open_ = false;
            }

            ss_.write(reinterpret_cast<const char *>(chunk), (long) chunk_size);
            delete[] chunk;
            return ss_.str();
        }

        throw exception::symmetric_stream_encryption_exception();
    }

    std::string symmetric_stream::header() {
        cleanStream();

        ss_.write(
                reinterpret_cast<const char *>(encryption_header_),
                (long) crypto_secretstream_xchacha20poly1305_HEADERBYTES
        );
        return ss_.str();
    }

    std::string
    symmetric_stream::decryptPushingToStream(const std::string &message) {
        cleanStream();

        if (!is_stream_open_) {
            throw exception::symmetric_stream_decryption_closed_exception();
        }

        // initialize the chunk
        size_t chunk_size = message.size() - crypto_secretstream_xchacha20poly1305_ABYTES;
        auto chunk = new unsigned char[chunk_size];
        unsigned char decrypted_tag;

        if (crypto_secretstream_xchacha20poly1305_pull(
                &state_,
                chunk,
                nullptr,
                &decrypted_tag,
                reinterpret_cast<const unsigned char *>(message.c_str()),
                message.size(),
                nullptr,
                0
        ) == 0) {
            // store the decrypted tag into the provided tag keeper
            switch (decrypted_tag) {
                default:
                case crypto_secretstream_xchacha20poly1305_TAG_MESSAGE:
                    tag_keeper_ = symmetric_stream_tag::_message;
                    break;
                case crypto_secretstream_xchacha20poly1305_TAG_FINAL:
                    tag_keeper_ = symmetric_stream_tag::_stream_end;
                    is_stream_open_ = false;
                    break;
                case crypto_secretstream_xchacha20poly1305_TAG_PUSH:
                    tag_keeper_ = symmetric_stream_tag::_message_end;
                    break;
                case crypto_secretstream_xchacha20poly1305_TAG_REKEY:
                    tag_keeper_ = symmetric_stream_tag::_rekey;
                    break;
            }
            ss_.write(reinterpret_cast<const char *>(chunk), (long) chunk_size);
            delete[] chunk;
            return ss_.str();
        }

        throw exception::symmetric_stream_decryption_exception();
    }

    std::shared_ptr<symmetric_stream> symmetric_stream::makeEncryptionStream(const std::string &key) {
        return std::shared_ptr<symmetric_stream>(new symmetric_stream(key));
    }

    std::shared_ptr<symmetric_stream>
    symmetric_stream::makeDecryptionStream(const std::string &header, const std::string &key) {
        return std::shared_ptr<symmetric_stream>(new symmetric_stream(header, key));
    }

    symmetric_stream_tag symmetric_stream::lastTag() {
        return tag_keeper_;
    }

    std::string symmetric_stream::write(const int &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const float &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const double &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const unsigned int &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const long &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const unsigned long &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const long long int &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const unsigned long long int &message) {
        return write(std::to_string(message));
    }

    std::string symmetric_stream::write(const std::string &message) {
        if (is_operating_in_encryption_mode_) {
            return encryptPushingToStream(message, symmetric_stream_tag::_message);
        }
        return decryptPushingToStream(message);
    }

    std::string symmetric_stream::write(const std::string &message, symmetric_stream_tag tag) {
        if (is_operating_in_encryption_mode_) {
            return encryptPushingToStream(message, tag);
        }
        return decryptPushingToStream(message);
    }

    std::string symmetric_stream::write(const int &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const float &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const double &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const unsigned int &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const long &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const unsigned long &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const long long int &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    std::string symmetric_stream::write(const unsigned long long int &message, symmetric_stream_tag tag) {
        return write(std::to_string(message), tag);
    }

    bool symmetric_stream::isStreamOpen() {
        return is_stream_open_;
    }
}