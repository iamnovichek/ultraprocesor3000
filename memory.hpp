/**
 * @file memory.hpp
 * @brief Header file for the memory module of the virtual processor simulator.
 *
 * This file defines the 'memory' class which provides an abstraction for the simulated
 * memory used by the processor. It includes functions to:
 *  - Read a 16-bit value from a specific memory address.
 *  - Write a 16-bit value to a specific memory address.
 *  - Push a 16-bit value onto a simulated stack.
 *  - Pop a 16-bit value from the simulated stack.
 *
 * In addition, the file declares internal utility functions for validating memory access:
 *  - validate_address: Ensures that memory operations do not access reserved regions.
 *  - validate_stack_pointer: Checks that stack operations do not result in overflow or underflow.
 *
 * The simulated RAM is implemented as a fixed-size array, and a static stack pointer variable
 * is maintained to track the current top of the stack. These definitions use constants from
 * 'values.h' to ensure consistency in memory size and error handling throughout the simulator.
 *
 * Author: Dmytro Lunhu
 * Date: April 21, 2025
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <array>
#include <string_view>

using namespace std;

/**
 * A declarative memory class that declares all methods that must and will be used in memory.cpp
 */
class Memory {
  uint8_t* MEM;
  
  // Validation methods
  static void validate_address(const uint8_t& address, const string_view& error_message);
  static void validate_stack_pointer(const string_view& error_message, const bool& is_error);
  
  static uint8_t stack_pointer;

 public:
  Memory(uint8_t nbytes);
  ~Memory();
  
  // Memory access operators
  uint16_t& operator[](uint8_t address);
  uint16_t  operator[](uint8_t address) const;
  
  // Stack operations
  void push(uint16_t value);
  uint16_t pop();
};

#endif  // MEMORY_HPP