/**
 * @file insctructions.cpp
 * @brief Implementation of instruction parsing for the processor.
 *
 * This file implements the functionality to parse raw instruction strings into
 * structured Instruction objects with their respective opcodes and operands.
 *
 * @author Dmytro Lunhu
 * @date April 21, 2025
 */

#include "instructions.hpp"
#include "software.hpp"
#include "hardware.hpp"
#include "values.hpp"
#include <sstream>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static const unordered_map<string, Opcode> OPCODES_MAP = {
    {"SETv", Opcode::SETv},
    {"SETr", Opcode::SETr},
    {"ADDv", Opcode::ADDv},
    {"ADDr", Opcode::ADDr},
    {"SUBv", Opcode::SUBv},
    {"SUBr", Opcode::SUBr},
    {"IFNZ", Opcode::IFNZ},
    {"PRINT", Opcode::PRINT},
    {"PUSH", Opcode::PUSH},
    {"POP", Opcode::POP},
    {"LOAD", Opcode::LOAD},
    {"STORE", Opcode::STORE},
};

/**
 * @brief Constructs an Instruction by parsing a raw instruction string.
 * 
 * Parses the opcode and operands from the raw string and initializes
 * the Instruction object.
 * 
 * @param raw The raw instruction string to parse.
 */
Instruction::Instruction(const string& raw) : opcode(parse_opcode(raw)) {
    operands[0] = operands[1] = nullptr;
    const vector<string> tokens = functools::split(raw, ' ');
    const set<string>& symbols = RegistersManager::get_registers_symbols();
    const int items = HardcodedValues::get_several_operands_vector_size() - 1;

    for (int i = 0; i < items; ++i) {
        const int operand_index = HardcodedValues::get_first_operand_index() + i;

        if (operand_index >= static_cast<int>(tokens.size())) break;

        const string& token = tokens[operand_index];
        Operand* operand = new Operand();

        if (symbols.contains(token)) {
            operand -> type = OperandType::REGISTER;
            operand -> parsed = static_cast<uint16_t>(distance(symbols.begin(), symbols.find(token))); 
        } else {
            operand -> type = OperandType::NUMERIC;
            operand -> parsed = static_cast<uint16_t>(stoi(token));
        }
        
        operands[i] = operand;
    }
}

/**
 * @brief Destructor for the Instruction class.
 * 
 * Releases memory allocated for operands.
 */
Instruction::~Instruction() {
    delete operands[0];
    delete operands[1];
}

/**
 * @brief Parses an opcode from a raw instruction string.
 * 
 * Maps the string representation of an opcode to its corresponding
 * enum value. If the opcode is not recognized, the program exits
 * with an error message.
 *
 * @param raw The raw instruction string to parse.
 * @return The corresponding Opcode enum value.
 */
Opcode parse_opcode(const string& raw) {
    string opcode = functools::split(raw, ' ')[HardcodedValues::get_first_item_index()];

    if (OPCODES_MAP.contains(opcode)) return OPCODES_MAP.find(opcode) -> second;
    
    cerr << ErrorMessages::get_unknown_opcode_error() << opcode << endl;
    exit(ExitStatusCodes::get_failure_exit_status());
}


