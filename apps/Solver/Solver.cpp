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
    SudokuZoo::SolverApp::Solver solver;

    solver.welcome_msg();
    usage();
    std::string command;
    while(!stop) {
        command = get_command();
        command_t comm;
        try {
            comm = command_encoder.at(command);
        } catch (std::out_of_range& e) {
            std::cerr << "Unknown command: " << command << std::endl;
            usage();
        }
        switch(comm) {
        case 'Q':
            solver.input_sudoku();
            std::cout << "Problem Set:" << std::endl;
            solver.print_sudoku();
            break;
        case 'R':
            solver.revise_sudoku();
            std::cout << "Revised Problem Set:" << std::endl;
            solver.print_sudoku();
            break;
        case 'S':
            solver.solve();
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
    }
    solver.say_goodbay();

    return 0;
}
