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
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/version.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/crypto/version.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/crypto/crypto.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/crypto/encodings.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/crypto/encode.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/crypto/coder.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/crypto/exceptions.h)
set(ABYSS_CRYPTO_SOURCES
        ${ABYSS_CRYPTO_PUBLIC_API}
        ${CMAKE_CURRENT_LIST_DIR}/crypto.cpp
        ${CMAKE_CURRENT_LIST_DIR}/encode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/exceptions.cpp
        ${CMAKE_CURRENT_LIST_DIR}/coder.cpp)

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

# install header file
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
