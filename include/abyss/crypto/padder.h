//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_PADDER_H
#define ABYSS_PADDER_H

#include <memory>
#include <sodium.h>
#include <string>
#include <sstream>
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto {
    class padder {
    private:
        static std::shared_ptr<padder> instance_;
        std::stringstream ss_;

        padder() = default;

        void cleanStream();

    public:
        static std::shared_ptr<padder> getInstance();

        std::string pad(const std::string &plain, size_t block_size);
        std::string unpad(const std::string &padded, size_t block_size);
    };
} // crypto

#endif //ABYSS_PADDER_H
