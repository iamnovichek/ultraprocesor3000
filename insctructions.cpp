/**
 * @file insctructions.cpp
 *
 * This file implements the functionality to parse raw instruction strings into
 * structured Instruction objects with their respective opcodes and operands.
 *
 * @date May 4, 2025
 */

#include <algorithm>
#include <array>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "hardware.hpp"
#include "instructions.hpp"
#include "software.hpp"
#include "values.hpp"

using namespace std;

const unordered_map<string, Opcode> OPCODES_MAP = {
    {"SETv", SETv}, {"SETr", SETr}, {"ADDv", ADDv},
    {"ADDr", ADDr}, {"SUBv", SUBv}, {"SUBr", SUBr},
    {"IFNZ", IFNZ}, {"PRINT", PRINT}, {"PUSH", PUSH},
    {"POP", POP}, {"LOAD", LOAD}, {"STORE", STORE},
};

/**
 * Parses the opcode and operands from the raw string and initializes
 * the Instruction object.
 *
 * @param raw The raw instruction string to parse.
 */
Instruction::Instruction(const string& raw) : opcode(parse_opcode(raw)) {
    operands[HardcodedValues::get_first_item_index()] =
        operands[HardcodedValues::get_second_item_index()] = nullptr;
    const vector<string> tokens = functools::split(raw, HardcodedValues::get_delimiter_symbol());
    const set<string>& symbols = RegistersManager::get_registers_symbols();
    const int items = HardcodedValues::get_several_operands_vector_size() - 1;

    for (int i = 0; i < items; ++i) {
        const int operand_index = HardcodedValues::get_first_operand_index() + i;

        if (operand_index >= static_cast<int>(tokens.size())) break;

        const string& token = tokens[operand_index];
        Operand* operand = new Operand();

        if (symbols.contains(token)) {
            operand -> type   = REGISTER;
            operand -> parsed = static_cast<uint16_t>(
                distance(symbols.begin(), symbols.find(token)));
        } else {
            operand -> type   = NUMERIC;
            operand -> parsed = static_cast<uint16_t>(stoi(token));
        }

        operands[i] = operand;
    }
}

/**
 * Releases memory allocated for operands.
 */
Instruction::~Instruction() {
    delete operands[HardcodedValues::get_first_item_index()];
    delete operands[HardcodedValues::get_second_item_index()];
}

/**
 * Maps the string representation of an opcode to its corresponding
 * enum value. If the opcode is not recognized, the program exits
 * with an error message.
 *
 * @param raw The raw instruction string to parse.
 * @return The corresponding Opcode enum value.
 */
Opcode parse_opcode(const string& raw) {
    string opcode = functools::split(raw, HardcodedValues::get_delimiter_symbol())[HardcodedValues::get_first_item_index()];

    if (OPCODES_MAP.contains(opcode)) return OPCODES_MAP.find(opcode) -> second;

    cerr << ErrorMessages::get_unknown_opcode_error() << opcode << endl;
    exit(ExitStatusCodes::get_failure_exit_status());
}
