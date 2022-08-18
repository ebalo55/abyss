//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/logger/logger.h"

using namespace abyss::logger;

TEST(LoggerTest, AllSinkLoggerExists) {
    init();
    EXPECT_NE(get(ABYSS_LOGGER_ALL_CHANNEL), nullptr);
    EXPECT_TRUE(exists(ABYSS_LOGGER_ALL_CHANNEL));
}

TEST(LoggerTest, ListsAllSinks) {
    init();
    EXPECT_EQ(list(), std::vector<std::string>{ABYSS_LOGGER_ALL_CHANNEL});

    auto stdout_logger = make_stdout_logger("test");
    EXPECT_EQ(list(), std::vector<std::string>({ABYSS_LOGGER_ALL_CHANNEL, "test"}));
}

TEST(LoggerTest, AllGeneratorsReturnPointers) {
    init();
    EXPECT_NE(make_stdout_logger("0"), nullptr);
    EXPECT_NE(make_stderr_logger("1"), nullptr);
    EXPECT_NE(make_rotating_file_logger("2", "test/logs/rotating.log", 1024, 1), nullptr);
    EXPECT_NE(make_daily_rotating_file_logger("3", "test/logs/daily.log", 12, 0), nullptr);
    EXPECT_NE(make_file_logger("4", "test/logs/simple.log"), nullptr);
    EXPECT_NE(make_syslog_logger("5", "test-logger"), nullptr);
#if includes_systemd()
    EXPECT_NE(make_systemd_logger("6", "test-logger"), nullptr);
#endif
#if _WIN32
    EXPECT_NE(make_windows_debug_logger("7"), nullptr);
#endif
    EXPECT_NE(make_group("8", {}), nullptr);
    EXPECT_NE(make_hourly_rotating_file_logger("10", "test/logs/hourly.log"), nullptr);
#if includes_mongo_db()
    EXPECT_NE(make_mongo_db_logger("11", "test", "test"), nullptr);
#endif
    // socket opening required
//    spdlog::sinks::tcp_sink_config tcp_config("127.0.0.1", 8000);
//    EXPECT_NE(make_tcp_logger("12", tcp_config), nullptr);
//    spdlog::sinks::udp_sink_config udp_config("127.0.0.1", 8000);
//    EXPECT_NE(make_udp_logger("13", udp_config), nullptr);
#if _WIN32
    EXPECT_NE(make_windows_event_registry_logger("14", "test-id"), nullptr);
#endif
}

#endif //ABYSS_HELLO_TEST_CPP
