# RISC-V Simulator & Assembler

<div align="center">

### **A Complete RISC-V RV64I Architecture Implementation**

*Full-featured assembler, simulator, and debugger for RISC-V assembly language*

---

**[Features](#-key-features)** •
**[Architecture](#-architecture-overview)** •
**[Installation](#-installation)** •
**[Usage](#-usage-guide)** •
**[Technical Details](#-technical-implementation-details)** •
**[Examples](#-examples)**

---

</div>

## 📋 Table of Contents

1. [Overview](#-overview)
2. [Key Features](#-key-features)
3. [Architecture Overview](#-architecture-overview)
4. [Project Structure](#-project-structure)
5. [Installation](#-installation)
6. [Usage Guide](#-usage-guide)
7. [Technical Implementation Details](#-technical-implementation-details)
8. [Instruction Set Support](#-instruction-set-support)
9. [Memory Model](#-memory-model)
10. [Examples](#-examples)
11. [Debugging Features](#-debugging-features)
12. [Error Handling](#-error-handling)
13. [Authors](#-authors)

---

## 🎯 Overview

This project is a **comprehensive RISC-V implementation** consisting of two main components:

1. **RISC-V Assembler**: Converts RISC-V assembly language into machine code (hexadecimal format)
2. **RISC-V Simulator**: Executes RISC-V assembly programs with full register, memory, and stack simulation

The implementation follows the **RV64I base integer instruction set** with support for all major instruction formats (R, I, S, B, J, U) and includes advanced debugging capabilities like breakpoints, step execution, and stack frame tracking.

### 🎓 Academic Context

- **Course**: Computer Architecture (CS2323), Lab 3 & 4
- **Institution**: IIT Hyderabad
- **Students**: Ahmik Virani (ES22BTECH11001), Divya Rajparia (ES22BTECH11013)

---

## ✨ Key Features

### Assembler Capabilities

- ✅ **Complete Instruction Set Support**: All 6 RISC-V instruction formats (R, I, S, B, J, U)
- ✅ **Label Resolution**: Two-pass assembly with forward and backward label references
- ✅ **Register Alias Support**: Both canonical (`x0-x31`) and ABI names (`zero`, `ra`, `sp`, etc.)
- ✅ **Immediate Value Validation**: Range checking for all immediate operands
- ✅ **Hexadecimal Output**: Generates 32-bit machine code in hex format
- ✅ **Comprehensive Error Reporting**: Line-specific error messages with detailed diagnostics

### Simulator Capabilities

- 🚀 **Full RV64I Execution**: 64-bit register operations with proper signed/unsigned arithmetic
- 🧠 **Memory Management**: Separate `.data` and `.text` sections with little-endian byte ordering
- 📊 **Stack Simulation**: Call stack tracking with function entry/exit monitoring
- 🔍 **Interactive Debugging**: Breakpoints, step execution, and state inspection
- 📈 **Register File**: 32 64-bit general-purpose registers (`x0-x31`)
- 💾 **Memory Space**: 327,681 bytes (0x00000 - 0x50000) with separate text and data segments
- ⚡ **Advanced Features**: Supports `.data` directives (`.byte`, `.half`, `.word`, `.dword`)

---

## 🏗️ Architecture Overview

### System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                    RISC-V Simulator System                  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌──────────────────┐         ┌──────────────────┐        │
│  │   Assembler      │         │    Simulator     │        │
│  │   Component      │────────▶│    Component     │        │
│  └──────────────────┘         └──────────────────┘        │
│          │                             │                   │
│          │                             │                   │
│          ▼                             ▼                   │
│  ┌──────────────────┐         ┌──────────────────┐        │
│  │  Assembly Code   │         │  Register File   │        │
│  │  (.s files)      │         │  (x0 - x31)      │        │
│  └──────────────────┘         └──────────────────┘        │
│          │                             │                   │
│          ▼                             ▼                   │
│  ┌──────────────────┐         ┌──────────────────┐        │
│  │  Machine Code    │         │  Memory System   │        │
│  │  (hex output)    │         │  (328KB total)   │        │
│  └──────────────────┘         └──────────────────┘        │
│                                        │                   │
│                                        ▼                   │
│                               ┌──────────────────┐         │
│                               │   Text Segment   │         │
│                               │   Data Segment   │         │
│                               │   Stack Segment  │         │
│                               └──────────────────┘         │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Component Interaction Flow

```
Assembly File (.s)
       │
       ▼
┌──────────────┐
│  Two-Pass    │  Pass 1: Label Detection & Symbol Table Creation
│  Assembler   │  Pass 2: Instruction Encoding & Code Generation
└──────────────┘
       │
       ▼
Machine Code (.hex)
       │
       ▼
┌──────────────┐
│   Simulator  │──▶ load <filename>     (Load assembly into memory)
│   Engine     │──▶ run                 (Execute entire program)
│              │──▶ step                (Single instruction execution)
│              │──▶ regs                (Display register values)
│              │──▶ mem <addr> <count>  (Display memory contents)
│              │──▶ show-stack          (Display call stack)
│              │──▶ break <line>        (Set breakpoint)
│              │──▶ del break <line>    (Remove breakpoint)
└──────────────┘
```

---

## 📁 Project Structure

```
RISC-V-Simulator/
│
├── Assembler/
│   ├── ES22BTECH11013_LabAssgn3_Src.cpp      # Assembler source code
│   ├── Makefile                               # Build configuration for assembler
│   ├── testcase-R.s                           # R-type instruction test cases
│   ├── testcase-I.s                           # I-type instruction test cases
│   ├── testcase-S.s                           # S-type instruction test cases
│   ├── testcase-BJU.s                         # B/J/U-type instruction test cases
│   ├── output.hex                             # Generated machine code output
│   ├── ES22BTECH11013_LabAssgn3_Report.pdf    # Technical report
│   └── ES22BTECH11013_LabAssgn3_ReadME.pdf    # Assembler documentation
│
├── Simulator/
│   ├── Lab4_ES22BTECH11001_ES22BTECH11013_Source_Code.cpp  # Simulator source
│   ├── makefile                               # Build configuration for simulator
│   ├── README                                 # Simulator documentation
│   └── report.pdf                             # Simulator technical report
│
└── README.md                                  # This file
```

---

## 🛠️ Installation

### Prerequisites

- **Operating System**: Ubuntu/Linux (recommended) or any Unix-like system
- **Compiler**: g++ with C++11 support or later
- **Build Tool**: GNU Make

### Build Instructions

#### Building the Assembler

```bash
# Navigate to the Assembler directory
cd Assembler

# Compile the assembler
make

# This creates the 'assembler' executable
```

#### Building the Simulator

```bash
# Navigate to the Simulator directory
cd Simulator

# Compile the simulator
make

# This creates the 'riscv_sim' executable
```

#### Clean Build Artifacts

```bash
# In Assembler directory
make clean

# In Simulator directory
make clean
```

---

## 📖 Usage Guide

### 1. Using the Assembler

The assembler converts RISC-V assembly files into machine code.

#### Input File Format

Create a `.s` file with RISC-V assembly instructions:

```assembly
.data
.dword 12345, 67890
.word 100, 200
.half 10, 20
.byte 1, 2, 3

.text
lui x3, 0x10000
ld x1, 0(x3)
add x2, x1, x1
sw x2, 8(x3)
```

#### Running the Assembler

```bash
./assembler

# The assembler reads from the hardcoded input file
# and generates 'output.hex'
```

**Note**: The current implementation uses a hardcoded input filename in the source. To assemble different files, modify line 1015 in `ES22BTECH11013_LabAssgn3_Src.cpp`:

```cpp
ifstream file("your-testcase.s");  // Change the filename here
```

#### Output Format

The assembler generates `output.hex` with one 32-bit instruction per line:

```
00010137
00018083
001080b3
00213423
```

### 2. Using the Simulator

The simulator provides an interactive environment for executing and debugging RISC-V programs.

#### Starting the Simulator

```bash
./riscv_sim
```

You'll see a prompt where you can enter commands.

#### Simulator Commands

| Command | Syntax | Description |
|---------|--------|-------------|
| **load** | `load <filename>` | Load assembly file and initialize simulator |
| **run** | `run` | Execute program until completion or breakpoint |
| **step** | `step` | Execute single instruction and display state |
| **regs** | `regs` | Display all 32 register values in hexadecimal |
| **mem** | `mem <addr> <count>` | Display memory contents (Little Endian) |
| **show-stack** | `show-stack` | Display call stack with function frames |
| **break** | `break <line>` | Set breakpoint at specified line number |
| **del break** | `del break <line>` | Delete breakpoint at specified line |
| **exit** | `exit` | Exit the simulator |

#### Example Session

```bash
$ ./riscv_sim

# Load assembly program
load testcase-R.s

# View initial register state
regs

# Execute step by step
step
Executed: lui x3, 0x10000; PC=0x00000000

step
Executed: ld x2, 0(x3); PC=0x00000004

# Set breakpoint
break 10

# Run until breakpoint
run

# View memory contents
mem 0x10000 16

# View call stack
show-stack

# Exit simulator
exit
```

---

## 🔧 Technical Implementation Details

### Assembler Architecture

#### Two-Pass Assembly Process

**Pass 1: Symbol Table Construction**
- Scans entire source file
- Identifies and records labels with their memory addresses
- Detects duplicate label definitions
- Builds symbol table for label resolution

**Pass 2: Code Generation**
- Processes each instruction
- Resolves label references using symbol table
- Validates operands and immediate ranges
- Generates 32-bit machine code
- Outputs hexadecimal representation

#### Register Name Resolution

The assembler implements comprehensive register alias handling:

```cpp
string aliasRemover(string r, int line_number, string reg_name) {
    // Supports both canonical names (x0-x31) and ABI names
    // Examples: zero→x0, ra→x1, sp→x2, gp→x3, etc.
}
```

**Register Mapping Table**:

| ABI Name | Canonical | Usage | Preserved |
|----------|-----------|-------|-----------|
| `zero` | `x0` | Hard-wired zero | N/A |
| `ra` | `x1` | Return address | No |
| `sp` | `x2` | Stack pointer | Yes |
| `gp` | `x3` | Global pointer | N/A |
| `tp` | `x4` | Thread pointer | N/A |
| `t0-t2` | `x5-x7` | Temporaries | No |
| `s0/fp` | `x8` | Saved/Frame pointer | Yes |
| `s1` | `x9` | Saved register | Yes |
| `a0-a7` | `x10-x17` | Arguments/return values | No |
| `s2-s11` | `x18-x27` | Saved registers | Yes |
| `t3-t6` | `x28-x31` | Temporaries | No |

#### Instruction Encoding Functions

Each instruction format has a dedicated encoding function:

1. **`rformat()`** - R-type: `add`, `sub`, `and`, `or`, `xor`, `sll`, `srl`, `sra`
2. **`iformat()`** - I-type arithmetic: `addi`, `xori`, `ori`, `andi`, `jalr`
3. **`iformatshift()`** - I-type shift: `slli`, `srli`, `srai`
4. **`iformatload()`** - I-type load: `lb`, `lh`, `lw`, `ld`, `lbu`, `lhu`, `lwu`
5. **`sformat()`** - S-type: `sb`, `sh`, `sw`, `sd`
6. **`bformat()`** - B-type: `beq`, `bne`, `blt`, `bge`, `bltu`, `bgeu`
7. **`jformat()`** - J-type: `jal`
8. **`uformat()`** - U-type: `lui`

#### Immediate Value Handling

The assembler validates immediate ranges based on instruction type:

| Instruction Type | Immediate Bits | Range | Validation Function |
|-----------------|----------------|-------|---------------------|
| I-type (arithmetic) | 12 bits signed | -2048 to 2047 | Lines 448-453 |
| I-type (shift) | 6 bits unsigned | 0 to 63 | Lines 305-310 |
| S-type | 12 bits signed | -2048 to 2047 | Lines 689-695 |
| B-type | 13 bits signed | -4096 to 4094 | Lines 800-804 |
| J-type | 21 bits signed | -1048576 to 1048574 | Lines 895-899 |
| U-type | 20 bits | -524288 to 524287 | Lines 975-978 |

### Simulator Architecture

#### Memory Layout

The simulator implements a unified memory space of **327,681 bytes** (0x50001):

```
┌─────────────────────────────────────┐  0x00000
│        Text Segment                 │
│    (Machine Code Instructions)      │
│                                     │
├─────────────────────────────────────┤  0x10000 (65536)
│        Data Segment                 │
│    (Global Variables)               │
│    - .dword (8 bytes)               │
│    - .word (4 bytes)                │
│    - .half (2 bytes)                │
│    - .byte (1 byte)                 │
├─────────────────────────────────────┤
│        Free Memory                  │
│                                     │
├─────────────────────────────────────┤
│        Stack (grows down)           │
│    (Function call frames)           │
└─────────────────────────────────────┘  0x50000 (327680)
```

**Memory Access**: Little-endian byte ordering

**Example**: Storing `0x12345678` at address `0x10000`
```
0x10000: 0x78
0x10001: 0x56
0x10002: 0x34
0x10003: 0x12
```

#### Register File Implementation

```cpp
unordered_map<string, int64_t> register_values;
```

- **64-bit registers** (`int64_t`) for RV64I compatibility
- **x0 (zero)** is hard-wired to 0 (enforced after every instruction)
- All registers initialized to 0 on program load

#### Instruction Execution Pipeline

The simulator uses a **decode-execute** model:

```cpp
// Instruction fetch
int instruction_address = PC;
vector<string> instruction = assembly_code[PC / 4];

// Decode and execute based on format
if (format[instruction[0]] == 'R') {
    step_R(instruction);
} else if (format[instruction[0]] == 'I') {
    step_I(instruction);
}
// ... etc for S, B, J, U formats

// Update PC
PC += 4;  // or branch target
```

#### Execution Functions

Each instruction format has dedicated execution logic:

1. **`step_R()`** (Lines 574-654): R-type arithmetic and logical operations
   - Implements: ADD, SUB, AND, OR, XOR, SLL, SRL, SRA
   - Handles unsigned right shift (SRL) with proper masking
   - Arithmetic right shift (SRA) preserves sign bit

2. **`step_I()`** (Lines 657-868): I-type operations
   - **Load operations**: Byte/half-word/word/double-word loading with sign/zero extension
   - **Arithmetic**: Immediate arithmetic and logical operations
   - **JALR**: Indirect jump with return address storage

3. **`step_S()`** (Lines 871-947): Store operations
   - Stores byte/half/word/double-word to memory
   - Implements little-endian byte ordering
   - Memory address calculation: `base + offset`

4. **`step_B()`** (Lines 999-1104): Branch operations
   - Conditional branches: BEQ, BNE, BLT, BGE, BLTU, BGEU
   - PC-relative addressing
   - Signed/unsigned comparisons

5. **`step_J()`** (Lines 1107-1148): Jump and link
   - Saves return address (PC+4) to `rd`
   - Updates PC to target
   - Updates function call stack

6. **`step_U()`** (Lines 950-996): Upper immediate
   - Loads 20-bit immediate into upper 20 bits of register
   - Supports both decimal and hexadecimal immediate values

#### Data Segment Handling

The simulator supports `.data` directives for initializing memory:

```cpp
int store_dword(vector<string> instruction, int mem_loc)  // 8 bytes
int store_word(vector<string> instruction, int mem_loc)   // 4 bytes
int store_half(vector<string> instruction, int mem_loc)   // 2 bytes
int store_byte(vector<string> instruction, int mem_loc)   // 1 byte
```

**Example**:
```assembly
.data
.dword 12345, 67890
.word 100
.half 50
.byte 10
```

This stores values starting at `0x10000` in little-endian format.

#### Binary Conversion Utilities

The simulator includes comprehensive number conversion functions:

```cpp
string hex_to_binary(string hex)              // Hex → Binary string
string binary_to_hex(string binary)           // Binary → Hex string
string decimal_to_binary(int decimal, int bits, bool isSigned)
int binary_to_decimal(const string &bin)      // Binary → Decimal
```

These handle:
- **Two's complement** representation for negative numbers
- **Sign extension** for signed values
- **Variable bit-width** encoding

#### Program Counter (PC) Management

- **Initialization**: PC = 0x00000 (start of text segment)
- **Sequential execution**: PC += 4 after each instruction
- **Branches**: PC = current_PC + offset (if condition true)
- **Jumps**: PC = target_address
- **Display format**: Hexadecimal with 0x prefix

#### Stack Frame Tracking

```cpp
stack<pair<string, int>> stack_of_functions;
```

- Tracks function calls and their execution
- Pushes new frame on `jal` instruction
- Pops frame on `jalr` (function return)
- Records last executed line per function

**Stack Display Format**:
```
Call Stack:
main:5
factorial:12
helper:3
```

---

## 📚 Instruction Set Support

### R-Type Instructions (Register-Register)

| Instruction | Opcode | Funct3 | Funct7 | Operation | Line (Assembler) | Line (Simulator) |
|-------------|--------|--------|--------|-----------|------------------|------------------|
| `add rd, rs1, rs2` | 0110011 | 000 | 0000000 | rd = rs1 + rs2 | 178-181 | 584-586 |
| `sub rd, rs1, rs2` | 0110011 | 000 | 0100000 | rd = rs1 - rs2 | 182-185 | 587-590 |
| `and rd, rs1, rs2` | 0110011 | 111 | 0000000 | rd = rs1 & rs2 | 186-189 | 591-594 |
| `or rd, rs1, rs2` | 0110011 | 110 | 0000000 | rd = rs1 \| rs2 | 190-193 | 595-598 |
| `xor rd, rs1, rs2` | 0110011 | 100 | 0000000 | rd = rs1 ^ rs2 | 194-198 | 599-602 |
| `sll rd, rs1, rs2` | 0110011 | 001 | 0000000 | rd = rs1 << rs2 | 199-202 | 603-606 |
| `srl rd, rs1, rs2` | 0110011 | 101 | 0000000 | rd = rs1 >> rs2 (logical) | 203-206 | 607-624 |
| `sra rd, rs1, rs2` | 0110011 | 101 | 0100000 | rd = rs1 >> rs2 (arithmetic) | 207-210 | 626-629 |

**Implementation Notes**:
- **SRL** (Logical Right Shift): Uses masking to ensure zero-fill from left
- **SRA** (Arithmetic Right Shift): Preserves sign bit during shift

### I-Type Instructions (Immediate)

#### Arithmetic & Logical

| Instruction | Opcode | Funct3 | Operation | Range | Line (Assembler) | Line (Simulator) |
|-------------|--------|--------|-----------|-------|------------------|------------------|
| `addi rd, rs1, imm` | 0010011 | 000 | rd = rs1 + imm | [-2048, 2047] | 460-463 | 764-767 |
| `xori rd, rs1, imm` | 0010011 | 100 | rd = rs1 ^ imm | [-2048, 2047] | 464-467 | 768-771 |
| `ori rd, rs1, imm` | 0010011 | 110 | rd = rs1 \| imm | [-2048, 2047] | 468-471 | 772-775 |
| `andi rd, rs1, imm` | 0010011 | 111 | rd = rs1 & imm | [-2048, 2047] | 472-475 | 776-779 |
| `slli rd, rs1, imm` | 0010011 | 001 | rd = rs1 << imm | [0, 63] | 316-320 | 780-783 |
| `srli rd, rs1, imm` | 0010011 | 101 | rd = rs1 >> imm (logical) | [0, 63] | 321-325 | 784-802 |
| `srai rd, rs1, imm` | 0010011 | 101 | rd = rs1 >> imm (arithmetic) | [0, 63] | 326-330 | 803-806 |

#### Load Instructions

| Instruction | Opcode | Funct3 | Operation | Line (Assembler) | Line (Simulator) |
|-------------|--------|--------|-----------|------------------|------------------|
| `lb rd, imm(rs1)` | 0000011 | 000 | rd = SignExtend(Mem[rs1+imm][7:0]) | 583-586 | 672-678 |
| `lh rd, imm(rs1)` | 0000011 | 001 | rd = SignExtend(Mem[rs1+imm][15:0]) | 587-590 | 680-686 |
| `lw rd, imm(rs1)` | 0000011 | 010 | rd = SignExtend(Mem[rs1+imm][31:0]) | 591-594 | 688-697 |
| `ld rd, imm(rs1)` | 0000011 | 011 | rd = Mem[rs1+imm][63:0] | 595-598 | 699-708 |
| `lbu rd, imm(rs1)` | 0000011 | 100 | rd = ZeroExtend(Mem[rs1+imm][7:0]) | 599-602 | 709-714 |
| `lhu rd, imm(rs1)` | 0000011 | 101 | rd = ZeroExtend(Mem[rs1+imm][15:0]) | 603-606 | 715-721 |
| `lwu rd, imm(rs1)` | 0000011 | 110 | rd = ZeroExtend(Mem[rs1+imm][31:0]) | 607-611 | 722-731 |

**Load Implementation Details**:
- Little-endian byte ordering
- Sign extension for `lb`, `lh`, `lw`
- Zero extension for `lbu`, `lhu`, `lwu`
- 64-bit load (`ld`) reads 8 consecutive bytes

#### Jump and Link Register

| Instruction | Opcode | Funct3 | Operation | Line (Assembler) | Line (Simulator) |
|-------------|--------|--------|-----------|------------------|------------------|
| `jalr rd, imm(rs1)` | 1100111 | 000 | rd = PC+4; PC = rs1+imm | 476-480 | 832-864 |

### S-Type Instructions (Store)

| Instruction | Opcode | Funct3 | Operation | Line (Assembler) | Line (Simulator) |
|-------------|--------|--------|-----------|------------------|------------------|
| `sb rs2, imm(rs1)` | 0100011 | 000 | Mem[rs1+imm][7:0] = rs2[7:0] | 714-717 | 885-889 |
| `sh rs2, imm(rs1)` | 0100011 | 001 | Mem[rs1+imm][15:0] = rs2[15:0] | 710-713 | 890-898 |
| `sw rs2, imm(rs1)` | 0100011 | 010 | Mem[rs1+imm][31:0] = rs2[31:0] | 706-709 | 899-910 |
| `sd rs2, imm(rs1)` | 0100011 | 011 | Mem[rs1+imm][63:0] = rs2[63:0] | 702-705 | 911-922 |

**Store Implementation**:
- Little-endian byte ordering
- Proper byte decomposition for multi-byte stores

### B-Type Instructions (Branch)

| Instruction | Opcode | Funct3 | Condition | Line (Assembler) | Line (Simulator) |
|-------------|--------|--------|-----------|------------------|------------------|
| `beq rs1, rs2, label` | 1100011 | 000 | rs1 == rs2 | 808-811 | 1013-1023 |
| `bne rs1, rs2, label` | 1100011 | 001 | rs1 != rs2 | 812-815 | 1024-1034 |
| `blt rs1, rs2, label` | 1100011 | 100 | rs1 < rs2 (signed) | 816-819 | 1035-1045 |
| `bge rs1, rs2, label` | 1100011 | 101 | rs1 >= rs2 (signed) | 820-823 | 1046-1056 |
| `bltu rs1, rs2, label` | 1100011 | 110 | rs1 < rs2 (unsigned) | 824-827 | 1069-1080 |
| `bgeu rs1, rs2, label` | 1100011 | 111 | rs1 >= rs2 (unsigned) | 828-831 | 1057-1068 |

**Branch Offset Calculation**:
- PC-relative addressing
- Offset = (target_line - current_line) * 4
- Range: [-4096, 4094] bytes

### J-Type Instructions (Jump)

| Instruction | Opcode | Operation | Range | Line (Assembler) | Line (Simulator) |
|-------------|--------|-----------|-------|------------------|------------------|
| `jal rd, label` | 1101111 | rd = PC+4; PC = PC+offset | [-1048576, 1048574] | 851-923 | 1107-1148 |

**Jump Implementation**:
- Saves return address (PC+4) to `rd`
- Updates call stack with new function frame
- Commonly used for function calls: `jal ra, function_name`

### U-Type Instructions (Upper Immediate)

| Instruction | Opcode | Operation | Range | Line (Assembler) | Line (Simulator) |
|-------------|--------|-----------|-------|------------------|------------------|
| `lui rd, imm` | 0110111 | rd = imm << 12 | [0, 1048575] | 925-1001 | 950-996 |

**LUI Usage**:
- Loads 20-bit immediate into upper 20 bits of register
- Lower 12 bits are zeroed
- Commonly paired with `addi` for loading 32-bit constants
- Supports hexadecimal input: `lui x3, 0x10000`

---

## 💾 Memory Model

### Memory Organization

```
Address Range  │  Segment      │  Purpose                    │  Access
───────────────┼───────────────┼─────────────────────────────┼──────────
0x00000 -      │  Text         │  Machine code instructions  │  Read/Execute
0x0FFFF        │  Segment      │  (64KB)                     │
───────────────┼───────────────┼─────────────────────────────┼──────────
0x10000 -      │  Data         │  Global variables           │  Read/Write
0x4FFFF        │  Segment      │  .dword, .word, .half, .byte│
               │               │  (256KB)                    │
───────────────┼───────────────┼─────────────────────────────┼──────────
0x50000        │  End of       │  Memory boundary            │  N/A
               │  Memory       │                             │
```

### Data Types & Storage

| Directive | Size | Alignment | Example | Memory Layout (Little-Endian) |
|-----------|------|-----------|---------|-------------------------------|
| `.byte` | 1 byte | 1 | `.byte 0x12` | `[0x12]` |
| `.half` | 2 bytes | 2 | `.half 0x1234` | `[0x34, 0x12]` |
| `.word` | 4 bytes | 4 | `.word 0x12345678` | `[0x78, 0x56, 0x34, 0x12]` |
| `.dword` | 8 bytes | 8 | `.dword 0x123456789ABCDEF0` | `[0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12]` |

### Little-Endian Byte Ordering

The simulator uses **little-endian** format where the least significant byte is stored at the lowest address.

**Example**: Storing `0xDEADBEEF` at address `0x10000`

```
Memory Address  │  Value (Hex)  │  Value (Decimal)
────────────────┼───────────────┼──────────────────
0x10000         │  0xEF         │  239
0x10001         │  0xBE         │  190
0x10002         │  0xAD         │  173
0x10003         │  0xDE         │  222
```

### Memory Access Instructions

#### Load Operations (with Sign/Zero Extension)

```assembly
# Assuming memory at 0x10000 contains: EF BE AD DE

lb x1, 0(x3)    # x1 = 0xFFFFFFFFFFFFFFEF (sign-extended)
lbu x2, 0(x3)   # x2 = 0x00000000000000EF (zero-extended)
lh x3, 0(x3)    # x3 = 0xFFFFFFFFFFFFBEEF (sign-extended)
lhu x4, 0(x3)   # x4 = 0x000000000000BEEF (zero-extended)
```

#### Store Operations

```assembly
# Store different sizes
li x1, 0x123456789ABCDEF0

sb x1, 0(x3)    # Stores: F0
sh x1, 0(x3)    # Stores: F0 DE
sw x1, 0(x3)    # Stores: F0 DE BC 9A
sd x1, 0(x3)    # Stores: F0 DE BC 9A 78 56 34 12
```

---

## 📖 Examples

### Example 1: Simple Arithmetic

```assembly
.data
.dword 100, 200

.text
    lui x3, 0x10000      # Load data segment base address
    ld x1, 0(x3)         # Load first value (100) into x1
    ld x2, 8(x3)         # Load second value (200) into x2
    add x4, x1, x2       # x4 = x1 + x2 = 300
    sub x5, x2, x1       # x5 = x2 - x1 = 100
    and x6, x1, x2       # x6 = x1 & x2 (bitwise AND)
```

**Execution**:
```bash
load example1.s
step    # Execute lui
step    # Execute ld x1
step    # Execute ld x2
step    # Execute add
regs    # View results
```

**Expected Register Values**:
- `x1 = 0x0000000000000064` (100 in hex)
- `x2 = 0x00000000000000C8` (200 in hex)
- `x4 = 0x000000000000012C` (300 in hex)
- `x5 = 0x0000000000000064` (100 in hex)

### Example 2: Conditional Branching

```assembly
.text
    addi x1, x0, 10      # x1 = 10
    addi x2, x0, 20      # x2 = 20
    beq x1, x2, equal    # Branch if x1 == x2 (not taken)
    blt x1, x2, less     # Branch if x1 < x2 (taken)
    addi x3, x0, 999     # Skipped
equal:
    addi x4, x0, 1       # Skipped
less:
    addi x5, x0, 1       # Executed: x5 = 1
```

**Trace**:
```
PC=0x00000: addi x1, x0, 10     → x1 = 10
PC=0x00004: addi x2, x0, 20     → x2 = 20
PC=0x00008: beq x1, x2, equal   → Not taken (10 != 20)
PC=0x0000C: blt x1, x2, less    → Taken (10 < 20), PC → 0x00014
PC=0x00014: addi x5, x0, 1      → x5 = 1
```

### Example 3: Function Call with Stack

```assembly
.text
main:
    addi x1, x0, 5       # Argument: x1 = 5
    jal ra, square       # Call function, ra = return address
    addi x3, x2, 0       # x3 = result (x2)
    # Program continues...

square:
    mul x2, x1, x1       # x2 = x1 * x1 = 25
    jalr x0, 0(ra)       # Return to caller (PC = ra + 0)
```

**Call Stack Visualization**:
```
# Before jal
Stack: [main:1]

# After jal
Stack: [main:2, square:0]

# After jalr
Stack: [main:3]
```

### Example 4: Memory Operations

```assembly
.data
.dword 0x123456789ABCDEF0
.word 0xDEADBEEF
.half 0xCAFE
.byte 0xAB

.text
    lui x3, 0x10000      # Data segment base

    # Load operations
    ld x1, 0(x3)         # Load dword
    lw x2, 8(x3)         # Load word (sign-extended)
    lwu x3, 8(x3)        # Load word (zero-extended)
    lh x4, 12(x3)        # Load half
    lb x5, 14(x3)        # Load byte

    # Store operations
    addi x6, x0, 0x10020 # New address
    sd x1, 0(x6)         # Store dword
    sw x2, 8(x6)         # Store word
```

### Example 5: Bitwise Operations

```assembly
.text
    addi x1, x0, 0xFF    # x1 = 0b11111111
    addi x2, x0, 0xF0    # x2 = 0b11110000

    and x3, x1, x2       # x3 = 0xF0 (0b11110000)
    or x4, x1, x2        # x4 = 0xFF (0b11111111)
    xor x5, x1, x2       # x5 = 0x0F (0b00001111)

    slli x6, x1, 4       # x6 = 0xFF0 (shift left by 4)
    srli x7, x2, 4       # x7 = 0x0F (logical shift right)

    # NOT operation using xor with -1
    addi x8, x0, -1      # x8 = 0xFFFFFFFFFFFFFFFF
    xor x9, x1, x8       # x9 = ~x1
```

---

## 🐛 Debugging Features

### Breakpoints

Set execution breakpoints at specific line numbers:

```bash
# Set breakpoint at line 10
break 10

# Run until breakpoint
run
# Output: Execution stopped at breakpoint

# Continue stepping
step

# Remove breakpoint
del break 10
```

**Implementation Details**:
- Breakpoints stored in `unordered_set<int> break_lines`
- Line numbers adjusted for `.data` section offset
- Execution pauses **before** executing the breakpoint line

### Single-Step Execution

Execute one instruction at a time with full visibility:

```bash
step
# Output: Executed: add x1, x2, x3; PC=0x00000004
```

**Step Output Format**:
- Displays executed instruction (without label prefix)
- Shows PC value **before** execution
- Updates register/memory state
- Advances PC to next instruction

### Register Inspection

View all 32 register values in hexadecimal:

```bash
regs
```

**Output Format**:
```
Registers:
x0  = 0x0
x1  = 0x64
x2  = 0xc8
x3  = 0x10000
...
x31 = 0x0
```

**Features**:
- 64-bit hexadecimal display
- Zero-padded to 16 hex digits
- Trimmed leading zeros for readability

### Memory Inspection

View memory contents with address and value pairs:

```bash
mem 0x10000 16
```

**Output Format**:
```
Memory[0x10000] = 0x64
Memory[0x10001] = 0x00
Memory[0x10002] = 0x00
...
Memory[0x1000F] = 0x00
```

**Parameters**:
- `<addr>`: Starting address (hexadecimal with 0x prefix)
- `<count>`: Number of bytes to display

### Call Stack Visualization

Track function call hierarchy:

```bash
show-stack
```

**Output Format**:
```
Call Stack:
main:5
factorial:12
helper:3
```

**Stack Information**:
- Function name and last executed line
- Bottom-to-top display (main at top)
- Automatic updates on `jal` (push) and `jalr` (pop)
- Line numbers adjusted for `.data` section

---

## ⚠️ Error Handling

### Assembler Error Detection

The assembler provides comprehensive error checking:

#### 1. Register Errors

```assembly
add x1, x32, x2    # Error: Register out of range
add x1, foo, x2    # Error: Incorrect Register name
```

**Error Message**:
```
Error in line 5: Register out of range: x32
Error in line 6: Incorrect Register name: foo
```

**Detection**: Lines 97-110 (assembler)

#### 2. Immediate Range Errors

```assembly
addi x1, x2, 5000   # Error: Immediate value out of range (max 2047)
slli x3, x4, 100    # Error: Immediate value out of range (max 63)
```

**Error Message**:
```
Error in line 3: Immediate value out of range
```

**Range Validation**:
- I-type arithmetic: [-2048, 2047]
- I-type shift: [0, 63]
- S-type: [-2048, 2047]
- B-type: [-4096, 4094]
- J-type: [-1048576, 1048574]
- U-type: [0, 1048575]

#### 3. Operand Count Errors

```assembly
add x1, x2          # Error: Missing operand
add x1, x2, x3, x4  # Error: Too many operands
```

**Error Message**:
```
Error in line 4: Incorrect number of operands
```

**Detection**: Each format function validates operand count

#### 4. Label Errors

```assembly
beq x1, x2, undefined_label   # Error: Label not defined

loop:
    addi x1, x1, 1
loop:                          # Error: Duplicate label
    addi x2, x2, 1
```

**Error Messages**:
```
Error in line 5: Incorrect label specified
Error in line 8: Same label found twice
```

#### 5. Invalid Instruction Errors

```assembly
multiply x1, x2, x3   # Error: Invalid instruction
```

**Error Message**:
```
Error in line 2: Incorrect instruction entered
```

### Simulator Error Detection

#### 1. File Loading Errors

```cpp
load nonexistent.s
```

**Error**: File not found (assembler/simulator reports error)

#### 2. Execution Boundary Errors

```bash
step   # When PC has reached end of program
```

**Output**:
```
Nothing to step
```

#### 3. Memory Access Errors

While not explicitly bounds-checked in current implementation, accessing memory beyond 0x50000 results in undefined behavior.

---

## 🔬 Advanced Topics

### Two's Complement Representation

The simulator uses **two's complement** for signed integers:

**Conversion Process** (Lines 149-201):

```cpp
string decimal_to_binary(int decimal, int no_of_bits, bool isSigned) {
    // 1. Convert absolute value to binary
    // 2. If negative and signed:
    //    a. Take 1's complement (flip all bits)
    //    b. Add 1 (2's complement)
}
```

**Example**: -5 in 8 bits
```
Decimal: -5
Binary (5): 00000101
1's complement: 11111010
2's complement: 11111011  ← Final representation
```

### Logical vs. Arithmetic Right Shift

**Logical Right Shift (SRL/SRLI)**:
- Fills with zeros from the left
- Used for unsigned division by powers of 2
- Implementation (Lines 607-624):

```cpp
uint64_t mask = (1U << (64 - shifting_amount)) - 1;
register_values[rd] = register_values[rd] & mask;
```

**Arithmetic Right Shift (SRA/SRAI)**:
- Preserves sign bit (sign extension)
- Used for signed division by powers of 2
- Implementation (Lines 626-629):

```cpp
register_values[rd] = register_values[rs1] >> register_values[rs2];
// C++ >> operator on signed types performs arithmetic shift
```

**Example**:
```
Value: 0x8000000000000004 (-9223372036854775804 in signed)
SRL 1: 0x4000000000000002 (logical: zero-fill)
SRA 1: 0xC000000000000002 (arithmetic: sign-extend)
```

### Instruction Encoding Format Details

#### R-Type Format (32 bits)

```
┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
│ funct7  │   rs2   │   rs1   │ funct3  │   rd    │ opcode  │
│ [31:25] │ [24:20] │ [19:15] │ [14:12] │ [11:7]  │  [6:0]  │
│ 7 bits  │ 5 bits  │ 5 bits  │ 3 bits  │ 5 bits  │ 7 bits  │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
```

**Example**: `add x1, x2, x3`
```
funct7  = 0000000
rs2     = 00011 (x3)
rs1     = 00010 (x2)
funct3  = 000
rd      = 00001 (x1)
opcode  = 0110011

Binary: 0000000 00011 00010 000 00001 0110011
Hex:    0x003100B3
```

#### I-Type Format (32 bits)

```
┌──────────────────┬─────────┬─────────┬─────────┬─────────┐
│   imm[11:0]      │   rs1   │ funct3  │   rd    │ opcode  │
│     [31:20]      │ [19:15] │ [14:12] │ [11:7]  │  [6:0]  │
│    12 bits       │ 5 bits  │ 3 bits  │ 5 bits  │ 7 bits  │
└──────────────────┴─────────┴─────────┴─────────┴─────────┘
```

**Example**: `addi x1, x2, 100`
```
imm     = 000001100100 (100 in binary)
rs1     = 00010 (x2)
funct3  = 000
rd      = 00001 (x1)
opcode  = 0010011

Binary: 000001100100 00010 000 00001 0010011
Hex:    0x06410093
```

#### S-Type Format (32 bits)

```
┌──────────┬─────────┬─────────┬─────────┬──────────┬─────────┐
│ imm[11:5]│   rs2   │   rs1   │ funct3  │ imm[4:0] │ opcode  │
│  [31:25] │ [24:20] │ [19:15] │ [14:12] │  [11:7]  │  [6:0]  │
│  7 bits  │ 5 bits  │ 5 bits  │ 3 bits  │  5 bits  │ 7 bits  │
└──────────┴─────────┴─────────┴─────────┴──────────┴─────────┘
```

**Note**: Immediate is split into two parts (imm[11:5] and imm[4:0])

#### B-Type Format (32 bits)

```
┌───┬──────────┬─────────┬─────────┬─────────┬──────────┬───┬─────────┐
│imm│ imm[10:5]│   rs2   │   rs1   │ funct3  │ imm[4:1] │imm│ opcode  │
│[12]│  [31:25] │ [24:20] │ [19:15] │ [14:12] │  [11:8]  │[11]│  [6:0]  │
│ 1 │  6 bits  │ 5 bits  │ 5 bits  │ 3 bits  │  4 bits  │ 1 │ 7 bits  │
└───┴──────────┴─────────┴─────────┴─────────┴──────────┴───┴─────────┘
```

**Note**: Immediate encoding: `imm[12|10:5|4:1|11]` (LSB imm[0] is implicit 0)

#### J-Type Format (32 bits)

```
┌───┬──────────┬───┬──────────┬─────────┬─────────┐
│imm│ imm[19:12]│imm│ imm[10:1]│   rd    │ opcode  │
│[20]│  [31:12] │[11]│ [30:21]  │ [11:7]  │  [6:0]  │
│ 1 │  8 bits  │ 1 │  10 bits │ 5 bits  │ 7 bits  │
└───┴──────────┴───┴──────────┴─────────┴─────────┘
```

**Note**: Immediate encoding: `imm[20|10:1|11|19:12]` (LSB imm[0] is implicit 0)

#### U-Type Format (32 bits)

```
┌──────────────────────────┬─────────┬─────────┐
│      imm[31:12]          │   rd    │ opcode  │
│        [31:12]           │ [11:7]  │  [6:0]  │
│        20 bits           │ 5 bits  │ 7 bits  │
└──────────────────────────┴─────────┴─────────┘
```

**Example**: `lui x3, 0x10000`
```
imm     = 00010000000000000000 (0x10000)
rd      = 00011 (x3)
opcode  = 0110111

Binary: 00010000000000000000 00011 0110111
Hex:    0x100001B7
```

---

## 📊 Performance Considerations

### Time Complexity

| Operation | Complexity | Notes |
|-----------|------------|-------|
| Assembly (Pass 1) | O(n) | n = number of lines |
| Assembly (Pass 2) | O(n) | Single scan with label lookup |
| Simulation (step) | O(1) | Direct instruction execution |
| Register lookup | O(1) | Hash map access |
| Memory access | O(1) | Array indexing |
| Label resolution | O(1) | Hash map lookup |

### Space Complexity

| Component | Size | Notes |
|-----------|------|-------|
| Memory array | 327,681 bytes | Fixed size (0x50001) |
| Register file | 32 × 8 bytes = 256 bytes | 64-bit registers |
| Symbol table | O(l) | l = number of labels |
| Instruction storage | O(n × m) | n instructions, m avg length |

### Optimization Opportunities

1. **Instruction Caching**: Pre-decode instructions to avoid repeated string parsing
2. **Memory Segmentation**: Use separate arrays for text/data/stack segments
3. **Register Array**: Use fixed array instead of hash map for faster access
4. **Binary Instruction Storage**: Store instructions as 32-bit integers, not strings

---

## 🧪 Testing

### Test Coverage

The project includes comprehensive test cases for all instruction types:

| Test File | Instructions Tested | Focus Area |
|-----------|---------------------|------------|
| `testcase-R.s` | R-type | Arithmetic, logical, shift operations |
| `testcase-I.s` | I-type | Immediate operations, loads |
| `testcase-S.s` | S-type | Store operations (byte, half, word, dword) |
| `testcase-BJU.s` | B, J, U-types | Branches, jumps, upper immediate |

### Running Tests

```bash
# Assembler tests
cd Assembler
./assembler
# Check output.hex for correctness

# Simulator tests
cd Simulator
./riscv_sim
load ../Assembler/testcase-R.s
run
regs
```

### Validation Methodology

1. **Instruction Encoding**: Compare generated hex with RISC-V ISA manual
2. **Register Values**: Verify arithmetic/logical operation results
3. **Memory Contents**: Check little-endian storage correctness
4. **Control Flow**: Trace branch/jump PC updates
5. **Stack Operations**: Verify function call/return stack frames

---

## 🚀 Future Enhancements

Potential improvements for the project:

### Assembler Enhancements
- [ ] Command-line argument for input file selection
- [ ] Support for pseudo-instructions (`li`, `mv`, `nop`, etc.)
- [ ] Macro definitions and expansion
- [ ] Multiple input file linking
- [ ] Symbol table export for debugging

### Simulator Enhancements
- [ ] **M Extension**: Multiplication and division instructions
- [ ] **F/D Extensions**: Floating-point support
- [ ] **Pipeline Simulation**: Multi-stage pipeline with hazard detection
- [ ] **Cache Simulation**: L1/L2 cache modeling
- [ ] **Performance Counters**: Instruction count, cycle count, CPI
- [ ] **System Calls**: Support for `ecall` instruction
- [ ] **GUI Interface**: Graphical debugger with visualization
- [ ] **Watchpoints**: Break on memory/register changes
- [ ] **Reverse Execution**: Step backward through execution

### Code Quality
- [ ] Comprehensive unit tests
- [ ] Continuous integration setup
- [ ] Code refactoring for modularity
- [ ] Doxygen documentation
- [ ] Address all compiler warnings

---

## 📚 References

### RISC-V Specifications
- [RISC-V ISA Manual (Volume I: Unprivileged ISA)](https://riscv.org/technical/specifications/)
- [RISC-V Assembly Programmer's Manual](https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md)
- [RISC-V Instruction Set Listing](https://rv8.io/isa)

### Learning Resources
- [RISC-V Green Card](https://www.cl.cam.ac.uk/teaching/1617/ECAD+Arch/files/docs/RISCVGreenCardv8-20151013.pdf)
- [Computer Organization and Design RISC-V Edition](https://www.amazon.com/Computer-Organization-Design-RISC-V-Architecture/dp/0128122757)

---

## 👥 Authors

### Project Team

**Ahmik Virani**
- Roll Number: ES22BTECH11001
- Institution: IIT Hyderabad
- Contribution: Simulator implementation, debugging features, memory management

**Divya Rajparia**
- Roll Number: ES22BTECH11013
- Institution: IIT Hyderabad
- Contribution: Assembler implementation, instruction encoding, error handling

### Course Information

- **Course**: CS2323 - Computer Architecture
- **Lab**: Lab 3 (Assembler) & Lab 4 (Simulator)
- **Institution**: Indian Institute of Technology Hyderabad
- **Academic Year**: 2022-2023

---

## 📄 License

This project is an academic assignment completed as part of the Computer Architecture course at IIT Hyderabad. It is provided for educational purposes.

---

## 🙏 Acknowledgments

- **RISC-V Foundation** for the open ISA specification
- **Course Instructors** for guidance and problem statements
- **Teaching Assistants** for testing and feedback

---

## 📞 Support & Contact

For questions, issues, or contributions related to this project:

- **Report Issues**: Use the project issue tracker
- **Academic Queries**: Contact the course instructor
- **Documentation**: Refer to the technical reports in `Assembler/` and `Simulator/` directories

---

<div align="center">

### Built with 💻 for Computer Architecture (CS2323)

**IIT Hyderabad | 2022-2023**

---

*Last Updated: January 2025*

</div>
