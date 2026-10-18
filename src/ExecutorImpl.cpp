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
    const char firstCommand = commands.at(0);
    const char command = firstCommand;
    if (command == 'M') {
        switch (pose.heading) {
        case 'E': ++pose.x; break;
        case 'W': --pose.x; break;
        case 'N': ++pose.y; break;
        case 'S': --pose.y; break;
        default: break;
        }
    } else if (command == 'L') {
        switch (pose.heading) {
        case 'E': pose.heading = 'N'; break;
        case 'N': pose.heading = 'W'; break;
        case 'W': pose.heading = 'S'; break;
        default: break;
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
