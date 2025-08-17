#include "../include/CalculatorEngine.h"

void CalculatorEngine::ErrorHandling()
{
    switch(this->currentState)
    {
        case EnteringFirstNumber:
            break;
        case OperationSelection:
            break;
        case EnteringSecondNumber:
            break;
        case ShowingResults:
            break;
    }
}
