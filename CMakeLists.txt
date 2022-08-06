cmake_minimum_required(VERSION 3.23)
project(spdlog-sample)

set(CMAKE_CXX_STANDARD 23)

# conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# library inclusion
#add_compile_definitions(FMT_HEADER_ONLY)
#find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# project asset definition
add_executable(${PROJECT_NAME} main.cpp Logger.cpp Logger.h)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        spdlog::libspdlog
        )
