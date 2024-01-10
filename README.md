# Modern CMake Template for Multi Executable

This repository is derived from [Modern CMake Template for Libraries](https://github.com/ShangjinTang/cmake-template), aims to represent a template for Modern C++ with multiple executable files.

It's a good template for demos, tutorials, scratchpads, etc.

## Introduction

- Every subdirectory is a standalone project, must have a `main` entry.
  - For example, to add projects `foo` and `bar`, directory tree should be as below:
    ```text
    .
    ├── foo
    │   ├── foo.h
    │   └── foo.cpp
    ├── bar
    │   ├── inc/bar.h
    │   └── src/bar.cpp
    ├── ...
    ├── CMakeLists.txt
    └── README.md
    ```
  - Header file should be placed at `inc`, or same directory as source file.
  - Source files are globbed (though it's an anti-pattern in CMake).
- No need to add `CMakeLists.txt` for every subdirectory.
- Link useful libraries for every subdirectory without install first, including:
  - `spdlog`
  - `fmt`
  - `doctest`
  - `gtest`
  - `ms-gsl`

## Requirements

- a modern C++20 compiler (suggest to use `gcc-13`, `clang-17`, `MSVC 2022` or above)
- [`cmake`](https://cmake.org) 3.15+ (required)
- [`conan`](https://conan.io) 2.0+ (required)
- `cppcheck` (optional)
- `clang-tidy` (optional)
- `clang-format` (optional)

## Features

- CMake-based project management, including dependencies
- Conan support for dependency management in CMake, completely optional
- Code check tools such as `clang-format`, `cppcheck`
- Sanitizers: Address Sanitizer, Leak Sanitizer, Undefined Behaviour Sanitizer, ...

## Repository layout

The repository layout is pretty straightforward, including the CMake files to build the project, a `conanfile` where are declared examples of dependencies, a suppression list for cppcheck and the C++ source code:

```text
-- .clang-format                - the clang-format rules for the C++ project
-- .clang-tidy                  - the clang-tidy rules for the C++ project
-- .gitignore                   - files to be excluded by git
+- `cmake/`                     - CMake modules
  | -- clang_format.cmake       - C++ header/source format, usage: `--target format`
  | -- clang_tidy.cmake         - C++ static check tool
  | -- compiler-options.cmake   - Common compiler options for major platforms/compilers
  | -- cppcheck.cmake           - C++ static check tool
  | -- dependencies.cmake       - Project dependencies
  | -- standard_options.cmake   - Standard options, can be overrided with "-D..."
-- CMakeLists.txt               - the main `CMake` Project configuration file
-- conanfile.txt                - the main `conan` configuration file listing dependencies
-- cppcheck_suppressions.txt    - optional list of suppressions for cppcheck
```

## Available CMake Options

Please see [Standard Options](cmake/standard_options.cmake) to check all available options.

## How to build from command line

The project can be built using conan:

```bash
python3 -m pip install conan
./compile_run_with_conan.sh
```
