#include "boogie_dodge_lite/BoogieDodgeLite.h"

#include <cmath>
#include <cstdio>

namespace {

void AddSyntheticProjectile(UDodge::DangerMap& map, float x)
{
    UDodge::LaneThreat& lane = map.lanes[map.laneCount++];
    lane.hitHalf = 0.35f;
    lane.pointCount = 3;
    lane.instantCount = 3;
    lane.pointTimesMs[0] = 0.f;
    lane.pointTimesMs[1] = 200.f;
    lane.pointTimesMs[2] = 400.f;
    lane.points[0] = {x, -3.f};
    lane.points[1] = {x, 0.f};
    lane.points[2] = {x, 3.f};
}

const char* KindName(UDodge::Solver::SolveKind kind)
{
    switch (kind) {
    case UDodge::Solver::SolveKind::Hold: return "hold";
    case UDodge::Solver::SolveKind::Safe: return "safe";
    case UDodge::Solver::SolveKind::Fallback: return "fallback";
    case UDodge::Solver::SolveKind::Surrounded: return "surrounded";
    }
    return "unknown";
}

} // namespace

int main()
{
    UDodge::DangerMap map{};
    map.tickValid = true;
    AddSyntheticProjectile(map, 0.f);

    BoogieDodgeLite::Frame frame{};
    frame.player = {0.f, 0.f};
    frame.intentDir = {1.f, 0.f};
    frame.stepTiles = 1.f;
    frame.speed = 0.005f;
    frame.tickId = 1;
    frame.map = &map;

    BoogieDodgeLite::Controller controller;
    const auto decision = controller.Tick(frame, frame.stepTiles);

    std::printf("BoogieDodgeLite demo\\n");
    std::printf("decision=%s target=(%.3f, %.3f) move=%s clearance=%.3f\\n",
        KindName(decision.kind), decision.target.x, decision.target.y,
        decision.shouldMove ? "yes" : "no", decision.clearance);
    return std::isfinite(decision.target.x) && std::isfinite(decision.target.y) ? 0 : 1;
}
