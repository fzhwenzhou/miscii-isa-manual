# MISC-II Instruction Set Manual Volumn 1: Unprivileged
## Preface
MISC-II is an instruction set architecture that adopts MISC (Minimum Instruction Set Computer) strategy. It aims to be an ISA with minimum first-level instructions. It is a stack machine, so there is no ordinary register for the programmers to directly operate on. However, compared with existing MISC ISAs, this ISA tends to make a balance between conciseness and efficiency, enabling it to work better with non-embedded applications, like smartphones, PCs, and servers. 

## 1. Introduction

## 2. MII32I Base Integer Instruction Set
This chapter describes the MII32I base integer instruction set.

## 2.1 Programmers' Model for Basic Integer ISA
For MII32I, there is one general purpose register stack, one program counter register, and one memory stack pointer register. Each register is 32 bits wide, i.e., WLEN=32. The register stack contains 8 general purpose registers (named x0, x1 ... x15) acting as a stack, holding values that various instructions interpret as a collection of Boolean values, or as two’s complement signed binary integers, or unsigned binary integers. The program counter pc holds the address of the current instruction, and the memory stack pointer sp holds the address of the peak of the memory stack.

There is no dedicated subroutine return address link register. In the standard software calling convention, the return address should be pushed onto the register stack when calling.

## 2.2 Base Instruction Formats
In the Base MII32I ISA, there are three core instruction formats (O/S/I), as shown in Base instruction formats. All are a fixed 8 bits (1 byte) in length. The ISA does not force to align.    
```
|   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |

|   0   |   0       0   |                op[4:0]                | O-type

|   0   |    op[6:5]    |                imm[4:0]               | S-type

|   1   |                       imm[6:0]                        | I-type
```
## 2.3 Basic Integer Computational Instructions
All the integer computational instructions operate on WLEN bits of values held in the integer register stack. 
### 2.3.1 Load Integer Instruction
There is only one instruction belonging to this category: LI (Load integer). This is also the only instruction that uses I-type. This instruction will push a sign-extended 7-bits immediate number into the stack if the previous instruction is not LI, or shift left the peak of the stack by 7 bits and add the immediate number to it. if the number of consecutive LI instructions times 7 is less than WLEN, then the value pushed will be zero-extended.
### 2.3.2 Basic Integer Arithmetic Instruction

## 2.4 Control Transfer Instructions

## 2.5 Load and Store Instructions

## 2.6 Other Instructions


## 3. MII64I Base Integer Instruction Set
This chapter describes the MII64I base integer instruction set. The instruction set does not differ much from MII32I, except each register is 64 bits wide, i.e., WLEN=64. Also, it will not ensure backward compability with MII32I.