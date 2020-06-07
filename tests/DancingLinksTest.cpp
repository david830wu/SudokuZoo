/* DancingLinksTest.cpp
* 
* Author: Wentao and Jiejun
* Created: 20200404 
* Version: 0.1
*/

#include "DancingLinks.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("DancingLinks", "[DancingLinks]") {
    SECTION("AddRow") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(7);

        problem.add_row_by_binary( {0, 0, 1, 0, 1, 1, 0} );

        problem.dump(std::cout); 

    }
    SECTION("CoverColumn") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(7);
        problem.add_row_by_binary({0, 0, 1, 0, 1, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 1})
               .add_row_by_binary({0, 1, 1, 0, 0, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 0})
               .add_row_by_binary({0, 1, 0, 0, 0, 0, 1})
               .add_row_by_binary({0, 0, 0, 1, 1, 0, 1});

        problem.cover_column(0);

        DancingLinks expected(6);
        expected.add_row_by_binary({0, 1, 0, 1, 1, 0})
                .add_row_by_binary({1, 1, 0, 0, 1, 0})
                .add_row_by_binary({1, 0, 0, 0, 0, 1})
                .add_row_by_binary({0, 0, 1, 1, 0, 1});
        REQUIRE(problem == expected);
    }
    SECTION("UncoverColumn") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(7);
        problem.add_row_by_binary({0, 0, 1, 0, 1, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 1})
               .add_row_by_binary({0, 1, 1, 0, 0, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 0})
               .add_row_by_binary({0, 1, 0, 0, 0, 0, 1})
               .add_row_by_binary({0, 0, 0, 1, 1, 0, 1});
        problem.cover_column(0);
        problem.uncover_column(0);
        DancingLinks expected(7);
        expected.add_row_by_binary({0, 0, 1, 0, 1, 1, 0})
                .add_row_by_binary({1, 0, 0, 1, 0, 0, 1})
                .add_row_by_binary({0, 1, 1, 0, 0, 1, 0})
                .add_row_by_binary({1, 0, 0, 1, 0, 0, 0})
                .add_row_by_binary({0, 1, 0, 0, 0, 0, 1})
                .add_row_by_binary({0, 0, 0, 1, 1, 0, 1});

        REQUIRE(problem == expected);

    }
    SECTION("FindMinimumOnesColumn1") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(7);
        problem.add_row_by_binary({0, 0, 1, 0, 1, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 1})
               .add_row_by_binary({0, 1, 1, 0, 0, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 0})
               .add_row_by_binary({0, 1, 0, 0, 0, 0, 1})
               .add_row_by_binary({0, 0, 0, 1, 1, 0, 1});
        REQUIRE(problem.find_min_ones_col() == 1);

    }
    SECTION("FindMinimumOnesColumn2") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(7);
        problem.add_row_by_binary({0, 0, 1, 0, 1, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 1})
               .add_row_by_binary({0, 1, 1, 0, 0, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 0})
               .add_row_by_binary({0, 1, 0, 0, 0, 0, 1})
               .add_row_by_binary({0, 0, 0, 1, 0, 0, 1});
        REQUIRE(problem.find_min_ones_col() == 5);
    }
    SECTION("Search") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(7);
        problem.add_row_by_binary({0, 0, 1, 0, 1, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 1})
               .add_row_by_binary({0, 1, 1, 0, 0, 1, 0})
               .add_row_by_binary({1, 0, 0, 1, 0, 0, 0})
               .add_row_by_binary({0, 1, 0, 0, 0, 0, 1})
               .add_row_by_binary({0, 0, 0, 1, 1, 0, 1});
        problem.solve();
    }
    SECTION("MultiSolution Search") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(3);
        problem.add_row_by_binary({1, 0, 1}, "101")   // row 1
               .add_row_by_binary({1, 1, 0}, "110")   // row 2
               .add_row_by_binary({0, 1, 0}, "010")   // row 3
               .add_row_by_binary({0, 0, 1}, "001");  // row 4
        problem.solve();
        problem.print_row_solution();
    }
    SECTION("InitCondSearch") {
        using SudokuZoo::ExactCoverProblem::Details::DancingLinks;

        DancingLinks problem(3);
        problem.add_row_by_binary({1, 0, 1}, "101")   // row 1
               .add_row_by_binary({1, 1, 0}, "110")   // row 2
               .add_row_by_binary({0, 1, 0}, "010")   // row 3
               .add_row_by_binary({0, 0, 1}, "001");  // row 4
        problem.add_init_condition(1);
        problem.solve();
        problem.print_row_solution();
    }

}

TEST_CASE("ExactCoverProblem", "[ExactCoverProblem]") {
    SECTION("Trivial") {
        SudokuZoo::ExactCoverProblem::Problem problem{
            {}
        };
        auto solution = problem.solve();
        REQUIRE(solution.size() == 0);
        REQUIRE(solution == SudokuZoo::ExactCoverProblem::SolutionSet{});
    }
    
    SECTION("Simple") {
        SudokuZoo::ExactCoverProblem::Problem problem{
            {1, 0, 1}, // row 0
            {1, 1, 0}, // row 1
            {0, 1, 0}  // row 2
        };
        auto solution = problem.solve();
        REQUIRE(solution.size() == 1);
        REQUIRE(solution == SudokuZoo::ExactCoverProblem::SolutionSet{
            {0, 2}
        });
    }

    SECTION("Knuth") {
        SudokuZoo::ExactCoverProblem::Problem problem{
            {0, 0, 1, 0, 1, 1, 0},
            {1, 0, 0, 1, 0, 0, 1},
            {0, 1, 1, 0, 0, 1, 0},
            {1, 0, 0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 1},
            {0, 0, 0, 1, 1, 0, 1}
        };
        auto solution = problem.solve();
        REQUIRE(solution.size() == 1);
        REQUIRE(solution == SudokuZoo::ExactCoverProblem::SolutionSet{
            {0, 3, 4}
        });
    }
        
    SECTION("Multi-Solution") {
        SudokuZoo::ExactCoverProblem::Problem problem{
            {1, 0, 1}, // row 0
            {1, 1, 0}, // row 1
            {0, 1, 0}, // row 2
            {0, 0, 1}  // row 3
        };
        auto solution = problem.solve();
        REQUIRE(solution.size() == 2);
        REQUIRE(solution == SudokuZoo::ExactCoverProblem::SolutionSet{
            {0, 2},
            {1, 3}
        });
    }
}
