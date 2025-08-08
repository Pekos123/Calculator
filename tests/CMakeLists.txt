enable_testing()

add_executable(calculator_tests
    test.cpp
    ../src/Button.cpp
)

# Link against GTest and SDL3
target_link_libraries(calculator_tests
    gtest
    gtest_main
    SDL3
)

target_include_directories(calculator_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
add_test(NAME CalculatorUnitTests COMMAND calculator_tests)
