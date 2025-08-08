cmake_minimum_required(VERSION 3.16)
project(CalculatorWithSDL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# GoogleTest, if you have CMakeLists.txt in googletest
add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/SDL3/local/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/SDL3/local/lib)

add_subdirectory(src)
add_subdirectory(tests)
