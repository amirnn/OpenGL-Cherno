# OpenGL Using C++

## How to build

To build run the command below
```shell
# For Debug
conan install . --build=missing --profile=profiles/brew-llvm -s build_type=Debug
# or for Release
conan install . --build=missing --profile=profiles/brew-llvm -s build_type=Release
```

## In case of using clangd

Make sure in your cmake file you have included:
```cmake
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```
and then in link the compile_commands.json file into the root directory.

```shell
# Issue the command in the root directory
ln -s ./build/Release/compile_commands.json

```

## Clang Tidy
TODO