//
// Created by ebalo on 17/08/22.
//

#ifndef ABYSS_EXCEPTIONS_H
#define ABYSS_EXCEPTIONS_H

#include <exception>

namespace abyss::crypto::exception {
    class b64_decoding_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class hex_decoding_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class initialization_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class padding_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_message_encryption_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_message_decryption_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_stream_encryption_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_stream_decryption_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_stream_encryption_closed_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_stream_decryption_closed_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_stream_decryption_invalid_header_closed_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class symmetric_mac_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class asymmetric_encryption_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };

    class asymmetric_decryption_exception
            : std::exception {
    public:
        [[nodiscard]]
        const char *what() const noexcept override;
    };
}
#endif //ABYSS_EXCEPTIONS_H
