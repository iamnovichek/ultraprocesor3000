/**
 * @file hardware.cpp
 * @brief Implementation of hardware components.
 *
 * This file implements the functionality of Register and RegistersManager classes,
 * including register operations with overflow/underflow protection and register
 * file access methods.
 *
 * @author Dmytro Lunhu
 * @date April 21, 2025
 */

#include "hardware.hpp"
#include "software.hpp"
#include <iostream>
#include <set>

using namespace std;

/**
 * @brief Assignment operator to set the register value.
 * 
 * Sets the register value to the provided value.
 * 
 * @param value The value to set the register to.
 */
void Register::operator=(uint16_t value) {
    register_value = value;
}

/**
 * @brief Addition assignment operator with overflow protection.
 * 
 * Adds a value to the register, clamping to PROCESSOR_REGISTER_MAX_VALUE if overflow occurs.
 * 
 * @param value The value to add to the register.
 */
void Register::operator+=(uint16_t value) {
    if (!functools::is_overflow(register_value, value)) 
    register_value += value; else 
    register_value = RegistersManager::PROCESSOR_REGISTER_MAX_VALUE;
}

/**
 * @brief Subtraction assignment operator with underflow protection.
 * 
 * Subtracts a value from the register, clamping to PROCESSOR_REGISTER_MIN_VALUE if underflow occurs.
 * 
 * @param value The value to subtract from the register.
 */
void Register::operator-=(uint16_t value) {
    if (!functools::is_underflow(register_value, value)) 
    register_value -= value; else 
    register_value = RegistersManager::PROCESSOR_REGISTER_MIN_VALUE;
}

Register::operator uint16_t() const {
    return register_value;
}

/**
 * Creates and returns a map of registers
 * @returns unordered_map<string, Register*>: A map of registers
 */
unordered_map<string, Register*>& RegistersManager::get_registers() {
    static unordered_map<string, Register*> processor_registers_mapping = {};

    if (processor_registers_mapping.empty()) {
        for (set<string>::iterator symbol = RegistersManager::REGISTERS_SYMBOLS.begin(); 
            symbol != RegistersManager::REGISTERS_SYMBOLS.end(); ++symbol) {
                processor_registers_mapping[*symbol] = new Register();
        }
    }
    
    
   return processor_registers_mapping;
}

/**
 * Returns the set of register symbols
 * @returns const set<string>&: A set of register symbols
 */
const set<string>& RegistersManager::get_registers_symbols() {
    return RegistersManager::REGISTERS_SYMBOLS;
}
