//
// Created by BLSMNL00E on 14/08/2022.
//

#ifndef ABYSS_ENCODINGS_H
#define ABYSS_ENCODINGS_H

#include <sodium/utils.h>

enum encodings {
	binary,
	hex,
	base64,
};

enum base64_variants {
	classic = sodium_base64_VARIANT_ORIGINAL,
	no_padding = sodium_base64_VARIANT_ORIGINAL_NO_PADDING,
	url_safe = sodium_base64_VARIANT_URLSAFE,
	url_safe_no_padding = sodium_base64_VARIANT_URLSAFE_NO_PADDING,
};

#endif //ABYSS_ENCODINGS_H
