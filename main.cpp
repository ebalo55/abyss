//
// Created by BLSMNL00E on 14/08/2022.
//
#include "abyss/crypto/crypto.h"
#include <iostream>

int main(int argc, char** argv) {
	abyss::crypto::init();
	std::cout << abyss::crypto::encode::hex("test") << std::endl;
}