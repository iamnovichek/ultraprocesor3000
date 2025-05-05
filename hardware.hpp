/**
 * @file hardware.hpp
 * @brief Hardware components for the processor simulation.
 *
 * This file defines the hardware components of the processor simulation.
 * It provides the necessary operations for register value manipulation.
 *
 * @date May 4, 2025
 */

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * @class Register
 *
 * Provides operations for setting, adding, and subtracting values.
 */
class Register {
    uint16_t register_value = 0;

   public:
    void operator=(uint16_t value);
    void operator+=(uint16_t value);
    void operator-=(uint16_t value);
    operator uint16_t() const;
};

/**
 * @class RegistersManager
 *
 * Provides a mapping from register names to Register objects.
 */
class RegistersManager {
    static constexpr int REGISTERS_NUMBER = 4;
    static const inline set<string> REGISTERS_SYMBOLS = {"a", "b", "c", "d"};
    array<Register, REGISTERS_NUMBER> registers;

   public:
    static constexpr uint16_t PROCESSOR_REGISTER_MIN_VALUE = 0;
    static constexpr uint16_t PROCESSOR_REGISTER_MAX_VALUE =
        UINT16_MAX;  // corresponds to 1111 1111 1111 1111 (16 bits)
    static unordered_map<string, Register*>& get_registers();
    static const set<string>& get_registers_symbols();
};

#endif
