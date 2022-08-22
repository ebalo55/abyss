cmake_minimum_required(VERSION 3.22)
enable_testing()

find_package(GTest REQUIRED)

add_executable(abyss_logger_test
        logger/logger_test.cpp logger/helper_generator_test.cpp
        )
target_link_libraries(abyss_logger_test GTest::gtest_main Abyss::Logger)
set_target_properties(abyss_logger_test PROPERTIES LINKER_LANGUAGE CXX)

add_executable(abyss_crypto_test
        crypto/coder_test.cpp
        crypto/padder_test.cpp
        crypto/random_generator_test.cpp
        crypto/symmetric_encryption_test.cpp
        crypto/symmetric_stream_test.cpp
        crypto/symmetric_mac_test.cpp
        crypto/asymmetric_encryption_test.cpp
        crypto/asymmetric_mac_test.cpp
        crypto/hash_test.cpp
        )
target_link_libraries(abyss_crypto_test GTest::gtest_main Abyss::Crypto)
set_target_properties(abyss_crypto_test PROPERTIES LINKER_LANGUAGE CXX)

include(GoogleTest)
gtest_discover_tests(abyss_logger_test)
gtest_discover_tests(abyss_crypto_test)