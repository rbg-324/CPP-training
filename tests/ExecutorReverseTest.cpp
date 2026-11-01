#include "Executor.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

namespace adas {
namespace {
void ExpectPose(const Executor& executor, const Pose& expected)
{
    const auto actual = executor.Query();
    EXPECT_EQ(expected.x, actual.x);
    EXPECT_EQ(expected.y, actual.y);
    EXPECT_EQ(expected.heading, actual.heading);
}
}  // namespace

TEST(Reverse01, MovesBackInEveryHeading)
{
    std::cout << "Reverse 01: BM moves back one cell in E/W/N/S; heading unchanged" << std::endl;
    const Pose expected[]{{-1, 0, 'E'}, {1, 0, 'W'}, {0, -1, 'N'}, {0, 1, 'S'}};
    for (const auto& target : expected) {
        SCOPED_TRACE(target.heading);
        const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, target.heading}));
        ASSERT_NE(nullptr, executor);
        executor->Execute("BM");
        ExpectPose(*executor, target);
    }
}

TEST(Reverse02, LeftCommandTurnsRight)
{
    std::cout << "Reverse 02: BL from (0,0,E); expect (0,0,S)" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("BL");
    ExpectPose(*executor, {0, 0, 'S'});
}

TEST(Reverse03, RightCommandTurnsLeft)
{
    std::cout << "Reverse 03: BR from (0,0,E); expect (0,0,N)" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("BR");
    ExpectPose(*executor, {0, 0, 'N'});
}

TEST(Reverse04, FastReverseOrderIsIndependent)
{
    std::cout << "Reverse 04: BFM and FBM from E; both expect (-2,0,E)" << std::endl;
    for (const auto* commands : {"BFM", "FBM"}) {
        SCOPED_TRACE(commands);
        const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
        ASSERT_NE(nullptr, executor);
        executor->Execute(commands);
        ExpectPose(*executor, {-2, 0, 'E'});
    }
}

TEST(Reverse05, FastLeftMovesBackThenTurnsRight)
{
    std::cout << "Reverse 05: BFL from E; expect (-1,0,S)" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("BFL");
    ExpectPose(*executor, {-1, 0, 'S'});
}

TEST(Reverse06, FastRightMovesBackThenTurnsLeft)
{
    std::cout << "Reverse 06: BFR from E; expect (-1,0,N)" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("BFR");
    ExpectPose(*executor, {-1, 0, 'N'});
}

TEST(Reverse07, SecondBCancelsReverse)
{
    std::cout << "Reverse 07: BBM from N; expect normal movement (0,1,N)" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor);
    executor->Execute("BBM");
    ExpectPose(*executor, {0, 1, 'N'});
}

TEST(Reverse08, StatePersistsAcrossExecuteCalls)
{
    std::cout << "Reverse 08: B, M, BM in separate calls from E; x goes 0,-1,0" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("B");
    ExpectPose(*executor, {0, 0, 'E'});
    executor->Execute("M");
    ExpectPose(*executor, {-1, 0, 'E'});
    executor->Execute("BM");
    ExpectPose(*executor, {0, 0, 'E'});
}

TEST(Reverse09, FastAndReverseToggleIndependently)
{
    std::cout << "Reverse 09: BFFM then BFM from E; x goes -1 then 1" << std::endl;
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("BFFM");
    ExpectPose(*executor, {-1, 0, 'E'});
    executor->Execute("BFM");
    ExpectPose(*executor, {1, 0, 'E'});
}
}  // namespace adas
