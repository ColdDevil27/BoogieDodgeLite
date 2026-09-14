#pragma once

#include "UDodgeSolver.h"

namespace BoogieDodgeLite {

using Frame = UDodge::MapInput;
using Goal = UDodge::Solver::Goal;
using Decision = UDodge::Solver::SolveResult;

// Host-side controller. The host owns sensing, collision callbacks, and
// movement actuation; this class owns only solver state between frames.
class Controller {
public:
    Decision Tick(const Frame& frame, float moveBudgetTiles, const Goal& goal = {})
    {
        Decision decision{};
        UDodge::Path::PlanResult noRoute{};
        UDodge::Solver::Solve(frame, moveBudgetTiles, goal, noRoute, state, decision);
        return decision;
    }

    void Reset()
    {
        state.Reset();
    }

private:
    UDodge::CoreState state{};
};

} // namespace BoogieDodgeLite
