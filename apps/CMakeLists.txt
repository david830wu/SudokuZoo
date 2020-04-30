cmake_minimum_required(VERSION 3.12)

project(SudokuZooApps
        VERSION 0.1
        DESCRIPTION "SudokuZoo apps"
        LANGUAGES C CXX
)

if(POLICY CMP0076)
  cmake_policy(SET CMP0076 NEW)
endif()

# enable c++17 globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# list and compile executable
#list(APPEND target_apps "main")
list(APPEND target_apps "Solver")

if ("main" IN_LIST target_apps)
    add_executable(main)
    target_sources(
        main
    PUBLIC
        main.cpp
    )
    target_include_directories(
        main
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(
        main
    PUBLIC
        Boost::boost
        Threads::Threads
        SudokuZoo::SudokuZoo
    )
endif()

if ("Solver" IN_LIST target_apps)
    set(target_name "Solver")
    add_executable(${target_name})
    target_sources(
        ${target_name}
    PUBLIC
        Solver/${target_name}.cpp
    )
    target_include_directories(
        ${target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/apps/Solver>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(
        ${target_name}
    PUBLIC
        SudokuZoo::SudokuZoo
    )
endif()