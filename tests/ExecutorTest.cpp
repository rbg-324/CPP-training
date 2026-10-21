#include "Executor.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

namespace adas {
TEST(Test01, StoresInitialPose)
{
    std::cout << "Test 01: specified initial pose (2,-3,E); no command; expect (2,-3,E)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({2, -3, 'E'}));
        ASSERT_NE(nullptr, executor);
        const Pose actual = executor->Query();
        EXPECT_EQ(2, actual.x); EXPECT_EQ(-3, actual.y); EXPECT_EQ('E', actual.heading);
}

TEST(Test02, UsesDefaultPose)
{
    std::cout << "Test 02: default initial pose; no command; expect (0,0,N)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor());
        ASSERT_NE(nullptr, executor);
        const Pose actual = executor->Query();
        EXPECT_EQ(0, actual.x); EXPECT_EQ(0, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test03, MovesForwardFacingE)
{
    std::cout << "Test 03: facing E at (0,0); M moves to (1,0,E)" << std::endl;
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

TEST(Test05, MovesForwardFacingN)
{
    std::cout << "Test 05: facing N at (0,0); M moves to (0,1,N)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'N'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(0, actual.x); EXPECT_EQ(1, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test06, MovesForwardFacingS)
{
    std::cout << "Test 06: facing S at (0,0); M moves to (0,-1,S)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({0, 0, 'S'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("M");
        const Pose actual = executor->Query();
        EXPECT_EQ(0, actual.x); EXPECT_EQ(-1, actual.y); EXPECT_EQ('S', actual.heading);
}

TEST(Test07, TurnsLeftFromE)
{
    std::cout << "Test 07: facing E at (3,-4); L turns to N without moving" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'E'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("L");
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test08, TurnsLeftFromN)
{
    std::cout << "Test 08: facing N at (3,-4); L turns to W without moving" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'N'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("L");
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('W', actual.heading);
}

TEST(Test09, TurnsLeftFromW)
{
    std::cout << "Test 09: facing W at (3,-4); L turns to S without moving" << std::endl;
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

TEST(Test11, TurnsRightPair1)
{
    std::cout << "Test 11: R turns E to S and S to W without moving" << std::endl;
    struct Case { char before; char after; };
        const Case cases[] = {{'E', 'S'}, {'S', 'W'}};
        for (const auto& item : cases) {
            const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, item.before}));
            ASSERT_NE(nullptr, executor);
            executor->Execute("R");
            const Pose actual = executor->Query();
            EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ(item.after, actual.heading);
        }
}

TEST(Test12, TurnsRightPair2)
{
    std::cout << "Test 12: R turns W to N and N to E without moving" << std::endl;
    struct Case { char before; char after; };
        const Case cases[] = {{'W', 'N'}, {'N', 'E'}};
        for (const auto& item : cases) {
            const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, item.before}));
            ASSERT_NE(nullptr, executor);
            executor->Execute("R");
            const Pose actual = executor->Query();
            EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ(item.after, actual.heading);
        }
}

TEST(Test13, ExecutesMixedCommandsInOrder)
{
    std::cout << "Test 13: default pose; MLMMRM executes in order; expect (-2,2,N)" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor());
        ASSERT_NE(nullptr, executor);
        executor->Execute("MLMMRM");
        const Pose actual = executor->Query();
        EXPECT_EQ(-2, actual.x); EXPECT_EQ(2, actual.y); EXPECT_EQ('N', actual.heading);
}

TEST(Test14, EmptyCommandKeepsPose)
{
    std::cout << "Test 14: pose (3,-4,S); empty command keeps the same pose" << std::endl;
    const auto executor = std::unique_ptr<Executor>(Executor::NewExecutor({3, -4, 'S'}));
        ASSERT_NE(nullptr, executor);
        EXPECT_NO_THROW(executor->Execute(""));
        const Pose actual = executor->Query();
        EXPECT_EQ(3, actual.x); EXPECT_EQ(-4, actual.y); EXPECT_EQ('S', actual.heading);
}

}  // namespace adas
