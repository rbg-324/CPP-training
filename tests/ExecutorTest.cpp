#include "Executor.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

namespace adas {
TEST(Test01, StoresInitialPose)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({2, -3, 'E'}));
        ASSERT_NE(nullptr, executor);
        const Pose actual = executor->Query();
        EXPECT_EQ(2, actual.x); EXPECT_EQ(-3, actual.y); EXPECT_EQ('E', actual.heading);
}

TEST(Test02, UsesDefaultPose)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor());
        ASSERT_NE(nullptr, executor);
        const Pose actual = executor->Query();
        EXPECT_EQ(0, actual.x); EXPECT_EQ(0, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test03, MovesForwardFacingE)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'E'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(1, actual.x); EXPECT_EQ(0, actual.y); EXPECT_EQ('E', actual.heading);
}

TEST(Test04, MovesForwardFacingW)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'W'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(-1, actual.x); EXPECT_EQ(0, actual.y); EXPECT_EQ('W', actual.heading);
}

TEST(Test05, MovesForwardFacingN)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'N'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(0, actual.x); EXPECT_EQ(1, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test06, MovesForwardFacingS)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'S'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(0, actual.x); EXPECT_EQ(-1, actual.y); EXPECT_EQ('S', actual.heading);
}

TEST(Test07, TurnsLeftFromE)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'E'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("L");
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test08, TurnsLeftFromN)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'N'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("L");
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('W', actual.heading);
}

TEST(Test09, TurnsLeftFromW)
{
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'W'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("L");
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('S', actual.heading);
}

TEST(Test10, TurnsLeftFromS)
{
    std::cout << "Test 10: facing S at (3,-4); L turns to E without moving" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'S'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("L");
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('E', actual.heading);
}

}  // namespace adas
