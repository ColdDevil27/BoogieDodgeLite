#pragma once

#include "BoogieDodgeLite.h"

namespace BoogieDodgeLite {

class FrameSource {
public:
    virtual ~FrameSource() = default;
    virtual bool NextFrame(Frame& frame, float& moveBudgetTiles, Goal& goal) = 0;
};

class MovementSink {
public:
    virtual ~MovementSink() = default;
    virtual void Apply(const Decision& decision) = 0;
};

class Application {
public:
    int Run(FrameSource& source, MovementSink& sink, int maxFrames = 0)
    {
        int frames = 0;
        Frame frame{};
        float moveBudgetTiles = 0.f;
        Goal goal{};
        while ((maxFrames <= 0 || frames < maxFrames) &&
               source.NextFrame(frame, moveBudgetTiles, goal)) {
            sink.Apply(controller.Tick(frame, moveBudgetTiles, goal));
            ++frames;
        }
        return frames;
    }

    void Reset()
    {
        controller.Reset();
    }

private:
    Controller controller{};
};

} // namespace BoogieDodgeLite
