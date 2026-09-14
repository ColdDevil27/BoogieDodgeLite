cmake_minimum_required(VERSION 3.20)

project(BoogieDodgeLite VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(boogie_dodge_lite STATIC
    src/features/movement/udodge/UDodgeCore.cpp
    src/features/movement/udodge/UDodgePathfinder.cpp
    src/features/movement/udodge/UDodgeSolver.cpp
    src/features/movement/udodge/UDodgeWorker.cpp
    src/features/movement/spacetime/SpacetimeCore.cpp
)

target_include_directories(boogie_dodge_lite
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/features/movement/udodge
        ${CMAKE_CURRENT_SOURCE_DIR}/src/features/movement/spacetime
)

target_compile_features(boogie_dodge_lite PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(boogie_dodge_lite PRIVATE /W4 /permissive-)
else()
    target_compile_options(boogie_dodge_lite PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(boogie_dodge_demo app/demo.cpp)
target_link_libraries(boogie_dodge_demo PRIVATE boogie_dodge_lite)

if(NOT MSVC)
    find_package(Threads REQUIRED)
    target_link_libraries(boogie_dodge_lite PUBLIC Threads::Threads)
endif()

include(GNUInstallDirs)
install(TARGETS boogie_dodge_lite
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
