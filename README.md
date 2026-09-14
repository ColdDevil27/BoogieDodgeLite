# BoogieDodgeLite

Standalone host-testable auto-dodge planner core.

This repository contains the plain-data danger model, temporal collision checks,
grid pathfinder, timed escape planner, worker handoff, and the small policy
functions shared by the original client integration. It deliberately excludes
IL2CPP hooks, game-memory readers, renderer/UI code, generated game headers,
and client-specific sensor adapters.

## Build and run

BoogieDodgeLite is now available as a small static library plus a console host
demo. The host owns sensing and movement; `BoogieDodgeLite::Controller` owns
the solver state between frames.

```text
cmake -S . -B build
cmake --build build --config Release
build/boogie_dodge_demo
```

On Windows with a Visual Studio generator, run
`build/Release/boogie_dodge_demo.exe` instead.

The demo feeds the production solver a synthetic projectile. Replace that
frame builder with your game's sensor adapter, then apply `Decision::target`
through your movement API after rechecking the host's collision rules.

## Build and test

The regression runner compiles the production math sources directly with a
C++17 compiler and executes seven native suites:

```text
python tests/run_udodge_zone_tests.py
```

The runner uses `CXX` when set, otherwise `c++`. A POSIX-like host needs a
compiler with pthread support. The CMake build supplies the portable timing
shim needed by the extracted planner; Windows builds can use Visual Studio
2022 or another C++17 compiler.

## Integration boundary

Feed the solver through `UDodgeTypes.h` plain-data inputs (`MapInput`,
`DangerMap`, and environment probes), or use the higher-level
`include/boogie_dodge_lite/BoogieDodgeLite.h` controller. Keep live game
capture and movement actuation in the host application. The host must
revalidate every proposed step against its own authoritative occupancy and
collision floors.

## Source provenance

BoogieDodgeLite is extracted from the `internal` auto-dodge implementation of
the original client. The audit and timed-escape design notes are included in
`docs/`.
