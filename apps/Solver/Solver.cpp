/* Solver.cpp
 * 
 * Author: Wentao and Jiejun
 * Created: 20200404
 * Version: 0.1
*/

#include "Solver.h"

#include <iostream>
#include <unordered_map>

using command_t = char;
const std::unordered_map<std::string, char> command_encoder {
    {"question", 'Q'},
    {"revise"  , 'R'},
    {"solve"   , 'S'},
    {"quit"    , 'X'},
    {"help"    , 'H'}
};

void welcome_msg() {
    std::cout << "Welcome to SodokuZoo solver" << std::endl;
}

void say_goodbay() {
    std::cout << "Bye~" << std::endl;
}

void usage() {
    std::cout << "Command list:" << std::endl;
    std::cout << "question) ask a sodoku problem"    << std::endl;
    std::cout << "revise  ) revise previous problem" << std::endl;
    std::cout << "solve   ) solve the problem"       << std::endl;
    std::cout << "help    ) print this help message" << std::endl;
    std::cout << "quit    ) quit"                    << std::endl;
}

std::string get_command() {
    std::string command;
    std::cout << ">>> ";
    if(std::getline(std::cin, command))
        return command;
    else 
        return "quit";
}

int main() {

    bool stop = false;
    std::unique_ptr<SudokuZoo::SolverApp::Solver> p_solver; 

    welcome_msg();
    usage();
    std::string command;
    while(!stop) {
        command = get_command();
        command_t comm;
        try {
            comm = command_encoder.at(command);
            switch(comm) {
            case 'Q':
                p_solver = std::make_unique<SudokuZoo::SolverApp::Solver>();
                p_solver->input_sudoku();
                std::cout << "Problem Set:" << std::endl;
                p_solver->print_sudoku();
                break;
            case 'R':
                if(p_solver->is_solved()) {
                    std::cout << "Problem has been solved as following. To start a new one, please Enter \"question\"." << std::endl;
                    p_solver->print_sudoku();
                } else {
                    p_solver->revise_sudoku();
                    std::cout << "Revised Problem Set:" << std::endl;
                    p_solver->print_sudoku();
                }
                break;
            case 'S':
                if(p_solver->is_solved()) {
                    std::cout << "Problem has been solved." << std::endl;
                    p_solver->print_sudoku();
                } else {
                    p_solver->solve();
                }
                break;
            case 'X':
                stop = true;
                break;
            case 'H':
                usage();
                break;
            default:
                break;
            }
        } catch (std::out_of_range& e) {
            std::cerr << "Unknown command: " << command << std::endl;
            usage();
        }
    }
    say_goodbay();

    return 0;
}
