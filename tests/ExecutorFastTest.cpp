#include "Executor.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

namespace adas {
TEST(Fast01, MovesTwoCellsEast)
{
    std::cout << "Fast 01: FM from (0,0,E); M advances two cells; expect (2,0,E)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("FM");
    const Pose actual = executor->Query();
    EXPECT_EQ(2, actual.x);
    EXPECT_EQ(0, actual.y);
    EXPECT_EQ('E', actual.heading);
}

TEST(Fast02, MovesBeforeLeftTurn)
{
    std::cout << "Fast 02: FL from (0,0,E); move one cell, then turn left; expect (1,0,N)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("FL");
    const Pose actual = executor->Query();
    EXPECT_EQ(1, actual.x);
    EXPECT_EQ(0, actual.y);
    EXPECT_EQ('N', actual.heading);
}

TEST(Fast03, MovesBeforeRightTurn)
{
    std::cout << "Fast 03: FR from (0,0,E); move one cell, then turn right; expect (1,0,S)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("FR");
    const Pose actual = executor->Query();
    EXPECT_EQ(1, actual.x);
    EXPECT_EQ(0, actual.y);
    EXPECT_EQ('S', actual.heading);
}

TEST(Fast04, SecondFCancelsAndNextFReenables)
{
    std::cout << "Fast 04: FFM from (0,0,N) cancels fast mode; another FM re-enables it; expect y=3" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor);
    executor->Execute("FFM");
    EXPECT_EQ(1, executor->Query().y);
    executor->Execute("FM");
    const Pose actual = executor->Query();
    EXPECT_EQ(0, actual.x);
    EXPECT_EQ(3, actual.y);
    EXPECT_EQ('N', actual.heading);
}
}  // namespace adas
