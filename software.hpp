/**
 * @file software.hpp
 * @brief Header file for the core functionality of the virtual processor simulator.
 *
 * This header declares the 'functools' class, which provides the main
 * functions for reading, parsing, and executing instructions from a program
 * file. It provides the simulation of a simple processor that operates on
 * 16-bit registers and supports a banch of instructions, including arithmetic
 * operations, conditional execution, memory access, and stack operations.
 *
 * Key features provided by this module include:
 *  - Parsing instruction strings to extract opcodes and operands.
 *  - Executing instructions such as:
 *      * SETv/SETr: Setting registers to immediate values or other register values.
 *      * ADDv/ADDr: Adding immediate values or register values to registers with overflow checks.
 *      * SUBv/SUBr: Subtracting immediate values or register values from registers with underflow checks.
 *      * IFNZ: Conditional instruction skipping based on register values.
 *      * PRINT: Outputting the value of a register.
 *      * LOAD and STORE: Interfacing with the memory module to transfer data
 * between registers and memory.
 *      * PUSH and POP: Implementing stack operations.
 *  - Maintaining a mapping between register names and their corresponding 16-bit values.
 *  - Utility functions for string tokenization and arithmetic condition
 * checking.
 *
 * The 'functools' class works in conjunction with other modules such as
 * 'software.cpp', 'memory.hpp', 'memory.cpp', and 'values.hpp' to provide a
 * modular and maintainable architecture for the virtual processor.
 *
 * @author: Dmytro Lunhu
 * @date: April 21, 2025
 */

#ifndef SOFTWARE_HPP
#define SOFTWARE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <variant>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include "instructions.hpp"
#include "hardware.hpp"

using namespace std;

/**
 * A declarative class that declares all methods that must and will be used in software.cpp
 */
class functools {
 public:
  static void exec(const string& program_path);
  // Arithmetic validation methods
  static bool is_overflow(uint16_t reg, uint16_t number);
  static bool is_underflow(uint16_t reg, uint16_t number);

  // String parsing methods
  static vector<string> split(const string& str, const char& delimiter);

 private:
  // Helper methods
  static Register* get_register_by_id(uint16_t id);
  
  // Parsing and utility methods
  static string parse_opcode(const string& instr);
  static variant<string, uint16_t> parse_operand(const string& instr, const int& operand_index);
  static uint16_t get_second_operand(const variant<string, uint16_t>& operand);
  
  // Instruction execution methods
  static void proceed_set_opcode(const variant<string, uint16_t>& first_operand,
                                const variant<string, uint16_t>& second_operand);
  static void proceed_add_opcode(const variant<string, uint16_t>& first_operand,
                                const variant<string, uint16_t>& second_operand);
  static void proceed_sub_opcode(const variant<string, uint16_t>& first_operand,
                                const variant<string, uint16_t>& second_operand);
  static void proceed_print_opcode(const variant<string, uint16_t>& operand);
  static void proceed_ifnz_opcode(const variant<string, uint16_t>& operand,
                                 ifstream& file,
                                 string& line);
  static void proceed_store_opcode(const variant<string, uint16_t>& first_operand,
                                  const variant<string, uint16_t>& second_operand);
  static void proceed_load_opcode(const variant<string, uint16_t>& first_operand,
                                 const variant<string, uint16_t>& second_operand);
  static void proceed_push_opcode(const variant<string, uint16_t>& operand);
  static void proceed_pop_opcode(const variant<string, uint16_t>& operand);
};


#endif
