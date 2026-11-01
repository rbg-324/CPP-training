#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <functional>
#include <new>
#include <unordered_map>

namespace adas {
Executor* Executor::NewExecutor(const Pose& initialPose) noexcept
{
    return new (std::nothrow) ExecutorImpl(initialPose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : poseHandler(initialPose) {}

void ExecutorImpl::Execute(const std::string& commands)
{
    static const std::unordered_map<char, std::function<void(PoseHandler&)>> commandMap{
        {'M', MoveCommand{}.operate},
        {'L', TurnLeftCommand{}.operate},
        {'R', TurnRightCommand{}.operate},
        {'F', FastCommand{}.operate},
    };

    for (const char command : commands) {
        const auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            it->second(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept { return poseHandler.Query(); }
}  // namespace adas
