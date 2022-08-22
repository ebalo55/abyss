cmake_minimum_required(VERSION 3.22)

include(../../cmake/utils.cmake)
component_extract_version(abyss/crypto ABYSS_CRYPTO)

# conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# library flag modification/definition
set(libsodium_DIR ${CMAKE_BINARY_DIR})

# source definitions
set(ABYSS_CRYPTO_PUBLIC_API
        ../../include/abyss/version.h ../../include/abyss/crypto/version.h ../../include/abyss/crypto/crypto.h
        ../../include/abyss/crypto/encodings.h ../../include/abyss/crypto/encode.h ../../include/abyss/crypto/pad.h
        ../../include/abyss/crypto/random.h ../../include/abyss/crypto/exceptions.h
        ../../include/abyss/crypto/symmetric_encryption.h ../../include/abyss/crypto/symmetric_stream.h
        ../../include/abyss/crypto/symmetric_message_authentication.h ../../include/abyss/crypto/encryption.h
        ../../include/abyss/crypto/asymmetric_encryption.h
        ../../include/abyss/crypto/asymmetric_message_authentication.h ../../include/abyss/crypto/types.h
        ../../include/abyss/crypto/hash_stream.h ../../include/abyss/crypto/hash.h
        ../../include/abyss/crypto/password_hash.h ../../include/abyss/crypto/key_derivation.h)
set(ABYSS_CRYPTO_SOURCES
        ${ABYSS_CRYPTO_PUBLIC_API}
        crypto.cpp encode.cpp exceptions.cpp encode.cpp pad.cpp random.cpp symmetric_encryption.cpp symmetric_stream.cpp
        symmetric_message_authentication.cpp asymmetric_encryption.cpp asymmetric_message_authentication.cpp hash.cpp
        hash_stream.cpp password_hash.cpp key_derivation.cpp)

find_package(libsodium REQUIRED)

# create library
add_library(Crypto ${ABYSS_CRYPTO_SOURCES})
add_library(Abyss::Crypto ALIAS Crypto)
target_link_libraries(Crypto PRIVATE libsodium::libsodium)
set_target_properties(Crypto PROPERTIES
        VERSION ${ABYSS_CRYPTO_VERSION}
        SOVERSION "${ABYSS_CRYPTO_VERSION_MAJOR}.${ABYSS_CRYPTO_VERSION_MINOR}")

# add include directories
target_include_directories(Crypto
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

# install the target and create export-set
install(TARGETS Crypto
        EXPORT CryptoTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/abyss
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/abyss
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/abyss
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

# install encryption_header_ file
install(FILES ${ABYSS_CRYPTO_PUBLIC_API} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/abyss/crypto)

# generate and install export file
install(EXPORT CryptoTargets
        FILE AbyssCryptoTargets.cmake
        NAMESPACE Abyss::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/abyss
        )

# library dependencies
include(CMakeFindDependencyMacro)
find_dependency(libsodium 1.0.18)
