#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <memory>
#include <new>

namespace adas {
Executor* Executor::NewExecutor(const Pose& initialPose) noexcept
{
    return new (std::nothrow) ExecutorImpl(initialPose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : poseHandler(initialPose) {}

void ExecutorImpl::Execute(const std::string& commands)
{
    for (const char command : commands) {
        std::unique_ptr<ICommand> handler;
        if (command == 'M') {
            handler = std::make_unique<MoveCommand>();
        } else if (command == 'L') {
            handler = std::make_unique<TurnLeftCommand>();
        } else if (command == 'R') {
            handler = std::make_unique<TurnRightCommand>();
        } else if (command == 'F') {
            handler = std::make_unique<FastCommand>();
        }
        if (handler) {
            handler->DoOperate(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept { return poseHandler.Query(); }
}  // namespace adas
