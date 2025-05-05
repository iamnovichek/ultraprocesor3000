# UltraProcessor3000 Documentation

Welcome to the UltraProcessor3000! This documentation will guide you through understanding the program, its instruction set, and how to use it effectively.

---

## Overview

The UltraProcessor3000 is a lightweight virtual processor simulator designed to execute a simple assembly-like language. It operates on a limited set of instructions and utilizes 4 registers: `a`, `b`, `c`, and `d`. The program reads instructions from a `.txt` file, processes them line by line, and executes them.

---

## Instruction Set

| Opcode | Explanation                                                                 | Example                                  |
|--------|-----------------------------------------------------------------------------|------------------------------------------|
| SETv   | Set a register to an immediate value.                                       | `SETv a 10`  Sets register `a` to 10.     |
| SETr   | Set a register to another register’s value.                                 | `SETr a b`  Sets register `a` to value of `b`. |
| ADDv   | Add an immediate value to a register (with overflow protection).            | `ADDv a 5`  Adds 5 to register `a`.       |
| ADDr   | Add a register’s value to another register (with overflow protection).      | `ADDr a b`  Adds value of `b` to `a`.     |
| SUBv   | Subtract an immediate value from a register (with underflow protection).    | `SUBv a 3`  Subtracts 3 from register `a`.|
| SUBr   | Subtract a register’s value from another register (with underflow protection). | `SUBr a b`  Subtracts value of `b` from `a`. |
| IFNZ   | Skip the next instruction if the specified register is zero.                | `IFNZ a`  Skips next instruction if `a` is zero. |
| PRINT  | Output the value of a register.                                             | `PRINT a`  Prints the value of register `a`. |
| LOAD   | Load a 16-bit value from memory into a register.                            | `LOAD a 100`  Loads memory[100] into `a`. |
| STORE  | Store a 16-bit value from a register into memory.                           | `STORE a 100`  Stores `a` into memory[100]. |
| PUSH   | Push a register’s value onto the stack.                                     | `PUSH a`  Pushes the value of `a` onto the stack. |
| POP    | Pop the top value from the stack into a register.                           | `POP a`  Pops top of stack into `a`.     |

---

## Registers

The UltraProcessor3000 currently supports 4 registers:

`a`
`b`
`c`
`d`

---

## How to Use

### 1. Compilation

To compile the UltraProcessor3000 program:

```bash
g++ -o ultraprocessor3000 main.cpp
```

### 2. Creating a Program File

To write a program for the UltraProcessor3000:
  1) Create a `.txt` file (e.g., `program.txt`).
  2) Write your instructions line by line using the supported instruction set.

Example `program.txt`
```plaintext
SETv a 5
SETv b 10
ADDv a 3
ADDr a b
PRINT a
PUSH b
```

This example:
 1) Sets register `a` to 5.
 2) Sets register `b` to 10.
 3) Adds 3 to register `a`.
 4) Adds the value of `b` to `a`.
 5) Prints the value of `a`.
 6) Pushes the value of `b` onto the stack.


### 3. Running the Program

To execute your program:

```bash
./ultraprocessor3000 program.txt
```
This will process the instructions in `program.txt` and output the results.


### Notes

  - Instructions are executed sequentially, one per line.

  - Ensure your `program.txt` follows the correct instruction syntax to avoid errors.

  - Currently, the processor supports only 4 registers (`a`, `b`, `c`, `d`).
