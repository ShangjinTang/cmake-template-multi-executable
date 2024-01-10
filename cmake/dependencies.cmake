# MIT License Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#
# External Dependencies

if(NOT USE_CONAN)
  message(FATAL_ERROR "Please enable conan")
endif()

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(doctest REQUIRED)
find_package(GTest REQUIRED)
find_package(absl REQUIRED)
