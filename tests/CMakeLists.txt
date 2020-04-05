cmake_minimum_required(VERSION 3.12)

project(SudokuZooTest
        VERSION 0.1
        DESCRIPTION "SudokuZoo test cases"
        LANGUAGES C CXX
)

if(POLICY CMP0076)
  cmake_policy(SET CMP0076 NEW)
endif()

enable_testing()

# enable c++17 globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Catch2 REQUIRED)

# list and compile executable
list(APPEND target_tests "SudokuZooTest")
list(APPEND target_tests "DancingListTest")

if ("SudokuZooTest" IN_LIST target_tests)
    add_executable(SudokuZooTest)
    target_sources(SudokuZooTest PUBLIC SudokuZooTest.cpp)
    target_link_libraries(SudokuZooTest PUBLIC Catch2::Catch2 SudokuZoo::SudokuZoo)
    add_test("SudokuZooTest" SudokuZooTest)
endif()

if ("DancingListTest" IN_LIST target_tests)
    add_executable(DancingListTest)
    target_sources(DancingListTest PUBLIC DancingListTest.cpp)
    target_link_libraries(DancingListTest PUBLIC Catch2::Catch2 SudokuZoo::SudokuZoo)
    add_test("DancingListTest" DancingListTest)
endif()
