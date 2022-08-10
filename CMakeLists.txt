cmake_minimum_required(VERSION 3.23)
project(abyss)

set(CMAKE_CXX_STANDARD 23)

# conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# library inclusion
add_compile_definitions(FMT_HEADER_ONLY)
#find_package(spdlog REQUIRED)

# project asset definition
add_executable(${PROJECT_NAME} main.cpp logger/Settings.cpp logger/Settings.h logger/helpers/helper_logger.h
        logger/Generator.cpp logger/Generator.h logger/helpers.h logger/helpers/helper_generator.h logger/logger.h
        logger/macro.h)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${CONAN_LIBS}
        )
