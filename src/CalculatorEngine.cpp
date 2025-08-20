#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "../include/CalculatorApp.h"
#include "../include/CalculatorEngine.h"

std::string FloatToString(float value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(Config::MAX_PRECISION);
    oss << value;
    
    std::string result = oss.str();
    
    // Remove trailing zeros and decimal point if necessary
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    if (!result.empty() && result.back() == '.') {
        result.pop_back();
    }
    
    return result;
}

bool StringToFloat(const std::string& str, float& result) {
    try {
        result = std::stof(str);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool CalculatorEngine::IsInErrorState() const {
    return currentState == CalculatorState::ThrowingError;
}

bool CalculatorEngine::HandleError(const std::string& errorMessage) {
    currentState = CalculatorState::ThrowingError;
    Clear();
    results = errorMessage;
    return true;
}

bool CalculatorEngine::ValidateState() {
    switch (currentState) {
        case CalculatorState::EnteringFirstNumber:
            break;
            
        case CalculatorState::OperationSelection:
            if (operation != CNULL) {
                return HandleError("OPERATION ERROR");
            }
            break;
            
        case CalculatorState::EnteringSecondNumber:
            break;
            
        case CalculatorState::ShowingResults:
            if (operation == ':' && secNum == "0") {
                return HandleError("DIVISION BY ZERO");
            }
            break;
            
        case CalculatorState::ThrowingError:
            return true;
    }
    return false;
}

void CalculatorEngine::Clear() {
    firstNum = "0";
    secNum = "0";
    operation = CNULL;
}

void CalculatorEngine::ClearEquation() {
    Clear();
    results = "0";
    currentState = CalculatorState::EnteringFirstNumber;
}

std::string CalculatorEngine::GetDisplayValue() const {
    if (IsInErrorState()) {
        return results;
    }
    
    switch (currentState) {
        case CalculatorState::EnteringFirstNumber:
            return firstNum;
        case CalculatorState::OperationSelection:
            return firstNum;
        case CalculatorState::EnteringSecondNumber:
            return secNum.empty() ? "0" : secNum;
        case CalculatorState::ShowingResults:
            return results;
        default:
            return "0";
    }
}

std::string CalculatorEngine::GetEquationString() const {
    if (IsInErrorState()) {
        return results;
    }
    
    std::string equation = firstNum;
    
    if (operation != CNULL) {
        equation += " " + std::string(1, operation) + " ";
        if (!secNum.empty() && secNum != "0") {
            equation += secNum;
        }
    }
    
    if (currentState == CalculatorState::ShowingResults) {
        equation += " = " + results;
    }
    
    return equation;
}

void CalculatorEngine::SetOperation(char operation) {
    if (IsInErrorState()) {
        return;
    }
    
    if (currentState == CalculatorState::ShowingResults) {
        firstNum = results;
        secNum = "0";
    }
    
    if (operation != '+' && operation!= '-' && operation != 'x' && operation != ':') {
        HandleError("INVALID OPERATION");
        return;
    }
    
    this->operation = operation;
    currentState = CalculatorState::EnteringSecondNumber;
}

void CalculatorEngine::EnterNumber(char digit) {
    if (IsInErrorState())
        ClearEquation();

    if (digit < '0' || digit > '9') {
        HandleError("INVALID INPUT");
        return;
    }
    
    switch (currentState) {
        case CalculatorState::EnteringFirstNumber:
            if (firstNum == "0") {
                firstNum = digit;
            } else {
                firstNum += digit;
            }
            break;
            
        case CalculatorState::OperationSelection:
            secNum = digit;
            currentState = CalculatorState::EnteringSecondNumber;
            break;
            
        case CalculatorState::EnteringSecondNumber:
            if (secNum == "0") {
                secNum = digit;
            } else {
                secNum += digit;
            }
            break;
            
        case CalculatorState::ShowingResults:
            ClearEquation();
            firstNum = digit;
            break;
    }
}

void CalculatorEngine::EnterDecimalPoint() {
    if (IsInErrorState()) {
        return;
    }
    
    switch (currentState) {
        case CalculatorState::EnteringFirstNumber:
            if (firstNum.find('.') == std::string::npos) {
                firstNum += '.';
            }
            break;
            
        case CalculatorState::EnteringSecondNumber:
            if (secNum.find('.') == std::string::npos) {
                secNum += '.';
            }
            break;
    }
}

void CalculatorEngine::ChangeNumberSign() {
    if (IsInErrorState()) {
        return;
    }
    
    switch (currentState) {
        case CalculatorState::EnteringFirstNumber:
            if (firstNum[0] == '-') {
                firstNum.erase(0, 1); // earising '-'
            } else if (firstNum != "0") {
                firstNum.insert(0, "-");
            }
            break;
            
        case CalculatorState::EnteringSecondNumber:
            if (secNum[0] == '-') {
                secNum.erase(0, 1); // earising '-'
            } else if (secNum != "0") {
                secNum.insert(0, "-");
            }
            break;
    }
}

void CalculatorEngine::SumUpEquation() {
    if (IsInErrorState()) {
        return;
    }
    
    if (firstNum.empty() || secNum.empty() || operation == CNULL) {
        HandleError("INCOMPLETE EQUATION");
        return;
    }
    
    float first, second;
    if (!StringToFloat(firstNum, first) || !StringToFloat(secNum, second)) {
        HandleError("INVALID NUMBER");
        return;
    }
    
    float result = 0.0f;
    
    switch (operation) {
        case '+':
            result = first + second;
            break;
        case '-':
            result = first - second;
            break;
        case 'x':
            result = first * second;
            break;
        case ':':
            if (second == 0.0f) {
                HandleError("DIVISION BY ZERO");
                return;
            }
            result = first / second;
            break;
        default:
            HandleError("UNKNOWN OPERATION");
            return;
    }
    
    if (std::isnan(result) || std::isinf(result)) {
        HandleError("MATH ERROR");
        return;
    }
    
    results = FloatToString(result);
    currentState = CalculatorState::ShowingResults;
    
    operation = CNULL;
    secNum = "0";
}
