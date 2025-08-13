add_executable(calculator 
    main.cpp 
    Button.cpp
    Frame.cpp
    GUIElement.cpp
    Text.cpp
    CalculatorApp.cpp
)

target_include_directories(calculator PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/SDL3/local/include 
)

target_link_libraries(calculator
    ${CMAKE_SOURCE_DIR}/lib/SDL3/local/lib/libSDL3.so
    ${CMAKE_SOURCE_DIR}/lib/SDL3/local/lib/libSDL3_ttf.so
)

set_target_properties(calculator PROPERTIES
    INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib/SDL3/local/lib"
)
