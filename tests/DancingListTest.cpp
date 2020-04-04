/* DancingListTest.cpp
* 
* Author: Wentao and Jiejun
* Created: 20200404 
* Version: 0.1
*/

#include "SudokuZoo.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("DancingListTest", "[DancingList]") {
    SECTION("Trivial") {
        SudokuZoo::ExactCoverProblem problem{
            {}
        };
        auto solution = problem.sovle();
        REQUIRE(solution.size() == 0);
        REQUIRE(solution == SodukuZoo::solution{});
    }
    
    SECTION("Simple") {
        SudokuZoo::ExactCoverProblem problem{
            {1, 0, 1}, // row 0
            {1, 1, 0}, // row 1
            {0, 1, 0}  // row 2
        };
        auto solution = problem.sovle();
        REQUIRE(solution.size() == 1);
        REQUIRE(solution == SodukuZoo::solution{
            {0, 2}
        });
    }

    SECTION("Knuth") {
        SudokuZoo::ExactCoverProblem problem{
            {0, 0, 1, 0, 1, 1, 0},
            {1, 0, 0, 1, 0, 0, 1},
            {0, 1, 1, 0, 0, 1, 0},
            {1, 0, 0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 1},
            {0, 0, 0, 1, 1, 0, 1}
        };
        auto solution = problem.sovle();
        REQUIRE(solution.size() == 1);
        REQUIRE(solution == SodukuZoo::solution{
            {0, 3, 4}
        });
    }
        
    SECTION("Multi-Solution") {
        SudokuZoo::ExactCoverProblem problem{
            {1, 0, 1}, // row 0
            {1, 1, 0}, // row 1
            {0, 1, 0}, // row 2
            {0, 0, 1}  // row 3
        };
        auto solution = problem.sovle();
        REQUIRE(solution.size() == 2);
        REQUIRE(solution == SodukuZoo::solution{
            {0, 2},
            {1, 3}
        });
    }
}
