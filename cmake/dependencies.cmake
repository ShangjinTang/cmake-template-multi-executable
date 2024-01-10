# MIT License Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#
# External Dependencies

if(NOT USE_CONAN)
  message(FATAL_ERROR "Please enable conan")
endif()

# non-test libraries
find_package(Microsoft.GSL QUIET REQUIRED)
find_package(absl QUIET REQUIRED)
find_package(fmt QUIET REQUIRED)
find_package(spdlog QUIET REQUIRED)

# test libraries
find_package(GTest QUIET REQUIRED)
find_package(doctest QUIET REQUIRED)
