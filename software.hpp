/**
 * @file software.hpp
 *
 * This header declares the 'functools' class, which provides the main
 * functions for reading, parsing, and executing instructions from a program
 * file. It provides the simulation of a simple processor that operates on
 * 16-bit registers and supports a banch of instructions, including arithmetic
 * operations, conditional execution, memory access, and stack operations.
 *
 * @date: May 4, 2025
 */

#ifndef SOFTWARE_HPP
#define SOFTWARE_HPP

#include <fstream>
#include <string>
#include <vector>

#include "hardware.hpp"
#include "instructions.hpp"

using namespace std;

/**
 * A declarative class that declares all methods that must and will be used in software.cpp
 */
class functools {
    // Helper methods
    static Register* get_register_by_id(uint16_t id);

    // Validation methods
    static void validate_two_operands_non_nullptr(const Operand* operands[2]);
    static void validate_one_operand_non_nullptr(const Operand* operand);
    static void validate_first_operand_type(const Operand* operand);
    static void validate_heap_opcodes_operands_types(const Operand* first_operand,
                                                     const Operand* second_operand);

    // Opcode execution methods
    static void proceed_set_opcode(const Operand* first_operand, const Operand* second_operand);
    static void proceed_add_opcode(const Operand* first_operand, const Operand* second_operand);
    static void proceed_sub_opcode(const Operand* first_operand, const Operand* second_operand);
    static void proceed_print_opcode(const Operand* operand);
    static void proceed_ifnz_opcode(const Operand* operand, ifstream& file, string& line);
    static void proceed_store_opcode(const Operand* first_operand, const Operand* second_operand);
    static void proceed_load_opcode(const Operand* first_operand, const Operand* second_operand);
    static void proceed_push_opcode(const Operand* operand);
    static void proceed_pop_opcode(const Operand* operand);

   public:
    static void exec(const string& program_path);

    // Arithmetic validation methods
    static bool is_overflow(uint16_t reg, uint16_t number);
    static bool is_underflow(uint16_t reg, uint16_t number);

    // String parsing methods
    static vector<string> split(const string& str, const char& delimiter);
};

#endif
