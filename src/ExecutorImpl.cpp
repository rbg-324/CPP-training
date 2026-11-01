#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <memory>
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
    std::unordered_map<char, std::unique_ptr<ICommand>> commandMap;
    commandMap.emplace('M', std::make_unique<MoveCommand>());
    commandMap.emplace('L', std::make_unique<TurnLeftCommand>());
    commandMap.emplace('R', std::make_unique<TurnRightCommand>());
    commandMap.emplace('F', std::make_unique<FastCommand>());

    for (const char command : commands) {
        const auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            it->second->DoOperate(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept { return poseHandler.Query(); }
}  // namespace adas
