cmake_minimum_required(VERSION 3.0.0)
project(sudokuApp VERSION 0.1.0)

include(CTest)
enable_testing()

## Adds directory link
add_subdirectory(src)


## Creates executable, links directories to executable
add_executable(sudokuApp main.cpp)
target_link_libraries(sudokuApp PRIVATE sudoku)
target_include_directories(sudokuApp PRIVATE include)
set_target_properties(sudokuApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
