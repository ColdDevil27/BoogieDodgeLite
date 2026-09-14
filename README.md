# BoogieDodgeLite

Standalone host-testable auto-dodge planner core.

This repository contains the plain-data danger model, temporal collision checks,
grid pathfinder, timed escape planner, worker handoff, and the small policy
functions shared by the original client integration. It deliberately excludes
IL2CPP hooks, game-memory readers, renderer/UI code, generated game headers,
and client-specific sensor adapters.

## Build and test

The regression runner compiles the production math sources directly with a
C++17 compiler and executes seven native suites:

```text
python tests/run_udodge_zone_tests.py
```

The runner uses `CXX` when set, otherwise `c++`. A POSIX-like host needs a
compiler with pthread support. Windows builds can use any C++17 compiler that
provides the standard library and a compatible `windows.h` replacement or
project PCH shim.

## Integration boundary

Feed the solver through `UDodgeTypes.h` plain-data inputs (`MapInput`,
`DangerMap`, and environment probes). Keep live game capture and movement
actuation in the host application. The host must revalidate every proposed
step against its own authoritative occupancy and collision floors.

## Source provenance

BoogieDodgeLite is extracted from the `internal` auto-dodge implementation of
the original client. The audit and timed-escape design notes are included in
`docs/`.
