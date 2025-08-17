# CALCULATOR CREATED IN C++ USING RENDER LIB SDL3

## About
Its simple 600x950 Calculator created in C++ 17 using SDL3 lib used for renderering.<p>**PROJECT DONT HAVE COMPLETED MATH LOGIC**

## How to build project?
**Linux Ubuntu/Debian:**
1. First Clone git repo
```bash
git clone https://github.com/Pekos123/Calculator.git
cd Calculator
```
2. Make build direcotry and run cmake
```bash
mkdir build
cd build
cmake ../CMakeLists.txt
make
```

## Project Structure
```
Calculator/          
├── src/                   # Source files          
│   ├── main.cpp           # Application entry point          
│   ├── CalculatorApp.cpp  # Main application class   
│   ├── CalculatorEngine.cpp  # All math logic 
│   ├── Button.cpp         # Button UI component          
│   ├── Text.cpp           # Text rendering component          
│   ├── Frame.cpp          # UI layout container          
│   ├── Event.cpp          # Events          
│   ├── GUIElement.cpp     # Base UI element class          
│   └── CMakeLists.txt     # CMake build configuration          
├── include/               # Header files          
│   ├── CalculatorApp.h
│   ├── CalculatorEngine.h         
│   ├── Button.h         
│   ├── Text.h           
│   ├── Frame.h          
│   ├── Event.h          
│   ├── GUIElement.h     
│   └── CMakeLists.txt     # CMake build configuratio
├── tests/                # Unit test using Gtest lib
├── lib/                  
├── font.otf               # Application font
├── CMakeLists.txt         # CMake build configuration
├── .gitignore             # Git ignore rules
└── README.md              # This file
```
## Architecture
*The calculator follows a modular architecture:*

- **CalculatorApp**: Main application class handling initialization and game loop
- **CalculatorEngine**: Handle all calculator logic
- **GUIElement**: Base class for all UI components  
- **Button**: Interactive button component with text and click event handling
- **Text**: Text rendering component using SDL3_ttf
- **Frame**: Layout container for organizing UI elements

### Dependencies

- SDL3
- SDL3_ttf
- GTest
- CMake (build system)
- **C++17** compatible compiler

## Photos
<img width="106" height="320" alt="image" src="https://github.com/user-attachments/assets/77d265f6-353f-4c54-a174-a37460baf150" />
<img width="106" height="320" alt="image" src="https://github.com/user-attachments/assets/edaa05d3-3f1d-4db1-b8d6-18f9a57c087c" />






