//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_EXCEPTIONS_H
#define ABYSS_EXCEPTIONS_H

#include <exception>

namespace abyss::crypto::exception {
    class b64_decoding_exception : std::exception {
    public:
        [[nodiscard]]
        const char * what() const noexcept override;
    };

    class hex_decoding_exception : std::exception {
    public:
        [[nodiscard]]
        const char * what() const noexcept override;
    };

    class initialization_exception : std::exception {
    public:
        [[nodiscard]]
        const char * what() const noexcept override;
    };
}
#endif //ABYSS_EXCEPTIONS_H
