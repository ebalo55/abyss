//
// Created by ebalo on 12/08/22.
//

#ifndef ABYSS_HELLO_TEST_CPP
#define ABYSS_HELLO_TEST_CPP

#include <gtest/gtest.h>
#include "abyss/logger/logger.h"

using namespace abyss::logger;

TEST(LoggerTest, CanInitializeSettingsAndGenerator) {
    // exists 2 copy of settings pointer once initialized, one is always stored in the class itself
    auto si = settings::getInstance();
    EXPECT_EQ(si.use_count(), 2);
    auto si_1 = settings::getInstance();
    EXPECT_EQ(si.get(), si_1.get());
    EXPECT_EQ(si.use_count(), 3);
    si.reset();
    EXPECT_EQ(si_1.use_count(), 2);
    si_1.reset();

    auto gi = generator::getInstance();
    EXPECT_EQ(gi.use_count(), 2);
    auto gi_1 = generator::getInstance();
    EXPECT_EQ(gi.get(), gi_1.get());
    EXPECT_EQ(gi.use_count(), 3);
    gi.reset();
    EXPECT_EQ(gi_1.use_count(), 2);
    gi_1.reset();

    init();
    EXPECT_NE(settings::getInstance(), si);
    EXPECT_NE(settings::getInstance().use_count(), 1);
    EXPECT_NE(settings::getInstance(), si_1);
    EXPECT_NE(generator::getInstance(), gi_1);
    EXPECT_NE(generator::getInstance().use_count(), 1);
    EXPECT_NE(generator::getInstance(), gi_1);
}

#endif //ABYSS_HELLO_TEST_CPP
