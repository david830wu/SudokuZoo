/* SudokuZoo.h
 * 
 * Author: Wentao and Jiejun
 * Created: 20200404
 * Version: 0.1
*/

#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

namespace SudokuZoo {

    class Sudoku {
    public:

        friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
            for(std::size_t row = 0; row < sudoku.problem_scale; ++row) {
                for(std::size_t col = 0; col < sudoku.problem_scale; ++col) {
                    os << sudoku.get(row, col) << "\t";
                }
                os << "\n";
            }
            return os;
        }

        using element_type = int;
        using size_type = int;
        const size_type house_scale = 3;
        const size_type problem_scale = house_scale * house_scale;
        const size_type problem_houres = problem_scale;

        Sudoku()
            : board_(problem_scale * problem_scale, 0)
            , house_table_(problem_scale, std::vector<size_type>(problem_scale, 0))
        {
            init_house();
        }

        Sudoku(std::initializer_list<element_type> li) 
            : board_(li)
            , house_table_(problem_scale, std::vector<size_type>(problem_scale, 0))
        {
            init_house();
        }

        bool is_valid() const {
            bool validity = true;
            for(size_type i = 0; i < problem_scale; ++i) {
                validity &= is_row_valid(i);
                validity &= is_col_valid(i);
            }
            for(size_type i = 0; i < problem_houres; ++i) {
                validity = validity && is_house_valid(i);
            }
            return validity;
        }

        bool is_completed() const {
            bool complete = true;
            for(size_type row = 0; row < problem_scale; ++row) {
                complete &= is_row_completed(row);
            }
            return complete;
        }

        bool is_solved() const {
            return is_completed() && is_valid();
        }

        bool set(size_type row, size_type col, element_type value) {
            board_[to_id(row, col)] = value;
        }
        
        element_type get(size_type row, size_type col) const {
            return board_[to_id(row, col)];
        }

        void generate(double difficulty = 0) {

        }

        int solve() {
            return 0;
        }

    protected:
        using coordinate_type = std::pair<size_type, size_type>;
        bool is_row_valid(size_type row) const{
            std::set<element_type> row_set;
            for(size_type col = 0; col < problem_scale; ++col) {
                element_type element = board_[to_id(row, col)];
                if(element == 0) {
                    continue;
                }
                if(row_set.find(element) == row_set.end()) {
                    row_set.insert(element);
                } else {
                    return false;
                }
            }
            return true;
        }
        bool is_col_valid(size_type col) const{
            std::set<element_type> col_set;
            for(size_type row = 0; row < problem_scale; ++row) {
                element_type element = board_[to_id(row, col)];
                if(element == 0) {
                    continue;
                }
                if(col_set.find(element) == col_set.end()) {
                    col_set.insert(element);
                } else {
                    return false;
                }
            }
            return true;
        }
        bool is_house_valid(size_type house) const {
            std::set<element_type> house_set;
            for(size_type hid = 0; hid < problem_scale; ++hid) {
                element_type element = board_[house_to_id(house, hid)];
                if(element == 0) {
                    continue;
                }
                if(house_set.find(element) == house_set.end()) {
                    house_set.insert(element);
                } else {
                    return false;
                }
            }
            return true;
        }
        bool is_row_completed(size_type row) const {
            size_type filled = 0;
            for(size_type col = 0; col < problem_scale; ++col) {
                if(board_[to_id(row, col)] != 0)
                    filled++;
            }
            return  filled == problem_scale;
        }
        bool is_col_completed(size_type col) const {
            size_type filled = 0;
            for(size_type row = 0; row < problem_scale; ++row) {
                if(board_[to_id(row, col)] != 0)
                    filled++;
            }
            return  filled == problem_scale;
        }
        bool is_house_completed(size_type house) const {
            size_type filled = 0;
            for(size_type hid = 0; hid < problem_scale; ++hid) {
                if(board_[house_to_id(house, hid)] != 0)
                    filled++;
            }
            return  filled == problem_scale;
        }

        coordinate_type to_coordinate(size_type id) const {
            return std::make_pair(
                id / problem_scale,
                id % problem_scale
            );
        }
        size_type to_id(size_type row, size_type col) const {
            return row * problem_scale + col;
        }
        size_type house_to_id(size_type house, size_type hid) const {
            return house_table_[house][hid];
        }

        void init_house() {
            for(size_type row = 0; row < problem_scale; ++row) {
                for(size_type col = 0; col < problem_scale; ++col) {
                    size_type belonged_house = (row/house_scale)*house_scale  + (col/house_scale);
                    size_type house_cornor_row = (row/house_scale)*house_scale;
                    size_type house_cornor_col = (col/house_scale)*house_scale;
                    size_type id_in_house = (row - house_cornor_row)*house_scale + (col - house_cornor_col);
                    house_table_[belonged_house][id_in_house] = to_id(row, col);
                }
            }
        }

    private:
        std::vector<element_type> board_;
        std::vector<std::vector<size_type>> house_table_;
    };

}
