#include <fmt/core.h>

#include "my_math.h"

int main() {
    fmt::print("Hello, world!\n");
    fmt::print("{} + {} is {}\n", 2, 3, add(2, 3));
}
