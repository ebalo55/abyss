cmake_minimum_required(VERSION 3.23)

include(../../cmake/utils.cmake)
component_extract_version(abyss/logger ABYSS_LOGGER)

# conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# library flag modification/definition
set(spdlog_DIR ${CMAKE_BINARY_DIR})
set(fmt_DIR ${CMAKE_BINARY_DIR})
add_compile_definitions(FMT_HEADER_ONLY)

# source definitions
set(ABYSS_LOGGER_PUBLIC_API
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/helper_logger.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/helper_generator.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/Settings.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/Generator.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/helpers.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/logger.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/macro.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/version.h)
set(ABYSS_LOGGER_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/Settings.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Generator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/helper_generator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/helper_logger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/logger.cpp
        ${ABYSS_LOGGER_PUBLIC_API})

# create library
add_library(Logger ${ABYSS_LOGGER_SOURCES})
add_library(Abyss::Logger ALIAS Logger)
set_target_properties(Logger PROPERTIES
                VERSION ${ABYSS_LOGGER_VERSION}
                SOVERSION "${ABYSS_LOGGER_VERSION_MAJOR}.${ABYSS_LOGGER_VERSION_MINOR}")

# add include directories
target_include_directories(Logger
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

# install the target and create export-set
install(TARGETS Logger
        EXPORT LoggerTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/abyss
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/abyss
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/abyss
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

# install header file
install(FILES ${ABYSS_LOGGER_PUBLIC_API} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/abyss/logger)

# generate and install export file
install(EXPORT LoggerTargets
        FILE AbyssLoggerTargets.cmake
        NAMESPACE Abyss::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/abyss
        )

# library dependencies
include(CMakeFindDependencyMacro)
find_dependency(spdlog 1.10.0)
find_dependency(fmt 8.1.1)