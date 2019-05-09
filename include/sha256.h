#ifndef __VZ_SHA__
#define __VZ_SHA__

#include <cstdio>      /* printf, scanf, NULL */
#include <cstdlib>     /* calloc, exit, free */
#include <cstring>     /* strlen, strcpy */
#include <cstdint>     /* uint32_t, uint64_t */
#include <climits>     /* CHAR_BIT */
#include <vector>      /* vector <> */
#include <string>      /* string */
#include <iostream>    /* cin, cout, new, delete*/

// Only for processors with the ror instruction
/* ********************************************
 * MOV IN, EAX
 * ROR BITS, EAX
 * MOV EAX, OUT
 * *********************************************/
/* #define RIGHTROTATE(in, bits) ({ uint32_t out; __asm__ __volatile__ ("\
    mov %1, %%eax;\n \
    ror %2, %%eax;\n \
    mov %%eax, %0;\n"\
    : "=r"(out) \
    : "r"(in), "c"((uint8_t)bits) \
    : "eax"); out;}) */

/* **********************************************************************************
 * ----------------------------------------------------------------------------------
 * CONSTANTS
 * ----------------------------------------------------------------------------------
 * **********************************************************************************/

namespace vzsha256
{
    // (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
    const uint32_t initial_values[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    const int initial_values_size = 8;
    // (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
    const uint32_t round_constants[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    /* **********************************************************************************
     * ----------------------------------------------------------------------------------
     *  FUNCTIONS
     * ----------------------------------------------------------------------------------
     * **********************************************************************************/

    // Function to right rotate number and return resultant 32 bit unsigned integer
    uint32_t right_rotate(const uint32_t& in, const int bits);

    // Function to swap from little endian number to big endian number
    uint32_t swap_uint32(uint32_t num);

    // Function to return the 256 bit hash of a piece of data
    void sha256(const std::string& data, std::vector<uint32_t>& hash_digest);
}
#endif
