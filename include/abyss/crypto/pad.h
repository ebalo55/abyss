//
// Created by ebalo on 14/08/2022.
//

#ifndef ABYSS_PAD_H
#define ABYSS_PAD_H

#include <string>
#include <sstream>
#include "abyss/crypto/padder.h"

namespace abyss::crypto::pad {
	/**
	 * Pad the given string to the provided number of characters
	 * @param plain String to pad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string pad(const std::string& plain, size_t block_size);
	
	/**
	 * Unpad the given string given the block size
	 * @param padded String to unpad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string unpad(const std::string &padded, size_t block_size);
    
	/**
	 * Pad the given string to 4 characters
	 * @param plain String to pad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string pad_4(const std::string& plain);
	
	/**
	 * Unpad the given string padded with 4 characters
	 * @param padded String to unpad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string unpad_4(const std::string &padded);
    
	/**
	 * Pad the given string to 8 characters
	 * @param plain String to pad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string pad_8(const std::string& plain);
	
	/**
	 * Unpad the given string padded with 8 characters
	 * @param padded String to unpad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string unpad_8(const std::string &padded);
    
	/**
	 * Pad the given string to 16 characters
	 * @param plain String to pad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string pad_16(const std::string& plain);
	
	/**
	 * Unpad the given string padded with 16 characters
	 * @param padded String to unpad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string unpad_16(const std::string &padded);
    
	/**
	 * Pad the given string to 32 characters
	 * @param plain String to pad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string pad_32(const std::string& plain);
	
	/**
	 * Unpad the given string padded with 32 characters
	 * @param padded String to unpad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string unpad_32(const std::string &padded);
    
	/**
	 * Pad the given string to 64 characters
	 * @param plain String to pad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string pad_64(const std::string& plain);
	
	/**
	 * Unpad the given string padded with 64 characters
	 * @param padded String to unpad
	 * @param block_size Pad block size
	 * @return
	 */
	std::string unpad_64(const std::string &padded);
}

#endif //ABYSS_PAD_H
