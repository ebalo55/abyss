//
// Created by ebalo on 14/08/2022.
//

#ifndef ABYSS_ENCODINGS_H
#define ABYSS_ENCODINGS_H

#include <sodium/utils.h>

enum encodings {
    _binary,
    _hex,
    _base64,
};

enum base64_variants {
    _classic = sodium_base64_VARIANT_ORIGINAL,
    _no_padding = sodium_base64_VARIANT_ORIGINAL_NO_PADDING,
    _url_safe = sodium_base64_VARIANT_URLSAFE,
    _url_safe_no_padding = sodium_base64_VARIANT_URLSAFE_NO_PADDING,
};

#endif //ABYSS_ENCODINGS_H
