## Problem Statement:
To develop a two-pass macro processor designed to efficiently process assembly-like code. The primary challenge is to create a functional one-pass macro processor capable of identifying and storing macros during the initial pass, followed by their dynamic expansion in a second pass.

## Objectives:
- Accurate Macro Identification and Storage.
- Effective File Handling and Error Management.
- Dynamic Macro Expansion

## Algorithm Design

### 2.1 Macro Identification and Storage (pass 1):
During the first pass, the algorithm identifies macros within the input code and stores relevant information in the `macro.txt` file. The algorithm follows these steps:

**Algorithm Steps:**
- Scan each line of the input file (`input.txt`) using `fscanf`.
- Identify lines containing the `MACRO` opcode.
- Extract and store macro information (label, opcode, operand) until encountering the `MEND` opcode.
- Write the extracted macro information to the `macro.txt` file using `fprintf`.

**Data Structures:**
- Character arrays (label, opcode, operand) are used to temporarily store macro information.
- File pointers (`f1` and `f2`) facilitate reading from and writing to files.

### 2.2 Macro Expansion (pass 2):
The second pass involves expanding macros in the input code based on the information stored in `macro.txt`. The algorithm ensures dynamic incorporation of macro details into the output file (`output.txt`). The algorithm follows these steps:

**Algorithm Steps:**
- Reopen `macro.txt` for reading (`f2 = fopen("macro.txt", "r")`) to access stored macros.
- Scan each line of the input file again, identifying lines containing the specified macro label.
- Replace the macro label in the input code with the corresponding macro information from `macro.txt`.
- Write the expanded code to the output file (`output.txt`) using `fprintf`.

**Data Structures:**
- Character arrays (label1, opcode1, operand1) temporarily store macro details during expansion.
- File pointers (`f1`, `f2`, `f3`) enable reading from and writing to files.
