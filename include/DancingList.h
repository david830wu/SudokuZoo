/* DancingList.h
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

namespace SudokuZoo { namespace ExactCoverProblem {

    using row_index_type = int;
    using row_element_type = bool;

    class Solution {
    public:
        using size_type = int;

        Solution() {}

        Solution(std::initializer_list<row_index_type> li) 
            : solution_(li)
        { }

        size_type size() const {
            return solution_.size();
        }

        bool operator==(const Solution& rhs) const {
            return solution_ == rhs.solution_;
        }
        bool operator<(const Solution& rhs) const {
            return solution_ < rhs.solution_;
        }
    
    protected:
        std::set<row_index_type> solution_;
    };

    class SolutionSet {
    public:
        friend std::ostream& operator<<(std::ostream& os, const SolutionSet& s_set) {
        }

        using size_type = std::size_t;

        SolutionSet()
        {}

        SolutionSet(std::initializer_list<Solution> li) 
            : solution_set_(li)
        { }

        size_type size() const {
            return solution_set_.size();
        }

        bool operator==(const SolutionSet& rhs) const {
            return solution_set_ == rhs.solution_set_;
        }
    protected:
        std::set<Solution> solution_set_;
    };

    class Row {
    public:
        using size_type = std::size_t;
        
        Row(std::initializer_list<row_element_type> li)
            : row_(li)
        { }

    protected:
        std::vector<row_element_type> row_;

    };

    class Problem {
    public:
        Problem(std::initializer_list<Row> li) {
        }

        int add_row(const Row& row) {
        }
        int add_row(Row&& row) {
        }

        SolutionSet solve() {
            return SolutionSet();
        }
    protected:
        std::vector<Row> problem_def_;

    };


namespace Details {
    class DancingList {
    public:
        using size_type = int;
        using binary_type = int;
        using col_index_type = size_type;

        DancingList(size_type num_cols)
            : num_cols_(num_cols)
            , col_names_(num_cols + 1)
            , num_rows_(0)
            , num_ones_(0)
        {
            // structure
            // column:    0,            1,            2, ...
            // row 0 : root, col_header_1, col_header_2, ...
            // row 1 :                0/1,          0/1, ... 
            // row 2 :                0/1,          0/1, ... 
            // row 3 : ...
            // And ones are counted start from root, and column headers count as well

            // add root to dancing list, root is in row 0, col 0
            col_names_[0] = "root";
            row_index_.push_back(0);
            col_index_.push_back(0);
            L_.push_back(num_cols_);
            R_.push_back(1);
            U_.push_back(0);
            D_.push_back(0);
            C_.push_back(0);
            S_.push_back(0);
            num_ones_++;

            // add column headers to dancing list
            // col_headers are in row 0, col from 1 to num_cols
            for(size_type col = 1; col <= num_cols_; ++col) {
                col_names_[col] = std::to_string(col);
                row_index_.push_back(0);
                col_index_.push_back(col);
                L_.push_back(col - 1);
                R_.push_back(col + 1);
                U_.push_back(col);
                D_.push_back(col);
                C_.push_back(col);
                S_.push_back(0);
                num_ones_++;
            }
            R_[num_cols_] = root_id_;
            num_rows_++;
            row_names_.push_back("col_header");

            partial_solution_.reserve(num_cols_);
        }

        DancingList& add_row_by_binary(const std::vector<binary_type>& binary_row, const std::string& row_name = "") {
            add_row(binary_to_col(binary_row), row_name);
            return *this;
        }

        DancingList& add_row(const std::vector<size_type>& row, const std::string& row_name = "") {
            size_type ones_in_row = row.size();
            for(size_type col : row) {
                row_index_.push_back(num_rows_);
                col_index_.push_back(col);
                L_.push_back(num_ones_ - 1);
                R_.push_back(num_ones_ + 1);
                U_.push_back(U_[col]); // get upper element of column header
                D_[U_[col]] = num_ones_;
                D_.push_back(col);
                U_[col] = num_ones_;
                C_.push_back(col);

                S_[col]++;
                num_ones_++;
            }
            size_type row_last = num_ones_ - 1;
            size_type row_first = row_last - ones_in_row + 1;
            L_[row_first] = row_last;
            R_[row_last] = row_first;
            row_names_.push_back(row_name);
            num_rows_++;
            return *this;
        }

        const std::string& get_row_name(size_type row) const {
            if(row == 0 || row >= row_names_.size())
                throw std::out_of_range("row index is not valid");
            return row_names_[row];
        }

        void add_init_condition(size_type row) {
            // cover row, i.e. cover all columns in the row
            if(row > *row_index_.rbegin()) {
                throw std::invalid_argument("Initial condition row index exceeds max row");
            }

            if(!is_capable_condition(row)){
                throw std::runtime_error("Incapable initial condition");
            }

            partial_solution_.push_back(row);
            // find the first node of the row
            size_type j = 0;
            for(j = 0; j < row_index_.size(); ++j) {
                if(row_index_[j] == row) {
                    break;
                }
            }
            std::vector<int> removed_col;
            cover_column(C_[j]);
            removed_col.push_back(C_[j]);
            for(size_type i = R_[j]; i != j; i = R_[i]){
                cover_column(C_[i]);
                removed_col.push_back(C_[i]);
            }
        }

        bool is_capable_condition(size_type row) {
            // TODO: scan all partial solution inserted before to 
            // check that no one appears in the same column
            return true;
        }

        void cover_column(size_type col) {
            // cover column header
            L_[R_[col]] = L_[col];
            R_[L_[col]] = R_[col];
            // cover overlapped rows from up to down and from left to right
            for(size_type i = D_[col]; i != col; i = D_[i]) { // for nodes in col
                for(size_type j = R_[i]; j != i; j = R_[j]) { // for nodes in the same row
                    // Knuth cover operation (1)
                    U_[D_[j]] = U_[j];
                    D_[U_[j]] = D_[j];
                    S_[C_[j]]--;
                }
            }
        }
        void uncover_column(size_type col) {
            // uncover overlapped rows from down to up and from right to left
            for(size_type i = U_[col]; i != col; i = U_[i]) {
                for(size_type j = L_[i]; j != i; j = L_[j]) {
                    S_[C_[j]]++;
                    // Knuth recover magic operation (2)
                    U_[D_[j]] = j;
                    D_[U_[j]] = j;
                }
            }
            L_[R_[col]] = col;
            R_[L_[col]] = col;
        }

        size_type find_min_ones_col() const {
            size_type min_ones = num_ones_;
            size_type min_col = root_id_;
            for(size_type j = R_[root_id_]; j != root_id_; j = R_[j]) {
                if(S_[j] < min_ones) {
                    min_col = j;
                    min_ones = S_[j];
                }
            }
            return min_col;
        }

        void search(size_type level) {
            if(R_[root_id_] == root_id_) {
                // row 0 being empty except root leads to a success solution
                solutions_.push_back(partial_solution_);
                return;
            }

            size_type c = find_min_ones_col();
            cover_column(c);
            for(size_type r = D_[c]; r != c; r = D_[r]) {
                partial_solution_.push_back(row_index_[r]);
                for(size_type j = R_[r]; j != r; j = R_[j]) {
                    cover_column(C_[j]);
                }
                search(level + 1);
                partial_solution_.pop_back();
                for(size_type j = L_[r]; j != r; j = L_[j]) {
                    uncover_column(C_[j]);
                }
            }
            uncover_column(c);
        }

        void print_row_solution() const {
            if(!solutions_.empty()) {
                size_type sol_num = 1;
                for(auto& sol : solutions_) {
                    std::cout << "Sol_" << sol_num++ << ": ";
                    std::vector<size_type> sol_row = sol;
                    // std::sort(sol_row.begin(), sol_row.end());
                    std::cout << "[ \n";
                    for(size_type i = 0; i < sol_row.size(); ++i) {
                        size_type selected_row = sol_row[i];
                        std::cout << i << ": " <<  selected_row << "(" << row_names_[selected_row] << ")" << ( i != (sol_row.size() - 1) ? ", \n" : "\n");
                    }
                    std::cout << "]" << std::endl;
                }
            } else {
                std::cout << "Found no solutions." << std::endl;
            }
        }

        size_type left_column_headers() const {
            size_type left_columns = 0;
            for(size_type i = R_[root_id_]; i != root_id_; i = R_[i]) 
                left_columns++;
            return left_columns;
        }

        const auto& solve() {
            if(left_column_headers() == 0) {
                std::cout << "has already been solved by init condition" << std::endl;
            }
            search(partial_solution_.size());
            return solutions_;
        }

        bool operator==(const DancingList& rhs) const {
            return true;
        }

        void dump(std::ostream& os) const {
            os << "node id:   [";
            for(size_type id = 0; id < row_index_.size(); ++id) {
                os << std::setw(5) << id << (id != (row_index_.size() - 1) ? ", " : "]\n");
            }
            os << "row_index: [";
            for(auto iter = row_index_.begin(); iter != row_index_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (row_index_.end() - 1) ? ", " : "]\n");
            }
            os << "col_index: [";
            for(auto iter = col_index_.begin(); iter != col_index_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (col_index_.end() - 1) ? ", " : "]\n");
            }
            os << "L:         [";
            for(auto iter = L_.begin(); iter != L_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (L_.end() - 1) ? ", " : "]\n");
            }
            os << "R:         [";
            for(auto iter = R_.begin(); iter != R_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (R_.end() - 1) ? ", " : "]\n");
            }
            os << "U:         [";
            for(auto iter = U_.begin(); iter != U_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (U_.end() - 1) ? ", " : "]\n");
            }
            os << "D:         [";
            for(auto iter = D_.begin(); iter != D_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (D_.end() - 1) ? ", " : "]\n");
            }
            os << "S:         [";
            for(auto iter = S_.begin(); iter != S_.end(); ++iter) {
                os << std::setw(5) << *iter << (iter != (S_.end() - 1) ? ", " : "]\n");
            }
        }

    private:
        std::vector<size_type> binary_to_col(const std::vector<binary_type>& binary_format) {
            size_type col = 1;
            std::vector<size_type> col_format;
            for(const auto& bin : binary_format) {
                if(bin != 0) {
                    col_format.push_back(col);
                }
                col++;
            }
            return col_format;
        }

    private:

        static const size_type root_id_ = 0;
        const size_type num_cols_;

        // array of num_cols elements
        std::vector<std::string> col_names_;
        std::vector<size_type> S_;
        // arry of num_rows
        std::vector<std::string> row_names_;

        // array of num_ones elements; row start from 1 to num_rows;
        size_type num_rows_, num_ones_;
        // ones are enumerated from 0 to num_ones;
        std::vector<size_type> row_index_; // Note: row start from 1
        std::vector<size_type> col_index_; // Note: col start from 1
        std::vector<size_type> L_, R_, U_, D_, C_;

        // solutions
        std::vector<size_type> partial_solution_;
        std::vector<std::vector<size_type>> solutions_;
    };
};

} /* namespace ExactCoverProblem */ } /* namespace SudokuZoo */
