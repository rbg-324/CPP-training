#pragma once
#include <cstdint>
#include <string>

namespace adas {
struct Pose {
    std::int32_t x;
    std::int32_t y;
    char heading;
};

class Executor {
public:
    static Executor* NewExecutor(const Pose& initialPose = {0, 0, 'E'}) noexcept;
    Executor() = default;
    virtual ~Executor() = default;
    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;
    virtual void Execute(const std::string& commands) = 0;
    virtual Pose Query() const noexcept = 0;
};
}  // namespace adas
