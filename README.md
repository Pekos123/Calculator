# CALCULATOR CREATED IN C++ USING RENDER LIB SDL3

## How to build project?
Linux Ubuntu/Debian
```bash
mkdir build
cd build
cmake ../CMakeLists.txt
make
```

## Project Structure
Calculator/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── CalculatorApp.cpp  # Main application class
│   ├── Button.cpp         # Button UI component
│   ├── Text.cpp           # Text rendering component
│   ├── Frame.cpp          # UI layout container
│   ├── Event.cpp          # Events
│   ├── GUIElement.cpp     # Base UI element class
│   └── CMakeLists.txt     # CMake build configuration
├── include/               # Header files
│   ├── CalculatorApp.h
│   ├── Button.h         
│   ├── Text.h           
│   ├── Frame.h          
│   ├── Event.h          
│   ├── GUIElement.h     
│   └── CMakeLists.txt     # CMake build configuration
├── font.otf         # Application font
├── CMakeLists.txt       # CMake build configuration
├── .gitignore          # Git ignore rules
└── README.md           # This file

## Architecture
- *The calculator follows a modular architecture:*

- **CalculatorApp**: Main application class handling initialization and game loop
- **GUIElement**: Base class for all UI components  
- **Button**: Interactive button component with text and click event handling
- **Text**: Text rendering component using SDL3_ttf
- **Frame**: Layout container for organizing UI elements

