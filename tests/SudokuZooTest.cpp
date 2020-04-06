/* SudokuZooTest.cpp
* 
* Author: Wentao and Jiejun
* Created: 20200404 
* Version: 0.1
*/

#include "SudokuZoo.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("SudokuZooTest", "[SudokuZoo]") {
    SECTION("Validation") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku{
            7, 8, 3, 4, 1, 2, 6, 9, 5,
            9, 2, 5, 7, 6, 3, 8, 1, 4,
            1, 4, 6, 9, 5, 8, 7, 2, 3,
            2, 5, 7, 6, 4, 1, 9, 3, 8,
            4, 9, 8, 2, 3, 7, 1, 5, 6,
            3, 6, 1, 5, 8, 9, 4, 7, 2,
            6, 1, 2, 3, 9, 4, 5, 8, 7,
            8, 7, 4, 1, 2, 5, 3, 6, 9,
            5, 3, 9, 8, 7, 6, 2, 4, 1
        };
        REQUIRE(sudoku.is_valid()     == true);
        REQUIRE(sudoku.is_completed() == true);
        REQUIRE(sudoku.is_solved()    == true);
    }
    SECTION("Validation False1") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku{
            7, 8, 3, 4, 1, 2, 6, 9, 5,
            9, 2, 5, 7, 6, 3, 8, 1, 4,
            1, 4, 6, 9, 5, 8, 7, 2, 3,
            2, 5, 7, 6, 4, 1, 9, 3, 8,
            4, 9, 8, 2, 3, 0, 1, 5, 6,   // 0 here
            3, 6, 1, 5, 8, 9, 4, 7, 2,
            6, 1, 2, 3, 9, 4, 5, 8, 7,
            8, 7, 4, 1, 2, 5, 3, 6, 9,
            5, 3, 9, 8, 7, 6, 2, 4, 1
        };
        REQUIRE(sudoku.is_valid()     == true );
        REQUIRE(sudoku.is_completed() == false);
        REQUIRE(sudoku.is_solved()    == false);
    }
    SECTION("Validation False2") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku{
            7, 8, 3, 4, 1, 2, 6, 8, 5,  // 7, 8, 3, 4, 1, 2, 6, *9*, 5,
            9, 2, 5, 7, 6, 3, 8, 1, 4,
            1, 4, 6, 9, 5, 8, 7, 2, 3,
            2, 5, 7, 6, 4, 1, 9, 3, 8,
            4, 9, 8, 2, 3, 7, 1, 5, 6,
            3, 6, 1, 5, 8, 9, 4, 7, 2,
            6, 1, 2, 3, 9, 4, 5, 8, 7,
            8, 7, 4, 1, 2, 5, 3, 6, 9,
            5, 3, 9, 8, 7, 6, 2, 4, 1
        };
        REQUIRE(sudoku.is_valid()     == false);
        REQUIRE(sudoku.is_completed() == true );
        REQUIRE(sudoku.is_solved()    == false);
    }
    SECTION("Generation") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku;
        sudoku.generate();
        REQUIRE(sudoku.is_valid() == true);
    }
    SECTION("Generation problem") {
        using SudokuZoo::Sudoku;

        double difficulty = 0.5;
        Sudoku sudoku;
        sudoku.generate(difficulty);
        REQUIRE(sudoku.is_valid() == true);
    }
    SECTION("Solver-DancingList") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku{
            7, 8, 3, 4, 1, 2, 6, 9, 5,
            9, 2, 5, 7, 6, 3, 8, 1, 4,
            1, 4, 6, 9, 5, 8, 7, 2, 3,
            2, 5, 7, 6, 4, 1, 9, 3, 8,
            4, 9, 8, 2, 3, 0, 1, 5, 6,   // 0 here, sovle for 7
            3, 6, 1, 5, 8, 9, 4, 7, 2,
            6, 1, 2, 3, 9, 4, 5, 8, 7,
            8, 7, 4, 1, 2, 5, 3, 6, 9,
            5, 3, 9, 8, 7, 6, 2, 4, 1
        };
        REQUIRE(sudoku.is_valid() == true);
        sudoku.solve();
        REQUIRE(sudoku.is_solved() == true);
        std::cout << sudoku << std::endl;
    }
    SECTION("Solver-DancingList Hard") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku{
            7, 8, 0, 0, 0, 0, 0, 0, 5,
            9, 2, 0, 0, 6, 0, 8, 0, 4,
            1, 4, 0, 9, 0, 0, 7, 0, 3,
            2, 0, 7, 0, 4, 1, 0, 0, 8,
            4, 0, 0, 2, 0, 0, 1, 0, 6,   // 0 here, sovle for 7
            3, 0, 0, 5, 0, 0, 0, 7, 2,
            6, 1, 0, 3, 0, 4, 0, 8, 7,
            8, 0, 0, 1, 0, 5, 0, 0, 9,
            5, 3, 0, 8, 0, 6, 0, 0, 1
        };
        REQUIRE(sudoku.is_valid() == true);
        sudoku.solve();
        REQUIRE(sudoku.is_solved() == true);
        std::cout << sudoku << std::endl;
    }
    SECTION("Pretty print") {
        using SudokuZoo::Sudoku;

        Sudoku sudoku {
            7, 8, 3, 4, 1, 2, 6, 9, 5,
            9, 2, 5, 7, 6, 3, 8, 1, 4,
            1, 4, 6, 9, 5, 8, 7, 2, 3,
            2, 5, 7, 6, 4, 1, 9, 3, 8,
            4, 9, 8, 2, 3, 7, 1, 5, 6,
            3, 6, 1, 5, 8, 9, 4, 7, 2,
            6, 1, 2, 3, 9, 4, 5, 8, 7,
            8, 7, 4, 1, 2, 5, 3, 6, 9,
            5, 3, 9, 8, 7, 6, 2, 4, 1
        };
        std::cout << sudoku << std::endl;
    }
}
