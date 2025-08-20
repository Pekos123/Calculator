#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H
#pragma once

#include <string>

#define CNULL '\0'

enum CalculatorState
{
    EnteringFirstNumber,
    OperationSelection,
    EnteringSecondNumber,
    ShowingResults,
    ThrowingError,
};

class CalculatorEngine
{
private:
    CalculatorState currentState = EnteringFirstNumber;
    std::string firstNum = "0";
    std::string secNum = "0";
    std::string results = "0"; // store results
    char operation = CNULL;

    bool ValidateState();
    bool IsInErrorState() const;
    bool HandleError(const std::string& errorMessage); 

    void Clear();
public:
    std::string GetEquationString() const;
    std::string GetDisplayValue() const;

    void SetOperation(const char operation);
    void EnterNumber(const char charNum);
    void ClearEquation(); 
    void ChangeNumberSign();
    void SumUpEquation();
    void EnterDecimalPoint();
};

#endif
