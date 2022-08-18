//
// Created by ebalo on 18/08/22.
//

#ifndef ABYSS_ASYMMETRIC_ENCRYPTION_H
#define ABYSS_ASYMMETRIC_ENCRYPTION_H

#include <memory>
#include <sodium.h>
#include <string>
#include <sstream>
#include "abyss/crypto/random.h"
#include "abyss/crypto/exceptions.h"

namespace abyss::crypto {
    class asymmetric_encryption {
    private:
        static std::shared_ptr <asymmetric_encryption> instance_;
        std::stringstream ss_;

        asymmetric_encryption() = default;

        void cleanStream();

    public:
        static std::shared_ptr <asymmetric_encryption> getInstance();
    };
} // crypto

#endif //ABYSS_ASYMMETRIC_ENCRYPTION_H
