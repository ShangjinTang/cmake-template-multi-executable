#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "fmt/core.h"
#include "gsl/gsl"
#include "spdlog/spdlog.h"

// #define ENABLE_DOCTEST_EXAMPLE
// #define ENABLE_GTEST_EXAMPLE

#ifdef ENABLE_DOCTEST_EXAMPLE
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#ifdef ENABLE_GTEST_EXAMPLE
#include "gtest/gtest.h"
#endif

#ifdef ENABLE_DOCTEST_EXAMPLE
TEST_CASE("Addition") {
    int a = 2;
    int b = 3;
    CHECK(a + b == 5);
}
#endif
#ifdef ENABLE_GTEST_EXAMPLE
// NOLINTNEXTLINE
TEST(Subtraction, Integers) {
    int a = 5;
    int b = 3;
    EXPECT_EQ(a - b, 2);
}
#endif

// ms-gsl
void processString(gsl::not_null<std::string *> strPtr) {
    fmt::print("Length of string '{}': {}\n", *strPtr, strPtr->length());
}

// abseil: ABSL_FLAG(type, name, default, help-text)
// NOLINTNEXTLINE
ABSL_FLAG(std::string, powered_by, "abseil-cpp", "Powered-By Information");

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
#ifdef ENABLE_DOCTEST_EXAMPLE
    doctest::Context context;
    int doctest_res = context.run();
    context.applyCommandLine(argc, argv);
    if (context.shouldExit())
        return doctest_res;
#endif

#ifdef ENABLE_GTEST_EXAMPLE
    ::testing::InitGoogleTest(&argc, argv);
    int gtest_res = RUN_ALL_TESTS();
    if (gtest_res)
        return gtest_res;
#endif

    // spdlog
    spdlog::info("Welcome to spdlog!");

    // fmtlib
    fmt::print("{}, {}!\n", "Hello", "{fmt}");

    // ms-gsl
    std::string str = "ms-gsl";
    processString(&str);

    // abseil
    absl::ParseCommandLine(argc, argv);
    std::cout << "Support parse flags, powered by: " << absl::GetFlag(FLAGS_powered_by) << std::endl;

    return 0;
}
