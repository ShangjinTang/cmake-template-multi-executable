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

      set(build_target "${subdir}")
      set(run_target "run-${subdir}")
      set(executable_filename "a.out")

      # glob all files
      file(GLOB_RECURSE sources ${DIRECTORY}/${subdir}/*.cpp)

      # define target executable according to options
      add_executable(${build_target} ${sources})

      # try include `inc` if seperate `inc` / `src` directories is used
      if(EXISTS "${DIRECTORY}/${subdir}/inc")
        target_include_directories(${build_target}
                                   PRIVATE "${DIRECTORY}/${subdir}/inc")
      endif()

      # generate executable in source file directory
      set_target_properties(${build_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                       "${DIRECTORY}/${subdir}")
      set_target_properties(${build_target} PROPERTIES OUTPUT_NAME
                                                       "${executable_filename}")

      # set target compile options as defined in the
      # cmake/compiler_options.cmake Module
      target_compile_options(${build_target} PRIVATE ${compiler_options})

      # add compiler definition
      target_compile_definitions(${build_target}
                                 PRIVATE ${compiler_definitions})

      # set target link options as defined in the cmake/compiler_options.cmake
      # Module
      target_link_options(${build_target} PRIVATE ${linker_flags})

      # link against libraries
      target_link_libraries(
        ${build_target}
        PRIVATE # ##############################################################
                # abseil
                absl::flags
                absl::flags_parse
                # fmt
                fmt
                # gsl
                Microsoft.GSL::GSL
                # spdlog
                spdlog::spdlog
                # ##############################################################
                # doctest
                doctest::doctest
                # gtest
                gtest
                gtest_main
                # ##############################################################
      )

      add_custom_target(
        ${run_target}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${executable_filename}
        WORKING_DIRECTORY ${DIRECTORY}/${subdir}
        DEPENDS ${build_target}
        COMMENT "Running ${subdir}/${executable_filename}")

    endif()
  endforeach()
endfunction()

add_executables_from_subdirectories(${CMAKE_CURRENT_SOURCE_DIR})
