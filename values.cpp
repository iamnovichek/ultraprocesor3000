/**
 * @file values.cpp
 * @brief Implements the accessor methods for constant values and message templates.
 *
 * This file provides the implementation for the accessor methods defined in values.hpp.
 * These methods allow access to private constants in the ExitStatusCodes,
 * ErrorMessages, and HardcodedValues classes.
 *
 * @date: May 4, 2025
 */


#include "values.hpp"

using namespace std;

/**
 * Returns success exit status code
 * @return int: Success exit status code
 */
int ExitStatusCodes::get_success_exit_status() {
    return SUCCESS_EXIT_STATUS;
}

/**
 * Returns failure exit status code
 * @return int: Failure exit status code
 */
int ExitStatusCodes::get_failure_exit_status() {
    return FAILURE_EXIT_STATUS;
}

/**
 * Returns file not provided error message
 * @return string_view: File not provided error message
 */
string_view ErrorMessages::get_file_not_provided_error() {
    return FILE_NOT_PROVIDED_ERROR;
}

/**
 * Returns unable to open file error message
 * @return string_view: Unable to open file error message
 */
string_view ErrorMessages::get_unable_to_open_file_error() {
    return UNABLE_TO_OPEN_FILE_ERROR;
}

/**
 * Returns unknown opcode error message
 * @return string_view: Unknown opcode error message
 */
string_view ErrorMessages::get_unknown_opcode_error() {
    return UNKNOWN_OPCODE_ERROR;
}

/**
 * Returns writing to stack region error message
 * @return string_view: Writing to stack region error message
 */
string_view ErrorMessages::get_writing_to_stack_region_error() {
    return WRITING_TO_STACK_REGION_ERROR;
}

/**
 * Returns reading from stack region error message
 * @return string_view: Reading from stack region error message
 */
string_view ErrorMessages::get_reading_from_stack_region_error() {
    return READING_FROM_STACK_REGION_ERROR;
}

/**
 * Returns stack overflow error message
 * @return string_view: Stack overflow error message
 */
string_view ErrorMessages::get_stack_overflow_error() {
    return STACK_OVERFLOW_ERROR;
}

/**
 * Returns stack underflow error message
 * @return string_view: Stack underflow error message
 */
string_view ErrorMessages::get_stack_underflow_error() {
    return STACK_UNDERFLOW_ERROR;
}

/**
 * Returns nullptr operand error message
 * @return string_view: nullptr operand error message
 */
string_view ErrorMessages::get_nullptr_operand_error() {
    return NULLPTR_OPERAND_ERROR;
}

/**
 * Returns invalid register ID error message
 * @return string_view: Invalid register ID error message
 */
string_view ErrorMessages::get_invalid_register_id_error() {
    return INVALID_REGISTER_ID_ERROR;
}

/**
 * Returns invalid opcode type error message
 * @return string_view: Invalid opcode type error message
 */
string_view ErrorMessages::get_invalid_first_operand_type_error() {
    return INVALID_FIRST_OPERAND_TYPE_ERROR;
}

/**
 * Returns invalid opcode type error message
 * @return string_view: Invalid opcode type error message
 */
string_view ErrorMessages::get_invalid_second_operand_type_error() {
    return INVALID_SECOND_OPERAND_TYPE_ERROR;
}

/**
 * Returns delimiter
 * @return char: Delimiter
 */
char HardcodedValues::get_delimiter_symbol() {
    return DELIMITER_SYMBOL;
}

/**
 * Returns null integer value
 * @return int: Null integer value
 */
int HardcodedValues::get_null_integer_value() {
    return NULL_INTEGER_VALUE;
}

/**
 * Returns program file path index
 * @return int: Program file path index
 */
int HardcodedValues::get_program_file_path_index() {
    return PROGRAM_FILE_PATH_INDEX;
}

/**
 * Returns first operand index
 * @return int: First operand index
 */
int HardcodedValues::get_first_operand_index() {
    return FIRST_OPERAND_INDEX;
}

/**
 * Returns second operand index
 * @return int: Second operand index
 */
int HardcodedValues::get_second_operand_index() {
    return SECOND_OPERAND_INDEX;
}

/**
 * Returns minimal program arguments number
 * @return int: Minimal program arguments number
 */
int HardcodedValues::get_minimal_program_arguments_number() {
    return MINIMAL_PROGRAM_ARGUMENTS_NUMBER;
}

/**
 * Returns several operands vector size
 * @return int: Several operands vector size
 */
int HardcodedValues::get_several_operands_vector_size() {
    return SEVERAL_OPERANDS_VECTOR_SIZE;
}

/**
 * Returns stack pointer size
 * @return int: Stack pointer size
 */
int HardcodedValues::get_stack_pointer_size() {
    return STACK_POINTER_SIZE;
}

/**
 * Returns bits in byte
 * @return int: Bits in byte
 */
int HardcodedValues::get_bits_in_byte() {
    return BITS_IN_BYTE;
}

/**
 * Returns stack size
 * @return int: Stack size
 */
int HardcodedValues::get_stack_size() {
    return STACK_SIZE;
}

/**
 * Returns first item index
 * @return int: First item index
 */
int HardcodedValues::get_first_item_index() {
    return FIRST_ITEM_INDEX;
}

/**
 * Returns second item index
 * @return int: Second item index
 */
int HardcodedValues::get_second_item_index() {
    return SECOND_ITEM_INDEX;
}

/**
 * Returns memory size
 * @return size_t: Memory size
 */
size_t HardcodedValues::get_memory_size() {
    return MEMORY_SIZE;
}
