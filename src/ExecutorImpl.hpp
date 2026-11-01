#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas {
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& initialPose) noexcept;
    void Execute(const std::string& commands) override;
    Pose Query() const noexcept override;

private:
    PoseHandler poseHandler;
};
}  // namespace adas
