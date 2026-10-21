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
    std::cout << "Test 04: facing W at (0,0); M moves to (-1,0,W)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'W'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(-1, actual.x); EXPECT_EQ(0, actual.y); EXPECT_EQ('W', actual.heading);
}

}  // namespace adas
