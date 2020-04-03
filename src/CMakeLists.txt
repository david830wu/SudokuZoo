cmake_minimum_required(VERSION 3.12)

project(SudokuZooLib
        VERSION 0.1
        DESCRIPTION "SudokuZoo"
        LANGUAGES C CXX
)

if(POLICY CMP0076)
  cmake_policy(SET CMP0076 NEW)
endif()

# enable c++17 globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SudokuZoo)
target_sources(
    SudokuZoo
PRIVATE
    SudokuZoo.cpp
)
target_include_directories(
    SudokuZoo
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(
    SudokuZoo
PUBLIC
    Threads::Threads
    Boost::boost
)
add_library(SudokuZoo::SudokuZoo ALIAS SudokuZoo)
