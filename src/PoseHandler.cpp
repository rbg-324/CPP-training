#include "PoseHandler.hpp"
#include <algorithm>
#include <array>

namespace adas {
namespace {
struct Step { int x; int y; };
constexpr std::array<char, 4> headings{{'N', 'E', 'S', 'W'}};
constexpr std::array<Step, 4> steps{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

std::size_t HeadingIndex(char heading) noexcept
{
    const auto it = std::find(headings.begin(), headings.end(), heading);
    return static_cast<std::size_t>(it - headings.begin());
}
}  // namespace

PoseHandler::PoseHandler(const Pose& initialPose) noexcept : pose(initialPose) {}

void PoseHandler::Move() noexcept
{
    const auto index = HeadingIndex(pose.heading);
    if (index < steps.size()) {
        pose.x += steps[index].x;
        pose.y += steps[index].y;
    }
}

void PoseHandler::Turn(std::size_t offset) noexcept
{
    const auto index = HeadingIndex(pose.heading);
    if (index < headings.size()) {
        pose.heading = headings[(index + offset) % headings.size()];
    }
}

void PoseHandler::TurnLeft() noexcept { Turn(3); }
void PoseHandler::TurnRight() noexcept { Turn(1); }
void PoseHandler::Fast() noexcept { fast = !fast; }
bool PoseHandler::IsFast() const noexcept { return fast; }
Pose PoseHandler::Query() const noexcept { return pose; }
}  // namespace adas
