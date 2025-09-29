# yumeami

A Yume Nikki inspired game where you can create your own collaborative dreamspace.

> [!note]
> This project is still in very early stages, and is not useable yet.

## Building

Building has been tested on Fedora with:
- `gcc` targeting Linux x86_64
- provided `mingw-w64` (UCRT) toolchain targeting Windows x86_64, with statically linked libraries.

This project can likely be easily built for and on other platforms, but these are untested.

All external libraries are automatically fetched and built by CMake, or provided in the `external/` directory:

- [EnTT](https://github.com/skypjack/entt) v3.15.0
- [Raylib](https://github.com/raysan5/raylib) v5.5
- [spdlog](https://github.com/gabime/spdlog) v1.15.3
- [reflect-cpp](https://github.com/getml/reflect-cpp) v0.20.0
