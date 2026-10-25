#include "ExecutorImpl.hpp"
#include <new>
#include <string>

namespace adas {
Executor* Executor::NewExecutor(const Pose& initialPose) noexcept
{
    return new (std::nothrow) ExecutorImpl(initialPose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : pose(initialPose)
{
}

void ExecutorImpl::Execute(const std::string& commands)
{
    for (const char command : commands) {
        if (command == 'M') {
            MoveCommand{}.DoOperate(*this);
        } else if (command == 'L') {
            TurnLeftCommand{}.DoOperate(*this);
        } else if (command == 'R') {
            TurnRightCommand{}.DoOperate(*this);
        }
    }
}

void ExecutorImpl::Move() noexcept
{
    switch (pose.heading) {
    case 'E': ++pose.x; break;
    case 'W': --pose.x; break;
    case 'N': ++pose.y; break;
    case 'S': --pose.y; break;
    default: break;
    }
}

void ExecutorImpl::TurnLeft() noexcept
{
    switch (pose.heading) {
    case 'E': pose.heading = 'N'; break;
    case 'N': pose.heading = 'W'; break;
    case 'W': pose.heading = 'S'; break;
    case 'S': pose.heading = 'E'; break;
    default: break;
    }
}

void ExecutorImpl::TurnRight() noexcept
{
    switch (pose.heading) {
    case 'E': pose.heading = 'S'; break;
    case 'S': pose.heading = 'W'; break;
    case 'W': pose.heading = 'N'; break;
    case 'N': pose.heading = 'E'; break;
    default: break;
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas

