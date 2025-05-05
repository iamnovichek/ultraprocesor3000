/**
 * @file values.hpp
 * @brief Provides global constants and definitions for the virtual processor simulator.
 *
 * This file defines several utility classes that store constant values and message templates used
 * throughout the simulator:
 *
 *  - ExitStatusCodes: Contains constants for program exit statuses (success and failure).
 *  - ErrorMessages: Provides formatted error message templates for file I/O issues, unknown
 * opcodes, and memory/stack access violations.
 *  - HardcodedValues: Defines various configuration constants including command-line argument
 * indices, register values, memory size, stack size, and other limits essential for the simulation.
 *
 * These definitions help ensure consistency in error handling and configuration across the entire
 * codebase.
 *
 * @date: May 4, 2025
 */

#ifndef VALUES_HPP
#define VALUES_HPP

#include <iostream>
#include <string_view>

using namespace std;

/**
 * A class that stores all exit status codes
 */
class ExitStatusCodes {
   public:
    static int get_success_exit_status();
    static int get_failure_exit_status();

   private:
    static constexpr int SUCCESS_EXIT_STATUS = 0;
    static constexpr int FAILURE_EXIT_STATUS = 1;
};

/**
 * A class that stores all exit messages
 */
class ErrorMessages {
   public:
    static string_view get_file_not_provided_error();
    static string_view get_unable_to_open_file_error();
    static string_view get_unknown_opcode_error();
    static string_view get_writing_to_stack_region_error();
    static string_view get_reading_from_stack_region_error();
    static string_view get_stack_overflow_error();
    static string_view get_stack_underflow_error();
    static string_view get_nullptr_operand_error();
    static string_view get_invalid_register_id_error();
    static string_view get_invalid_first_operand_type_error();
    static string_view get_invalid_second_operand_type_error();

   private:
    static constexpr string_view FILE_NOT_PROVIDED_ERROR = "Program file path was not provided.";
    static constexpr string_view UNABLE_TO_OPEN_FILE_ERROR = "Unable to open file: ";
    static constexpr string_view UNKNOWN_OPCODE_ERROR = "Unknown opcode: ";
    static constexpr string_view WRITING_TO_STACK_REGION_ERROR = "Error: writing to stack region ";
    static constexpr string_view READING_FROM_STACK_REGION_ERROR =
        "Error: reading from stack region ";
    static constexpr string_view STACK_OVERFLOW_ERROR = "Error: stack overflow";
    static constexpr string_view STACK_UNDERFLOW_ERROR = "Error: stack underflow";
    static constexpr string_view NULLPTR_OPERAND_ERROR = "Error: working with nullptr operand";
    static constexpr string_view INVALID_REGISTER_ID_ERROR = "Error: invalid register ID";
    static constexpr string_view INVALID_FIRST_OPERAND_TYPE_ERROR = "Error: invalid first operand";
    static constexpr string_view INVALID_SECOND_OPERAND_TYPE_ERROR =
        "Error: invalid second operand";
};

/**
 * A class that stores all "magic numbers"
 */
class HardcodedValues {
   public:
    static int get_null_integer_value();
    static int get_program_file_path_index();
    static int get_first_operand_index();
    static int get_second_operand_index();
    static int get_minimal_program_arguments_number();
    static int get_several_operands_vector_size();
    static int get_stack_pointer_size();
    static int get_bits_in_byte();
    static int get_stack_size();
    static int get_first_item_index();
    static int get_second_item_index();
    static size_t get_memory_size();
    static char get_delimiter_symbol();

   private:
    static constexpr char DELIMITER_SYMBOL = ' ';
    static constexpr size_t MEMORY_SIZE = 1 << 8;
    static constexpr int FIRST_ITEM_INDEX = 0;
    static constexpr int NULL_INTEGER_VALUE = 0;
    static constexpr int PROGRAM_FILE_PATH_INDEX = 1;
    static constexpr int FIRST_OPERAND_INDEX = 1;
    static constexpr int SECOND_ITEM_INDEX = 1;
    static constexpr int SECOND_OPERAND_INDEX = 2;
    static constexpr int MINIMAL_PROGRAM_ARGUMENTS_NUMBER = 2;
    static constexpr int SEVERAL_OPERANDS_VECTOR_SIZE = 3;
    static constexpr int STACK_POINTER_SIZE = 2;
    static constexpr int BITS_IN_BYTE = 8;
    static constexpr int STACK_SIZE = 16;
};

#endif
