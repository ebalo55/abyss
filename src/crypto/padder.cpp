//
// Created by ebalo on 17/08/22.
//

#include "abyss/crypto/padder.h"

namespace abyss::crypto {
    std::shared_ptr<padder> padder::instance_ = nullptr;

    void padder::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<padder> padder::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<padder>(new padder());
        }
        return instance_;
    }

    std::string padder::pad(const std::string &plain, size_t block_size) {
        cleanStream();

        // add the block size to the size of the string in order to always allow for the padding of the string
        size_t plain_size = plain.size() + block_size;

        // create and fill the buffer
        auto buf = new unsigned char[plain_size];
        plain.copy(reinterpret_cast<char *>(buf), plain.size());

        size_t real_length;

        if(sodium_pad(
                &real_length,
                buf,
                plain.size(),
                block_size,
                plain_size
                ) == 0) {
            ss_.write(reinterpret_cast<const char *>(buf), (long) real_length);
            delete[] buf;
            return ss_.str();
        }
        delete[] buf;
        throw exception::padding_exception();
    }

    std::string padder::unpad(const std::string &padded, size_t block_size) {
        cleanStream();

        size_t real_length;

        if(sodium_unpad(
                &real_length,
                reinterpret_cast<const unsigned char *>(padded.c_str()),
                padded.size(),
                block_size
        ) == 0) {
            ss_.write(padded.c_str(), (long) real_length);
            return ss_.str();
        }
        throw exception::padding_exception();
    }
} // crypto