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

    Pose pose;
};
}  // namespace adas
