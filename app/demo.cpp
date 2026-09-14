#include "boogie_dodge_lite/BoogieDodgeApp.h"

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

class DemoSource final : public BoogieDodgeLite::FrameSource {
public:
    bool NextFrame(BoogieDodgeLite::Frame& frame, float& moveBudgetTiles,
                   BoogieDodgeLite::Goal& goal) override
    {
        if (tick >= 60) return false;

        map = {};
        map.tickValid = true;
        AddSyntheticProjectile(map, -1.5f + 0.05f * static_cast<float>(tick));
        frame = {};
        frame.player = player;
        frame.intentDir = {1.f, 0.f};
        frame.stepTiles = 1.f;
        frame.speed = 0.005f;
        frame.tickId = static_cast<uint32_t>(tick + 1);
        frame.map = &map;
        moveBudgetTiles = frame.stepTiles;
        goal = {};
        ++tick;
        return true;
    }

private:
    int tick = 0;
    UDodge::Vec2 player{};
    UDodge::DangerMap map{};
};

class DemoSink final : public BoogieDodgeLite::MovementSink {
public:
    void Apply(const BoogieDodgeLite::Decision& decision) override
    {
        std::printf("frame=%02d decision=%s target=(%.3f, %.3f) move=%s clearance=%.3f\\n",
            frame++, KindName(decision.kind), decision.target.x, decision.target.y,
            decision.shouldMove ? "yes" : "no", decision.clearance);
    }

private:
    int frame = 1;
};

} // namespace

int main()
{
    std::printf("BoogieDodgeLite demo\\n");
    DemoSource source;
    DemoSink sink;
    BoogieDodgeLite::Application app;
    return app.Run(source, sink, 60) == 60 ? 0 : 1;
}
