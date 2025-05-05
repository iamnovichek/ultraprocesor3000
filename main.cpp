/**
 * @file main.cpp
 *
 * This program simulates a basic processor executing instructions from a file.
 * It supports arithmetic operations, conditional execution, memory access,
 * and stack operations using 16-bit registers.
 *
 * Supported instructions:
 *  - SETv <register> <value>: Set the specified register to an immediate value
 *  - SETr <register> <register>: Set the specified register to another register's value
 *  - ADDv <register> <value>: Add an immediate value to the specified register (with overflow
 * protection)
 *  - ADDr <register> <register>: Add a register's value to another register (with overflow
 * protection)
 *  - SUBv <register> <value>: Subtract an immediate value from the specified register (with
 * underflow protection)
 *  - SUBr <register> <register>: Subtract a register's value from another register (with underflow
 * protection)
 *  - IFNZ <register>: Skip the next instruction if the specified register is zero
 *  - PRINT <register>: Output the value of the specified register
 *  - LOAD <memory_address> <register>: Load a 16-bit value from memory at the given address into
 * the register
 *  - STORE <memory_address> <register>: Store the 16-bit value from the register into memory at the
 * given address
 *  - PUSH <register>: Push the value of the specified register onto the stack
 *  - POP <register>: Pop the top value from the stack into the specified register
 *
 * Memory operations (LOAD and STORE) interact with a simulated memory module,
 * while stack operations (PUSH and POP) are performed with appropriate boundary checks.
 *
 * @date May 4, 2025
 */

#include <iostream>

#include "software.hpp"
#include "values.hpp"

using namespace std;

/**
 * A main function that runs the program
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @returns int Status code
 */
int main(const int argc, const char** argv) {
    if (argc >= HardcodedValues::get_minimal_program_arguments_number()) {
        const string program_file_path = argv[HardcodedValues::get_program_file_path_index()];
        functools::exec(program_file_path);
    } else {
        cerr << ErrorMessages::get_file_not_provided_error() << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }

    return ExitStatusCodes::get_success_exit_status();
}
