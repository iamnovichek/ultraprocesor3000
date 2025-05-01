/**
 * @file instructions.hpp
 * @brief Defines the instruction set for the processor.
 *
 * This file provides the core instruction definitions for the processor,
 * including opcodes, operand structure, and instruction representation.
 * 
 * The instruction set uses suffix notation to indicate operand types:
 *  - 'v' suffix: Indicates the operation uses an immediate value as operand
 *  - 'r' suffix: Indicates the operation uses a register value as operand
 * 
 * @author Dmytro Lunhu
 * @date April 21, 2025
 */

#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @enum Opcode
 * @brief Enumeration of supported instruction opcodes for the processor.
 * 
 * Opcodes with 'v' suffix operate on immediate values, while those with 'r' suffix
 * operate on values from registers.
 */
enum Opcode {
    SETv,
    SETr,
    ADDv,
    ADDr,
    SUBv,
    SUBr,
    IFNZ,
    PRINT,
    PUSH,
    POP,
    LOAD,
    STORE, 
};

/**
 * @enum OperandType
 * @brief Enumeration of operand types.
 * 
 * This enum is used to differentiate between immediate values and register names.
 * The 'NUMERIC' type indicates an immediate value, while 'REGISTER' indicates a register value.
 */
enum OperandType {
    NUMERIC,
    REGISTER,
};

/**
 * @struct Operand
 * @brief Represents an operand for an instruction.
 *
 * An operand can be a register name or an immediate value.
 * For a REGISTER type operand, the parsed value must be unique for each register.
 */
struct Operand {
    OperandType type;
    uint16_t parsed;
};

/**
 * @struct Instruction
 * @brief Represents a processor instruction with its opcode and operands.
 *
 * Each instruction consists of an opcode and zero or more operands.
 */
struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];

    Instruction(const string& raw);
    ~Instruction();
};

Opcode parse_opcode(const string& raw);

#endif
