cmake_minimum_required(VERSION 3.22)
enable_testing()

find_package(GTest REQUIRED)

add_executable(abyss_test
        logger/logger_test.cpp logger/helper_generator_test.cpp
        )
target_link_libraries(abyss_test GTest::gtest_main Abyss::Logger)
set_target_properties(abyss_test PROPERTIES LINKER_LANGUAGE CXX)

include(GoogleTest)
gtest_discover_tests(abyss_test)