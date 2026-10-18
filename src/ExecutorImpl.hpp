#pragma once

#include "Executor.hpp"

namespace adas {
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& initialPose) noexcept;
    ~ExecutorImpl() noexcept override = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    Pose pose;
};
}  // namespace adas
