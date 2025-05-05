/**
 * @file memory.hpp
 *
 * This file defines the Memory class which provides an abstraction for the simulated
 * memory used by the processor. It includes functions to:
 *  - Read a 16-bit value from a specific memory address.
 *  - Write a 16-bit value to a specific memory address.
 *  - Push a 16-bit value onto a simulated stack.
 *  - Pop a 16-bit value from the simulated stack.
 *
 * @date: May 4, 2025
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <string_view>

using namespace std;

/**
 * @class Memory
 * 
 * A declarative memory class that declares all methods that must and will be used in memory.cpp
 */
class Memory {
    uint8_t* MEM;
    static uint8_t stack_pointer;

    // Validation methods
    static void validate_address(const uint8_t& address, const string_view& error_message);
    static void validate_stack_pointer(const string_view& error_message, const bool& is_error);

   public:
    Memory(uint8_t nbytes);
    ~Memory();

    // Heap operators
    uint16_t& operator[](uint8_t address);
    uint16_t operator[](uint8_t address) const;

    // Stack operations
    void push(uint16_t value);
    uint16_t pop()const;
};

#endif