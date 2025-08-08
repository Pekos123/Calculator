add_executable(calculator 
    main.cpp 
    Button.cpp
)
target_include_directories(calculator PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(calculator SDL3)
