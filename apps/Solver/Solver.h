/* Solver.h
 * 
 * Author: Wentao and Jiejun
 * Created: 20200404
 * Version: 0.1
*/

#pragma once

#include "SudokuZoo.h"

namespace SudokuZoo { namespace SolverApp {

class Solver {
public:
    const static int k_scale = 9;

    void welcome_msg() {
        std::cout << "Welcome to SodokuZoo solver" << std::endl;
    }

    void say_goodbay() {
        std::cout << "Bye~" << std::endl;
    }

    void print_col_header() {
        std::cout << "Col   ";
        for(int i = 1; i <= k_scale; ++i) {
            std::cout << " " << i;
        }
        std::cout << std::endl;
    }

    void input_sudoku() {
        print_col_header();
        int row = 0;
        while(row < k_scale) {
            if(input_row(row)) {
                ++row;
            }
        }

        if(!sudoku_.is_valid()) {
            std::cerr << "Input problem is invalid, use \"revise\" command to update" << std::endl;
        }
        if(sudoku_.is_solved()) {
            std::cerr << "Wow! You have solved it by yourself, brilliant!" << std::endl;
        }
    }

    void revise_sudoku() {
        int row;
        std::cout << "revise row: ";
        std::cin >> row;
        if(row < 0 || row > k_scale) {
            std::cerr << "Invalid row number" << std::endl;
            return;
        }
        std::string _;
        std::getline(std::cin, _);
        print_col_header();
        input_row(row - 1);
    }

    void solve() {
        std::cout << "Start solving..." << std::endl;
        sudoku_.solve();
    }
    void print_sudoku() {
        std::cout << sudoku_ << std::endl;
    }
private:
    using row_t = std::array<int, k_scale>;

    bool is_row_valid(const row_t& row) {
        bool is_valid = true;
        for(auto& value : row) {
            if((value < 0) || (value > k_scale)) {
                is_valid = false;
            }
        }
        return is_valid;
    }

    bool input_row(int row) {
        row_t filling_row;
        std::cout << "Row " << row + 1 << ": ";
        std::string row_line;
        std::getline(std::cin, row_line);
        std::stringstream ss(row_line);
        for(int i = 0; i < k_scale; ++i) {
            ss >> filling_row[i];
        }
        if(is_row_valid(filling_row)) {
            for(int col = 0; col < k_scale; ++col) {
                sudoku_.set(row, col, filling_row[col]);
            }
            return true;
        } else {
            std::cout << "Invalid row filling, please try again" << std::endl;
            return false;
        }
    }

    bool verify() {

    }

private:
    SudokuZoo::Sudoku sudoku_;

};
    
} /* namespace SolverApp */ }  /* namespace SudokuZoo */

