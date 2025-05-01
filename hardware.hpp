/**
 * @file hardware.hpp
 * @brief Hardware components for the processor simulation.
 *
 * This file defines the hardware components of the processor simulation. 
 * It provides the necessary operations for register value manipulation.
 *
 * @author Dmytro Lunhu
 * @date April 21, 2025
 */

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

#include <iostream>
#include <array>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

/**
 * @class Register
 * @brief Represents a 16-bit processor register.
 *
 * Provides operations for setting, adding, and subtracting values.
 */
class Register {
uint16_t register_value = 0;

public:
    /**
     * @brief Assignment operator to set the register value.
     * @param value The value to set the register to.
     */
    void operator=(uint16_t value);
    
    /**
     * @brief Addition assignment operator with overflow protection.
     * @param value The value to add to the register.
     */
    void operator+=(uint16_t value);
    
    /**
     * @brief Subtraction assignment operator with underflow protection.
     * @param value The value to subtract from the register.
     */
    void operator-=(uint16_t value);
    
    /**
     * @brief Conversion operator to uint16_t.
     * @return The register's current value.
     */
    operator uint16_t() const;
};

/**
 * @class RegistersManager
 * @brief Manages a set of registers accessible by name or index.
 *
 * Provides a mapping from register names to Register objects.
 */
class RegistersManager {
static constexpr int REGISTERS_NUMBER = 4;
static const inline set<string> REGISTERS_SYMBOLS = {"a", "b", "c", "d"};
array<Register, REGISTERS_NUMBER> registers;

public:
    static constexpr uint16_t PROCESSOR_REGISTER_MIN_VALUE = 0;
    static constexpr uint16_t PROCESSOR_REGISTER_MAX_VALUE = UINT16_MAX;  // corresponds to 1111 1111 1111 1111 (16 bits)
    static unordered_map<string, Register*>& get_registers();
    static const set<string>& get_registers_symbols();
};

#endif
