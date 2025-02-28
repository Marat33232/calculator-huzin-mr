#include <gtest/gtest.h>
extern "C" {
    #include "../src/main.c"
}

TEST(CalculatorTest, BasicAddition) {
    const char* expr = "5 + 3";
    EXPECT_DOUBLE_EQ(evaluate_expression(expr, 0), 8);
}

TEST(CalculatorTest, DivisionByZero) {
    const char* expr = "5 / 0";
    EXPECT_DEATH(evaluate_expression(expr, 0), "Деление на ноль");
}

TEST(CalculatorTest, FloatMode) {
    const char* expr = "5 / 3";
    EXPECT_DOUBLE_EQ(evaluate_expression(expr, 1), 1.6666666667);
}
