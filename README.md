# Helo Engine

Helo Engine is a 2D game engine intended platformers and top-down RPGs.

- [Overview](#overview)
- [Examples](#examples)
- [Building](#building)


# Overview
## Scene Management
Scenes are managed using states. Each scene is managed by a class that inherits from `he::GameState`. The mandatory overrides are `ProcessInput(sf::Event)`, `Update(float)`, `Render(float)`, `Init()`.

The functions `ProcessInput(sf::Event)`, `Update(float)`, `Render(float)` are called every game tick.

The function `FixedUpdate(float)` updates with a fixed timestep and should be used for physics-related processes.

### State Stack
States are managed via a state stack, similar to a call stack. The active state is the topmost state in the stack. Usually, only one state should be in the stack, other than in the case of UI/menuing states or a pause state.

## Window
The window will resize its view automatically because of its events being handled in `he::Game`.


# Examples
WIP


# Building
## Requirements
* [CMake 3.0.0 or newer](https://cmake.org/)
* Any C++17 compiler
* An internet connection (to pull from git)

## Prerequisites
Download and install CMake, and a C++17 Compiler.
## CMake
The following options are available to be set:
| Options | Description |
| - | - |
| SFML_STATIC_LIBRARIES=FALSE | (Optional) Statically link SFML libraries with the executable? |

Example for CMake CLI targeting Unix Makefiles:
```
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=../install -DSWI_PROLOG_LIBRARY=lib/swipl/bin -DSWI_PROLOG_INCLUDE_DIR=lib/swipl/include -DSWI_PROLOG_BIN_DIR=lib/swipl/bin
make
```

# Licenses
* This project is under the [MIT license](https://opensource.org/licenses/MIT)
* [SFML](https://github.com/SFML/SFML) is under the [zlib/libpng license](https://opensource.org/licenses/Zlib)
* [Dear ImGui](https://github.com/ocornut/imgui) is under the [MIT license](https://opensource.org/licenses/MIT)
* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) is under the [MIT license](https://opensource.org/licenses/MIT)
* [debug_assert](https://github.com/foonathan/debug_assert) is under the [zlib/libpng license](https://opensource.org/licenses/Zlib)
* [spdlog](https://github.com/gabime/spdlog) is under the [MIT license](https://opensource.org/licenses/MIT)