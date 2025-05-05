/**
 * @file instructions.hpp
 *
 * This file provides the core instruction definitions for the processor,
 * including opcodes, operand structure, and instruction representation.
 *
 * The instruction set uses suffix notation to indicate operand types:
 *  - 'v' suffix: Indicates the operation uses an immediate value as operand
 *  - 'r' suffix: Indicates the operation uses a register value as operand
 *
 * @date May 4, 2025
 */

#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include <string>

using namespace std;

/**
 * @enum Opcode
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
 *
 * An operand can be a register name or an immediate value.
 */
struct Operand {
    OperandType type;
    uint16_t parsed;
};

/**
 * @struct Instruction
 *
 * Each instruction consists of an opcode and zero or more operands.
 */
struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];

    Instruction(const string& raw);
    ~Instruction();
};

/**
 * Parses an opcode from a raw instruction string.
 *
 * @param raw The raw instruction string to parse.
 * @return Opcode The parsed opcode.
 */
Opcode parse_opcode(const string& raw);

#endif
