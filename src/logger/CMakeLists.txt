cmake_minimum_required(VERSION 3.22)

include(../../cmake/utils.cmake)
component_extract_version(abyss/logger ABYSS_LOGGER)

# conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# library flag modification/definition
set(spdlog_DIR ${CMAKE_BINARY_DIR})
set(fmt_DIR ${CMAKE_BINARY_DIR})
add_compile_definitions(FMT_HEADER_ONLY)

option(ABYSS_LOGGER_INCLUDES_QT_SINK "Build Logger with Qt sink support" OFF)
option(ABYSS_LOGGER_INCLUDES_SYSTEMD_SINK "Build Logger with Systemd sink support" OFF)
option(ABYSS_LOGGER_INCLUDES_MONGO_DB_SINK "Build Logger with Mongo Db sink support" OFF)

# source definitions
set(ABYSS_LOGGER_PUBLIC_API
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/helper_logger.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/helper_generator.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/settings.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/generator.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/helpers.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/logger.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/macro.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/version.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/version.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/abyss_logger.h
        ${CMAKE_CURRENT_LIST_DIR}/../../include/abyss/logger/types.h)
set(ABYSS_LOGGER_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/settings.cpp
        ${CMAKE_CURRENT_LIST_DIR}/generator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/helper_generator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/logger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/abyss_logger.cpp
        ${ABYSS_LOGGER_PUBLIC_API})

# create library
add_library(Logger ${ABYSS_LOGGER_SOURCES})
add_library(Abyss::Logger ALIAS Logger)
set_target_properties(Logger PROPERTIES
                VERSION ${ABYSS_LOGGER_VERSION}
                SOVERSION "${ABYSS_LOGGER_VERSION_MAJOR}.${ABYSS_LOGGER_VERSION_MINOR}")

# define macro values
if(ABYSS_LOGGER_INCLUDES_QT_SINK)
    target_compile_definitions(Logger PRIVATE INCLUDE_QT_SINK=true)
endif()
if(ABYSS_LOGGER_INCLUDES_SYSTEMD_SINK)
    target_compile_definitions(Logger PRIVATE INCLUDE_SYSTEMD_SINK=true)
endif()
if(ABYSS_LOGGER_INCLUDES_MONGO_DB_SINK)
    target_compile_definitions(Logger PRIVATE INCLUDE_MONGO_DB_SINK=true)
endif()

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
find_dependency(fmt)