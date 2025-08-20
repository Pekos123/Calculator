#include <gtest/gtest.h>
#include <string>

#include "../include/CalculatorEngine.h"

CalculatorEngine engine;

void EnterCalculatorNums(const float firstNum, const float secNum, const char operation)
{
    std::string firstNumString = std::to_string(firstNum);
    std::string secNumString = std::to_string(secNum);
   
    for(const char num : firstNumString)
    {
        if(num == '.') engine.EnterDecimalPoint();
        else engine.EnterNumber(num);
    }
    engine.SetOperation(operation);
      
    for(const char num : secNumString)
    {
        if(num == '.') engine.EnterDecimalPoint();
        else engine.EnterNumber(num);
    }

    engine.SumUpEquation();
}

TEST(CalculatorLogic, Substraction)
{
    EnterCalculatorNums(15, 5, '-');
    EXPECT_EQ("10", engine.GetDisplayValue()); // 15 - 5 = 10;
}
TEST(CalculatorLogic, Addition)
{
    EnterCalculatorNums(15, 5, '+');
    EXPECT_EQ("20", engine.GetDisplayValue()); // 15 + 5 = 20;
}
TEST(CalculatorLogic, Multiplication)
{
    EnterCalculatorNums(15, 5, 'x');
    EXPECT_EQ("75", engine.GetDisplayValue()); // 15 * 5 = 75;
}
TEST(CalculatorLogic, Deviding)
{
    EnterCalculatorNums(15, 5, ':');
    EXPECT_EQ("3", engine.GetDisplayValue()); // 15 / 5 = 3;
}
TEST(CalculatorLogic, Working_On_Decimal_Points)
{
    EnterCalculatorNums(1.5f, 5.0f, ':');
    EXPECT_EQ("0.3", engine.GetDisplayValue()); // 1.5 / 5 = 3;
}
TEST(CalculatorLogic, Handle_Math_Errors)
{
    EnterCalculatorNums(1, 0, ':');
    EXPECT_EQ("DIVISION BY ZERO", engine.GetDisplayValue()); // 15 - 5 = 10;
}

