#pragma once
#include "Executor.hpp"

namespace adas {
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& initialPose) noexcept;
    void Execute(const std::string& commands) override;
    Pose Query() const noexcept override;
private:
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    class MoveCommand final {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept { executor.Move(); }
    };
    class TurnLeftCommand final {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept { executor.TurnLeft(); }
    };
    class TurnRightCommand final {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept { executor.TurnRight(); }
    };

    Pose pose;
};
}  // namespace adas
