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

}  // namespace adas
