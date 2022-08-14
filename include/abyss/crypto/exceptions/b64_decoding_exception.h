//
// Created by BLSMNL00E on 14/08/2022.
//

#ifndef ABYSS_INITIALIZATION_EXCEPTION_H
#define ABYSS_INITIALIZATION_EXCEPTION_H

#include <exception>

namespace abyss::crypto::exceptions {
	class b64_decoding_exception : std::exception {
	public:
		[[nodiscard]]
		const char * what() const noexcept override;
	};
} // abyss::crypto

#endif //ABYSS_INITIALIZATION_EXCEPTION_H
