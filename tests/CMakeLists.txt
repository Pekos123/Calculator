enable_testing()

add_executable(calculator_tests
    ../src/Button.cpp
    ../src/Frame.cpp
    ../src/GUIElement.cpp
    ../src/Text.cpp
    ../src/CalculatorApp.cpp
    ../src/CalculatorEngine.cpp
    ../src/Event.cpp
    button_test.cpp
    font_test.cpp
    frame_test.cpp
)

# Link against GTest and SDL3
target_link_libraries(calculator_tests
    gtest
    gtest_main
    SDL3
    ${CMAKE_SOURCE_DIR}/lib/SDL3/local/lib/libSDL3_ttf.so
)

target_include_directories(calculator_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/SDL3/local/include    
)
set_target_properties(calculator_tests PROPERTIES
    INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib/SDL3/local/lib"
    BUILD_WITH_INSTALL_RPATH TRUE
)

add_test(NAME CalculatorUnitTests COMMAND calculator_tests)
