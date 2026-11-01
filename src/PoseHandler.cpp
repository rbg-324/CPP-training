#include "PoseHandler.hpp"

namespace adas {
PoseHandler::PoseHandler(const Pose& initialPose) noexcept : pose(initialPose) {}

void PoseHandler::Move() noexcept
{
    switch (pose.heading) {
    case 'E': ++pose.x; break;
    case 'W': --pose.x; break;
    case 'N': ++pose.y; break;
    case 'S': --pose.y; break;
    default: break;
    }
}

void PoseHandler::TurnLeft() noexcept
{
    switch (pose.heading) {
    case 'E': pose.heading = 'N'; break;
    case 'N': pose.heading = 'W'; break;
    case 'W': pose.heading = 'S'; break;
    case 'S': pose.heading = 'E'; break;
    default: break;
    }
}

void PoseHandler::TurnRight() noexcept
{
    switch (pose.heading) {
    case 'E': pose.heading = 'S'; break;
    case 'S': pose.heading = 'W'; break;
    case 'W': pose.heading = 'N'; break;
    case 'N': pose.heading = 'E'; break;
    default: break;
    }
}

void PoseHandler::Fast() noexcept { fast = !fast; }
bool PoseHandler::IsFast() const noexcept { return fast; }
Pose PoseHandler::Query() const noexcept { return pose; }
}  // namespace adas
