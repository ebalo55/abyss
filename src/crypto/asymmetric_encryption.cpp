//
// Created by ebalo on 18/08/22.
//

#include "asymmetric_encryption.h"

namespace abyss::crypto {
    std::shared_ptr<symmetric_message_authentication> symmetric_message_authentication::instance_ = nullptr;

    void symmetric_message_authentication::cleanStream() {
        ss_.clear();
        ss_.str("");
    }

    std::shared_ptr<symmetric_message_authentication> symmetric_message_authentication::getInstance() {
        if (instance_ == nullptr) {
            instance_ = std::shared_ptr<symmetric_message_authentication>(new symmetric_message_authentication());
        }
        return instance_;
    }
} // crypto