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

        default: break;
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
