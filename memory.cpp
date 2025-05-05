/**
 * @file memory.cpp
 *
 * This file provides the implementation for the simulated memory used by the processor.
 * The memory module is responsible for:
 *  - Emulating a fixed-size RAM using a statically allocated array.
 *  - Reading and writing 16-bit values from/to specific memory addresses.
 *  - Managing a stack with push and pop operations, including boundary checks.
 *  - Validating memory accesses to ensure that operations do not interfere with the reserved stack
 * region.
 *
 * @date: May 4, 2025
 */

#include "memory.hpp"

#include <iostream>
#include <string>
#include <string_view>

#include "values.hpp"

using namespace std;

uint8_t Memory::stack_pointer = 0;

/**
 * Constructor for the Memory class
 * 
 * @param nbytes The size of the memory in bytes
 */
Memory::Memory(const uint8_t nbytes) {
    MEM = new uint8_t[nbytes];
}

/**
 * Destructor for the Memory class
 * 
 * @return void: Nothing
 */
Memory::~Memory() {
    delete[] MEM;
}

/**
 * Overloaded operator to read/write 16-bit values from/to memory
 * 
 * @param address Memory address
 * @return uint16_t: The value at the specified address
 */
uint16_t& Memory::operator[](const uint8_t address) {
    validate_address(address, ErrorMessages::get_writing_to_stack_region_error());

    return *reinterpret_cast<uint16_t*>(MEM + address);
}

/**
 * Overloaded operator to read 16-bit values from memory
 * 
 * @param address Memory address
 * @return uint16_t: The value at the specified address
 */
uint16_t Memory::operator[](const uint8_t address) const {
    validate_address(address, ErrorMessages::get_reading_from_stack_region_error());

    return static_cast<uint16_t>((MEM[address + 1] << HardcodedValues::get_bits_in_byte()) |
                                 MEM[address]);
}

/**
 * Adds a value to the top of the stack
 * @param value The value to write
 * @return void: Nothing
 */
void Memory::push(const uint16_t value) {
    validate_stack_pointer(ErrorMessages::get_stack_overflow_error(),
                           stack_pointer + HardcodedValues::get_stack_pointer_size() >
                               HardcodedValues::get_stack_size());

    const uint16_t memory_size = static_cast<uint16_t>(HardcodedValues::get_memory_size()) - 1;
    MEM[stack_pointer] = static_cast<uint8_t>(value & memory_size);
    MEM[stack_pointer + 1] =
        static_cast<uint8_t>((value >> HardcodedValues::get_bits_in_byte()) & memory_size);
    stack_pointer += HardcodedValues::get_stack_pointer_size();
}

/**
 * Removes the value from the top of the stack and returns that value
 * @return uint16_t: The value at the top of the stack
 */
uint16_t Memory::pop()const {
    validate_stack_pointer(ErrorMessages::get_stack_underflow_error(),
                           stack_pointer < HardcodedValues::get_stack_pointer_size());

    stack_pointer -= HardcodedValues::get_stack_pointer_size();
    return static_cast<uint16_t>((MEM[stack_pointer + 1] << HardcodedValues::get_bits_in_byte()) |
                                 MEM[stack_pointer]);
}

/**
 * Validates if we are reading/writing from/to the heap
 * 
 * @param address Memory address
 * @param error_message Error message to print
 * @return void: Nothing
 */
void Memory::validate_address(const uint8_t& address, const string_view& error_message) {
    if (address < HardcodedValues::get_stack_size()) {
        cerr << error_message << address << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }
}

/**
 * Validates if the stack pointer allows us to push/pop to/from the stack
 * 
 * @param error_message Error validation message
 * @param is_error Defines if the operation will cause an error
 * @return void: Nothing
 */
void Memory::validate_stack_pointer(const string_view& error_message, const bool& is_error) {
    if (is_error) {
        cerr << error_message << endl;
        exit(ExitStatusCodes::get_failure_exit_status());
    }
}
