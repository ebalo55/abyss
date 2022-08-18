//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_SYMMETRIC_STREAM_H
#define ABYSS_SYMMETRIC_STREAM_H

#include <memory>
#include <sodium.h>
#include <string>
#include <sstream>
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto {

    enum symmetric_stream_tag {
        message = crypto_secretstream_xchacha20poly1305_TAG_MESSAGE,
        stream_end = crypto_secretstream_xchacha20poly1305_TAG_FINAL,
        message_end = crypto_secretstream_xchacha20poly1305_TAG_PUSH,
        rekey = crypto_secretstream_xchacha20poly1305_TAG_REKEY
    };

    class symmetric_stream {
    private:
        std::stringstream ss_;

        crypto_secretstream_xchacha20poly1305_state state_;
        unsigned char encryption_header_[crypto_secretstream_xchacha20poly1305_HEADERBYTES];

        bool is_stream_open_ = false;
        bool is_operating_in_encryption_mode_;

        symmetric_stream_tag tag_keeper_ = message;

        void cleanStream();

        std::string encryptPushingToStream(const std::string &message, symmetric_stream_tag tag);

        std::string decryptPushingToStream(const std::string &message);

        explicit symmetric_stream(const std::string &key);

        symmetric_stream(const std::string &header, const std::string &key);

    public:
        symmetric_stream() = delete;

        /**
         * Create an instance of the encryption stream loading the given key
         * @param key Key used in encryption
         * @return Symmetric stream working in encryption mode
         */
        static std::shared_ptr<symmetric_stream> makeEncryptionStream(const std::string &key);

        /**
         * Create an instance of the decryption stream loading the given key
         * @param header Header returned by the encryption process
         * @param key Key used in encryption
         * @return Symmetric stream working in decryption mode
         */
        static std::shared_ptr<symmetric_stream>
        makeDecryptionStream(const std::string &header, const std::string &key);

        /**
         * Generates a random valid encryption key
         * @return Encryption key
         */
        static std::string makeEncryptionKey();

        /**
         * Closes the current stream returning an encrypted closing message.
         * NOTE: This method returns an empty string if called from a decryption stream.
         * NOTE: To avoid empty closing message consider using
         * @code
         * write("<your string>", symmetric_stream_tag::stream_end)
         * @endcode
         * @return
         */
        std::string closeStream();

        /**
         * Closes the current message returning an encrypted closing message.
         * NOTE: This method returns an empty string if called from a decryption stream.
         * NOTE: To avoid empty closing message consider using
         * @code
         * write("<your string>", symmetric_stream_tag::message_end)
         * @endcode
         * @return
         */
        std::string closeMessage();

        /**
         * Get the current stream header
         * @return
         */
        std::string header();

        /**
         * Get the last decrypted tag
         * @return
         */
        symmetric_stream_tag lastTag();

        /**
         * Checks whether the current stream is open
         * @return
         */
        bool isStreamOpen();

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const std::string &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const int &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const float &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const double &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const unsigned int &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const long &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const unsigned long &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const long long &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @return Binary message encrypted/decrypted
         */
        std::string write(const unsigned long long &message);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const std::string &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const int &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const float &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const double &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const unsigned int &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const long &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const unsigned long &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const long long &message, symmetric_stream_tag tag);

        /**
         * Write a message to the stream and returns the encrypted or decrypted content depending on the operation mode
         * @param message Message to encrypt/decrypt
         * @param tag Tag to append to the message
         * @return Binary message encrypted/decrypted
         */
        std::string write(const unsigned long long &message, symmetric_stream_tag tag);
    };

}

#endif //ABYSS_SYMMETRIC_STREAM_H
