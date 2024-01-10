# Modern CMake Template for Multi Executable

This repository aims to represent a template for Modern C++ with multiple executable files.

It's good for C++ demo:

- Every subdirectory is a standalone project.
- No need to add `CMakeLists.txt` for every subdirectory.
- Link useful libraries for every subdirectory without install first.
  - `spdlog`
  - `fmt`
  - `doctest`
  - `gtest`
  - `ms-gsl`

## Important Note

It's not for library use, so every subdirectory must have a `main` entry. If you want to develop a library, see: [CMake Template](https://github.com/ShangjinTang/cmake-template).

1. Do not have dependencies between subdirectories.
2. When you add new project, structure should be as below. Header file should be placed at `inc`, or same directory as source files.
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
3. Use `glob` to automatically search all source files, though it's an anti-pattern in CMake.

## Resources

- CMake:
  - Official: [Getting Started](https://cmake.org/getting-started/)
  - OnLine Book: [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
  - Introduction Video: [CppCon 2017: Mathieu Ropert “Using Modern CMake Patterns to Enforce a Good Modular Design”](https://www.youtube.com/watch?v=eC9-iRN2b04)
- Conan:
  - Official: [conan.io](https://conan.io/)

## Requirements

- a modern C++20 compiler (suggest to use latest `gcc-13`, `clang-17`, `MSVC 2022` or above)
- [`cmake`](https://cmake.org) 3.15+
- [`conan`](https://conan.io) 2.0+
- `cppcheck` (optional)
- `clang-tidy` (optional)
- `clang-format` (optional for code format)

## Features

- CMake-based project management, including dependencies
- Conan support for dependency management in CMake, completely optional
- Code check tools such as `clang-format`, `cppcheck`
- Sanitizers: Address Sanitizer, Leak Sanitizer, Undefined Behaviour Sanitizer, ...
- Support for shared/static libraries, including generation of export information

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
