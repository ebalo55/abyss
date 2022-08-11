cmake_minimum_required(VERSION 3.22)

include(cmake/utils.cmake)
extract_version(abyss ABYSS)

project(abyss VERSION ${ABYSS_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)

# components inclusion
add_subdirectory(src/logger)

# define package configurator
include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/AbyssConfigVersion.cmake"
        VERSION "${ABYSS_LOGGER_VERSION}"
        COMPATIBILITY AnyNewerVersion
)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/abyss.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/AbyssConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/abyss
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )
# install config files
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/AbyssConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/AbyssConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/abyss
        )
