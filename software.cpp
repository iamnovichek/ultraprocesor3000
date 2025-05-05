/**
 * @file software.cpp
 * @brief Implements the core functionalities of a virtual processor simulator.
 *
 * This file provides the implementation for the 'functools' class, which is
 * responsible for reading and executing instructions from a program file. It
 * simulates a basic processor that operates on 16-bit registers and
 * interacts with a virtual memory module.
 *
 * Key responsibilities implemented in this file include:
 *  - Reading a program file line by line and parsing each instruction.
 *  - Tokenizing instruction strings to identify opcodes and operands.
 *  - Supporting various instructions such as:
 *      * SETv: Set a register to an immediate value.
 *      * SETr: Set a register to another register's value.
 *      * ADDv: Add an immediate value to a register (with overflow protection).
 *      * ADDr: Add a register's value to another register (with overflow protection).
 *      * SUBv: Subtract an immediate value from a register (with underflow protection).
 *      * SUBr: Subtract a register's value from another register (with underflow protection).
 *      * IFNZ: Conditional execution by skipping the next instruction if a register is zero.
 *      * PRINT: Output the value of a register.
 *      * LOAD: Load a 16-bit value from memory into a register.
 *      * STORE: Store a 16-bit value from a register into memory.
 *      * PUSH: Push a register's value onto the stack.
 *      * POP: Pop the top value from the stack into a register.
 *  - Ensuring robust arithmetic by checking for overflow and underflow conditions.
 *  - Interfacing with a separate memory module for handling load, store, and
 * stack operations.
 *
 * @author: Dmytro Lunhu
 * @date: April 21, 2025
 */

#include "software.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "hardware.hpp"
#include "memory.hpp"
#include "values.hpp"

using namespace std;

auto RAM = Memory(HardcodedValues::get_memory_size());

/**
 * Executes the program in the text file
 * @param program_path The path to the file where the program is stored
 * @returns void
 */
void functools::exec(const string& program_path) {
    ifstream file(program_path);

    if (!file) {
        cerr << ErrorMessages::get_unable_to_open_file_error() << program_path << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }

    string line;

    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        Instruction instruction(line);

        // Proceed the instruction based on its opcode
        switch (instruction.opcode) {
            case SETv:
            case SETr:
                validate_two_operands_non_nullptr(instruction.operands);
                proceed_set_opcode(instruction.operands[HardcodedValues::get_first_item_index()],
                                   instruction.operands[HardcodedValues::get_second_item_index()]);
                break;

            case ADDv:
            case ADDr:
                validate_two_operands_non_nullptr(instruction.operands);
                proceed_add_opcode(instruction.operands[HardcodedValues::get_first_item_index()],
                                   instruction.operands[HardcodedValues::get_second_item_index()]);
                break;

            case SUBv:
            case SUBr:
                validate_two_operands_non_nullptr(instruction.operands);
                proceed_sub_opcode(instruction.operands[HardcodedValues::get_first_item_index()],
                                   instruction.operands[HardcodedValues::get_second_item_index()]);
                break;

            case IFNZ:
                validate_one_operand_non_nullptr(
                    instruction.operands[HardcodedValues::get_first_item_index()]);
                proceed_ifnz_opcode(instruction.operands[HardcodedValues::get_first_item_index()],
                                    file, line);
                break;

            case PRINT:
                validate_one_operand_non_nullptr(
                    instruction.operands[HardcodedValues::get_first_item_index()]);
                proceed_print_opcode(instruction.operands[HardcodedValues::get_first_item_index()]);
                break;

            case PUSH:
                validate_one_operand_non_nullptr(
                    instruction.operands[HardcodedValues::get_first_item_index()]);
                proceed_push_opcode(instruction.operands[HardcodedValues::get_first_item_index()]);
                break;

            case POP:
                validate_one_operand_non_nullptr(
                    instruction.operands[HardcodedValues::get_first_item_index()]);
                proceed_pop_opcode(instruction.operands[HardcodedValues::get_first_item_index()]);
                break;

            case LOAD:
                validate_two_operands_non_nullptr(instruction.operands);
                proceed_load_opcode(instruction.operands[HardcodedValues::get_first_item_index()],
                                    instruction.operands[HardcodedValues::get_second_item_index()]);
                break;

            case STORE:
                validate_two_operands_non_nullptr(instruction.operands);
                proceed_store_opcode(
                    instruction.operands[HardcodedValues::get_first_item_index()],
                    instruction.operands[HardcodedValues::get_second_item_index()]);
                break;
        }
    }
}

/**
 * Helper method to get a register by its ID
 * @param id The register ID
 * @return Pointer to the register
 */
Register* functools::get_register_by_id(const uint16_t id) {
    if (const set<string> registers = RegistersManager::get_registers_symbols();id < registers.size()) {
        return RegistersManager::get_registers()[*next(registers.begin(), id)];
    }

    cerr << ErrorMessages::get_invalid_register_id_error() << endl;
    exit(ExitStatusCodes::get_failure_exit_status());
}

/**
 * Validates that the operand is not a nullptr
 * @param operands operands to validate
 * @returns void
 */
void functools::validate_two_operands_non_nullptr(const Operand* operands[2]) {
    if (operands[HardcodedValues::get_first_item_index()] == nullptr ||
        operands[HardcodedValues::get_second_item_index()] == nullptr) {
        cerr << ErrorMessages::get_nullptr_operand_error() << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }
};

/**
 * Validates that the operand is not a nullptr
 * @param operand Operand to validate
 * @returns void
 */
void functools::validate_one_operand_non_nullptr(const Operand* operand) {
    if (operand == nullptr) {
        cerr << ErrorMessages::get_nullptr_operand_error() << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }
};

/**
 * Validates the first operand type
 * @param operand Operand to validate
 */
void functools::validate_first_operand_type(const Operand* operand) {
    if (operand -> type != REGISTER) {
        cerr << ErrorMessages::get_invalid_first_operand_type_error() << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }
}

/**
 * Validates that the operands are not nullptr
 * @param first_operand First operand to validate
 * @param second_operand Second operand to validate
 * @returns void
 */
void functools::validate_heap_opcodes_operands_types(const Operand* first_operand,
                                                     const Operand* second_operand) {
    if (first_operand -> type != NUMERIC ||
        second_operand -> type != REGISTER) {
        cerr << ErrorMessages::get_invalid_first_operand_type_error() << endl;
        cerr << ErrorMessages::get_invalid_second_operand_type_error() << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }
}

/**
 * Proceeds SETv/SETr opcodes
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_set_opcode(const Operand* first_operand, const Operand* second_operand) {
    validate_first_operand_type(first_operand);

    switch (second_operand -> type) {
        case NUMERIC:
            *get_register_by_id(first_operand -> parsed) = second_operand -> parsed;

            break;

        case REGISTER:
            *get_register_by_id(first_operand -> parsed) =
                static_cast<uint16_t>(*get_register_by_id(second_operand -> parsed));

            break;

        default:
            cerr << ErrorMessages::get_invalid_second_operand_type_error() << endl;
            exit(ExitStatusCodes::get_failure_exit_status());
    }
}

/**
 * Proceeds ADDv/ADDr opcodes
 * @param first_operand First operand
 * @param second_operand
 */
void functools::proceed_add_opcode(const Operand* first_operand, const Operand* second_operand) {
    validate_first_operand_type(first_operand);

    switch (second_operand -> type) {
        case NUMERIC:
            *get_register_by_id(first_operand -> parsed) += second_operand -> parsed;

            break;

        case REGISTER:
            *get_register_by_id(first_operand -> parsed) += *get_register_by_id(second_operand -> parsed);

            break;

        default:
            cerr << ErrorMessages::get_invalid_second_operand_type_error() << endl;
            exit(ExitStatusCodes::get_failure_exit_status());
    }
}

/**
 * Proceeds SUB opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_sub_opcode(const Operand* first_operand, const Operand* second_operand) {
    validate_first_operand_type(first_operand);

    switch (second_operand -> type) {
        case NUMERIC:
            *get_register_by_id(first_operand -> parsed) -= second_operand -> parsed;

            break;

        case REGISTER:
            *get_register_by_id(first_operand -> parsed) -= *get_register_by_id(second_operand -> parsed);

            break;

        default:
            cerr << ErrorMessages::get_invalid_second_operand_type_error() << endl;
            exit(ExitStatusCodes::get_failure_exit_status());
    }
}

/**
 * Proceeds PRINT opcode
 * @param operand An operand
 */
void functools::proceed_print_opcode(const Operand* operand) {
    validate_first_operand_type(operand);

    cout << *get_register_by_id(operand -> parsed) << endl;
}

/**
 * Proceeds IFNZ opcode
 * @param operand Operand to proceed
 * @param file ifstream file variable
 * @param line ifstream's string line variable
 */
void functools::proceed_ifnz_opcode(const Operand* operand, ifstream& file, string& line) {
    validate_first_operand_type(operand);
    if (static_cast<uint16_t>(*get_register_by_id(operand -> parsed)) == 0) {
        getline(file, line);
    }
}

/**
 * Proceeds STORE opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_store_opcode(const Operand* first_operand, const Operand* second_operand) {
    validate_heap_opcodes_operands_types(first_operand, second_operand);
    RAM[static_cast<uint8_t>(first_operand -> parsed)] =
        static_cast<uint16_t>(*get_register_by_id(second_operand -> parsed));
}

/**
 * Proceeds LOAD opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_load_opcode(const Operand* first_operand, const Operand* second_operand) {
    validate_heap_opcodes_operands_types(first_operand, second_operand);
    *get_register_by_id(second_operand -> parsed) = RAM[static_cast<uint8_t>(first_operand -> parsed)];
}

/**
 * Proceeds PUSH opcode
 * @param operand An operand
 */
void functools::proceed_push_opcode(const Operand* operand) {
    validate_first_operand_type(operand);
    RAM.push(*get_register_by_id(operand -> parsed));
}

/**
 * Proceeds POP opcode
 * @param operand An operand
 */
void functools::proceed_pop_opcode(const Operand* operand) {
    validate_first_operand_type(operand);
    *get_register_by_id(operand -> parsed) = RAM.pop();
}

/**
 * Checks if the sum will overflow
 * @param reg register value
 * @param number value to add
 * @return bool true if the sum will overflow and false if it won't
 */
bool functools::is_overflow(const uint16_t reg, const uint16_t number) {
    const uint16_t sum = reg + number;

    return sum < reg;
}

/**
 * Checks if the subtraction result will underflow
 * @param reg register value
 * @param number number to subtract
 * @return bool true if the subtraction will underflow and false if it won't
 */
bool functools::is_underflow(const uint16_t reg, const uint16_t number) {
    return reg < number;
}

/**
 * Splits a string into tokens
 * @param str a string to split
 * @param delimiter a delimiter to split the string by
 * @returns vector<string> a split string into tokens
 */
vector<string> functools::split(const string& str, const char& delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
