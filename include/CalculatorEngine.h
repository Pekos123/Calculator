#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H
#pragma once

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
    CalculatorState currentState;
    char operation;

    void ErrorHandling();
public:
    
};

#endif
