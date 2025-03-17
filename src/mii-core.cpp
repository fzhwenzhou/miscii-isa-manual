#include "ac_int.h"

// Define WLEN, by default 32 bit
const int WLEN = 32;

void mii_core(char* mem) {
    ac_int<WLEN, false> register_stack[8]{};
    ac_int<3, false> register_ptr{};

    ac_int<WLEN, false> pc{};
}