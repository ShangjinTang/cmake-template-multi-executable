# MIT License Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#
# Main CMake Project file

# ##############################################################################
# Define Project-Wide Settings
# ##############################################################################
cmake_minimum_required(VERSION 3.15)

# Define the Project Name and Description
project(
  multi-executable
  LANGUAGES CXX
  DESCRIPTION "")

set(AUTHUR "shangjin.tang@gmail.com")
set(PROJECT_NAME "MultiExecutable")

# Set Project version (used for library versioning and for CPack)
set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)
set(CMAKE_PROJECT_VERSION
    ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}
)

# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "Build in source directory is not allowed. Please specify a build directory as below:
    cmake [options] -S . -B build\n")
endif()

# Start building
message(
  STATUS
    "Started CMake for ${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION}...\n")

# Set required C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# Generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
# Set the Relative Path Configurations
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# Define installation folder and the module path (this one required by conan)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# ##############################################################################
# Define CMake Module Imports
# ##############################################################################
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(InstallRequiredSystemLibraries)
include(GenerateExportHeader)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# configurations
include(standard_options)
include(compiler_options)
include(dependencies)

# tools
include(clang_tidy)
include(clang_format)
include(cppcheck)

# ##############################################################################
# Define Targets
# ##############################################################################

function(add_executables_from_subdirectories DIRECTORY)
  file(
    GLOB subdirs
    RELATIVE ${DIRECTORY}
    ${DIRECTORY}/*)

  foreach(subdir ${subdirs})
    if(IS_DIRECTORY ${DIRECTORY}/${subdir} AND NOT ${subdir} MATCHES
                                               "build|cmake|.git|.cache")

      set(target_name ${subdir}) # use directory name as CMake target name
      set(executable_filename a.out) # use `a.out` as target executable filename
      set(include_dir)

      # glob all files
      file(GLOB_RECURSE sources ${DIRECTORY}/${subdir}/*.cpp)

      # define target executable according to options
      add_executable(${target_name} ${sources})

      # try include `inc` if seperate `inc` / `src` directories is used
      if(EXISTS "${DIRECTORY}/${subdir}/inc")
        target_include_directories(${target_name}
                                   PRIVATE "${DIRECTORY}/${subdir}/inc")
      endif()

      # generate executable in source file directory
      set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                      "${DIRECTORY}/${subdir}")
      set_target_properties(${target_name} PROPERTIES OUTPUT_NAME
                                                      "${executable_filename}")

      # set target compile options as defined in the
      # cmake/compiler_options.cmake Module
      target_compile_options(${target_name} PRIVATE ${compiler_options})

      # add compiler definition
      target_compile_definitions(${target_name} PRIVATE ${compiler_definitions})

      # set target link options as defined in the cmake/compiler_options.cmake
      # Module
      target_link_options(${target_name} PRIVATE ${linker_flags})

      # link against libraries
      target_link_libraries(
        ${target_name} PRIVATE doctest::doctest gtest gtest_main
                               Microsoft.GSL::GSL fmt spdlog::spdlog)

      add_custom_command(
        TARGET ${target_name}
        POST_BUILD
        COMMAND ${executable_filename}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}
        COMMENT "Running ${subdir}/${executable_filename}")
    endif()
  endforeach()
endfunction()

add_custom_target(all_subdirs)

add_custom_target(default)

add_dependencies(default all_subdirs)

add_executables_from_subdirectories(${CMAKE_CURRENT_SOURCE_DIR})
