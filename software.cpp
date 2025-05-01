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
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "memory.hpp"
#include "values.hpp"
#include "hardware.hpp"

using namespace std;

Memory RAM = Memory(HardcodedValues::get_memory_size());

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
        if (line.empty())
            continue;

        // Parse the instruction
        Instruction instr(line);
        
        // Execute the instruction based on its opcode
        switch (instr.opcode) {
            case Opcode::SETv:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER &&
                    instr.operands[1]->type == OperandType::NUMERIC) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    *reg = instr.operands[1]->parsed;
                }
                break;
                
            case Opcode::SETr:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER &&
                    instr.operands[1]->type == OperandType::REGISTER) {
                    Register* reg1 = get_register_by_id(instr.operands[0]->parsed);
                    Register* reg2 = get_register_by_id(instr.operands[1]->parsed);
                    *reg1 = static_cast<uint16_t>(*reg2);
                }
                break;
                
            case Opcode::ADDv:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER &&
                    instr.operands[1]->type == OperandType::NUMERIC) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    uint16_t value = instr.operands[1]->parsed;
                    *reg += value;
                }
                break;
                
            case Opcode::ADDr:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER &&
                    instr.operands[1]->type == OperandType::REGISTER) {
                    Register* reg1 = get_register_by_id(instr.operands[0]->parsed);
                    Register* reg2 = get_register_by_id(instr.operands[1]->parsed);
                    uint16_t value = static_cast<uint16_t>(*reg2);
                    *reg1 += value;
                }
                break;
                
            case Opcode::SUBv:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER &&
                    instr.operands[1]->type == OperandType::NUMERIC) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    uint16_t value = instr.operands[1]->parsed;
                    *reg -= value;
                }
                break;
                
            case Opcode::SUBr:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER &&
                    instr.operands[1]->type == OperandType::REGISTER) {
                    Register* reg1 = get_register_by_id(instr.operands[0]->parsed);
                    Register* reg2 = get_register_by_id(instr.operands[1]->parsed);
                    uint16_t value = static_cast<uint16_t>(*reg2);
                    *reg1 -= value;
                }
                break;
                
            case Opcode::IFNZ:
                if (instr.operands[0] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    if (static_cast<uint16_t>(*reg) == 0) {
                        // Skip next instruction
                        getline(file, line);
                    }
                }
                break;
                
            case Opcode::PRINT:
                if (instr.operands[0] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    cout << static_cast<uint16_t>(*reg) << endl;
                }
                break;
                
            case Opcode::PUSH:
                if (instr.operands[0] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    // Use the Memory instance instead of the static memory functions
                    RAM.push(static_cast<uint16_t>(*reg));
                }
                break;
                
            case Opcode::POP:
                if (instr.operands[0] != nullptr && 
                    instr.operands[0]->type == OperandType::REGISTER) {
                    Register* reg = get_register_by_id(instr.operands[0]->parsed);
                    // Use the Memory instance instead of the static memory functions
                    *reg = RAM.pop();
                }
                break;
                
            case Opcode::LOAD:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::NUMERIC &&
                    instr.operands[1]->type == OperandType::REGISTER) {
                    Register* reg = get_register_by_id(instr.operands[1]->parsed);
                    *reg = RAM[static_cast<uint8_t>(instr.operands[0]->parsed)];
                }
                break;
                
            case Opcode::STORE:
                if (instr.operands[0] != nullptr && instr.operands[1] != nullptr && 
                    instr.operands[0]->type == OperandType::NUMERIC &&
                    instr.operands[1]->type == OperandType::REGISTER) {
                    Register* reg = get_register_by_id(instr.operands[1]->parsed);

                    RAM[static_cast<uint8_t>(instr.operands[0]->parsed)] = static_cast<uint16_t>(*reg);
                }
                break;
        }
    }
}

/**
 * Helper method to get a register by its ID
 * @param id The register ID (0-3 for a-d)
 * @return Pointer to the register
 */
Register* functools::get_register_by_id(uint16_t id) {
    static const array<string, 4> register_names = {"a", "b", "c", "d"};
    if (id < register_names.size()) {
        return RegistersManager::get_registers()[register_names[id]];
    }
    cerr << "Invalid register ID: " << id << endl;
    exit(ExitStatusCodes::get_failure_exit_status());
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

/**
 * Returns the operand (parameter)
 * @param instr An instruction
 * @param operand_index operand index
 * @returns variant<string, uint16_t>: Parsed operand
 */
variant<string, uint16_t> functools::parse_operand(const string& instr,
                                                  const int& operand_index) {
    const vector<string> row = split(instr, ' ');

    // We are using our registers or the stack
    if (RegistersManager::get_registers_symbols().contains(row[operand_index])) {
        return row[operand_index];
    }

    // We are using the heap (immediate number)
    return static_cast<uint16_t>(stoi(row[operand_index]));
}

/**
 * Returns the instruction without operand
 * @param instr An instruction
 * @returns string Parsed opcode
 */
string functools::parse_opcode(const string& instr) {
    return split(instr, ' ')[HardcodedValues::get_first_item_index()];
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
 * Proceeds IFNZ opcode
 * @param operand Operand to proceed
 * @param file ifstream file variable
 * @param line ifstream's string line variable
 */
void functools::proceed_ifnz_opcode(const variant<string, uint16_t>& operand,
                                    ifstream& file,
                                    string& line) {
  if (static_cast<uint16_t>(*RegistersManager::get_registers()[get<string>(operand)]) ==
      HardcodedValues::get_null_integer_value()) {
    getline(file, line);
  }
}

/**
 * Proceeds SET opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_set_opcode(
    const variant<string, uint16_t>& first_operand,
    const variant<string, uint16_t>& second_operand) {
  *RegistersManager::get_registers()[get<string>(first_operand)] =
      get_second_operand(second_operand);
}

/**
 * Proceeds ADD opcode
 * @param first_operand First operand
 * @param second_operand
 */
void functools::proceed_add_opcode(
    const variant<string, uint16_t>& first_operand,
    const variant<string, uint16_t>& second_operand) {
  Register* reg = RegistersManager::get_registers()[get<string>(first_operand)];
  const uint16_t add_value = get_second_operand(second_operand);
  
  if (!is_overflow(static_cast<uint16_t>(*reg), add_value)) {
    *reg += add_value;
  } else {
    *reg = RegistersManager::PROCESSOR_REGISTER_MAX_VALUE;
  }
}

/**
 * Proceeds SUB opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_sub_opcode(
    const variant<string, uint16_t>& first_operand,
    const variant<string, uint16_t>& second_operand) {
  Register* reg = RegistersManager::get_registers()[get<string>(first_operand)];
  const uint16_t sub_value = get_second_operand(second_operand);
  
  if (!is_underflow(static_cast<uint16_t>(*reg), sub_value)) {
    *reg -= sub_value;
  } else {
    *reg = RegistersManager::PROCESSOR_REGISTER_MIN_VALUE;
  }
}

/**
 * Proceeds PRINT opcode
 * @param operand An operand
 */
void functools::proceed_print_opcode(
    const variant<string, uint16_t>& operand) {
  cout << static_cast<uint16_t>(*RegistersManager::get_registers()[get<string>(operand)]) << endl;
}

/**
 * Proceeds LOAD opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_load_opcode(
    const variant<string, uint16_t>& first_operand,
    const variant<string, uint16_t>& second_operand) {
  *RegistersManager::get_registers()[get<string>(second_operand)] =
  RAM[get<uint16_t>(first_operand)];
}

/**
 * Proceeds STORE opcode
 * @param first_operand First operand
 * @param second_operand Second operand
 */
void functools::proceed_store_opcode(
    const variant<string, uint16_t>& first_operand,
    const variant<string, uint16_t>& second_operand) {
        RAM[get<uint16_t>(first_operand)] = static_cast<uint16_t>(*RegistersManager::get_registers()[get<string>(second_operand)]);
}

/**
 * Proceeds PUSH opcode
 * @param operand An operand
 */
void functools::proceed_push_opcode(
    const variant<string, uint16_t>& operand) {
        RAM.push(static_cast<uint16_t>(*RegistersManager::get_registers()[get<string>(operand)]));
}

/**
 * Proceeds POP opcode
 * @param operand An operand
 */
void functools::proceed_pop_opcode(
    const variant<string, uint16_t>& operand) {
  *RegistersManager::get_registers()[get<string>(operand)] = RAM.pop();
}

/**
 * Returns the second's operand value
 * @param operand An operand
 * @return uint16_t: Second operand value
 */
uint16_t functools::get_second_operand(
    const variant<string, uint16_t>& operand) {
  if (holds_alternative<string>(operand)) {
    return static_cast<uint16_t>(*RegistersManager::get_registers()[get<string>(operand)]);
  }

  return get<uint16_t>(operand);
}
