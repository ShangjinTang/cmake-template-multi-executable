# MIT License Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#
# External Dependencies

if(NOT USE_CONAN)
  message(FATAL_ERROR "Please enable conan")
endif()

set(CONAN_LIBRARIES)

# ##############################################################################
# common libraries

find_package(Microsoft.GSL QUIET REQUIRED)
list(APPEND CONAN_LIBRARIES Microsoft.GSL::GSL)

find_package(absl QUIET REQUIRED)
list(APPEND CONAN_LIBRARIES absl::flags absl::flags_parse)

find_package(fmt QUIET REQUIRED)
list(APPEND CONAN_LIBRARIES fmt)

find_package(spdlog QUIET REQUIRED)
list(APPEND CONAN_LIBRARIES spdlog::spdlog)

# ##############################################################################
# test libraries

find_package(GTest QUIET REQUIRED)
list(APPEND CONAN_LIBRARIES gtest gtest_main)

find_package(doctest QUIET REQUIRED)
list(APPEND CONAN_LIBRARIES doctest::doctest)

# ##############################################################################
