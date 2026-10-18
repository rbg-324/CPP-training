#include "ExecutorImpl.hpp"
#include <new>
#include <string>

namespace adas {
Executor* Executor::NewExecutor(const Pose& initialPose) noexcept
{
    return new (std::nothrow) ExecutorImpl(initialPose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept
{
    (void)initialPose;
}

void ExecutorImpl::Execute(const std::string& commands)
{
    (void)commands;
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
