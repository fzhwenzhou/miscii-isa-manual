#include "ac_int.h"



// Define WLEN, by default 32 bit
#define WLEN 32


// Basic integer instruction set
// Define Opcodes
#define S_LSP 0b01
#define S_SSP 0b10
#define S_ASP 0b11

// Arithmetic and Logic
#define O_NOP 0b00000
#define O_ADD 0b00001
#define O_SUB 0b00010
#define O_AND 0b00011
#define O_OR  0b00100
#define O_XOR 0b00101

#define O_SLL 0b00110
#define O_SRL 0b00111
#define O_SRA 0b01000
#define O_SLT 0b01001
#define O_SLTU 0b01010
#define O_SGE 0b01011
#define O_SGEU 0b01100
#define O_SEQ 0b01101
#define O_SNE 0b01110

// Stack Operations
#define O_SWP 0b01111
#define O_DUP 0b10000

// Branch Operations
#define O_BT  0b10001
#define O_BF  0b10010
#define O_J   0b10011
#define O_JAL 0b10100

// Load-Store Operations
#define O_LB  0b10101
#define O_LH  0b10110
#define O_LW  0b10111


#define O_LBU 0b11000
#define O_LHU 0b11001

#define O_SB  0b11010
#define O_SH  0b11011
#define O_SW  0b11100

#define O_OPR 0b11101

#define O_SCALL 0b11110
#define O_BREAK 0b11111

// Second level instruction
#define OPR_FENCE 0b0000000
#define OPR_GPC   0b0000001
#define OPR_PPC   0b0000010
#define OPR_GSP   0b0000011
#define OPR_PSP   0b0000100

// Multiplication extension
#ifdef MII_MUL
#define OPR_MUL 0b0000101
#define OPR_MULH 0b0000110
#define OPR_MULHU 0b0000111
#endif

#ifdef MII_DIV
#define OPR_DIV 0b0001000
#define OPR_DIVU 0b0001001
#define OPR_MOD 0b0001010
#define OPR_MODU 0b0001011
#endif

#ifdef MII_ATOMIC

#endif

#ifdef MII_FLOAT

#endif

#ifdef MII_DOUBLE

#endif


// Vector table definition for error handling
#define EXCPT_ILLEGAL_INSTRUCTION 0
#define EXCPT_NO_SUFFICIENT_ELEMENT 1
#define EXCPT_OPR_NO_IMM 2

void exception(uint8 exception_number) {

}


void mii_core(char* mem) {
    /* PLACEHOLDER FOR PRAGMA TO ATTACH MEM TO AXI INTERFACE */

    ac_int<WLEN, false> register_stack[8]{};
    uint4 register_ptr{};
    ac_int<WLEN, false> imm_register{};

    ac_int<WLEN, false> pc{0x8000000}; // Starting address
    ac_int<WLEN, false> csr_excpt{}; // The default exception handler table base address
    uint1 csr_imm{};
    
    
    while (true) {
        // Fetch
        uint8 instr = mem[pc];
        
        // Decode
        auto bit7 = instr[7];
        auto op_s = instr.slc<2>(5);
        
        // Immediate
        auto imm_i = instr.slc<7>(0);
        auto imm_s = instr.slc<5>(0);
        auto &op_o = imm_s;

        // Execute
        if (bit7) { // is LI instruction
            if (csr_imm) {
                imm_register <<= 7;
                imm_register |= imm_i;
            }
            else {
                csr_imm = 1;
                imm_register = imm_i;
            }
        }
        else { // Other instruction
            if (op_s == 0 && op_o == O_OPR) {
                if (!csr_imm) {
                    exception(EXCPT_OPR_NO_IMM);
                }
            }
            else {
                if (csr_imm) {
                    if (register_ptr == 8) { // The stack is full, discard the last one
                        /* PLACEHOLDER FOR PRAGMA TO UNROLL LOOP */
                        for (int i = 0; i < 7; i++) {
                            register_stack[i] = register_stack[i + 1];
                        }
                        register_stack[register_ptr - 1] = imm_register;
                    }
                    else {
                        register_stack[register_ptr++] = imm_register;
                    }
                    csr_imm = 0;
                }
            }
        }
    }
}