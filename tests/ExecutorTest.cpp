#include "Executor.hpp"

#include <gtest/gtest.h>
#include <memory>

namespace adas {
TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // Given: a vehicle starts at (0, 0) facing east.
    const std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);

    // When: query the pose without executing any commands.
    const Pose actual = executor->Query();

    // Then: position and heading must match the initial pose.
    EXPECT_EQ(0, actual.x);
    EXPECT_EQ(0, actual.y);
    EXPECT_EQ('E', actual.heading);
}
}  // namespace adas
