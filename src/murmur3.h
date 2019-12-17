#pragma once
// MurmurHash3 hash function x64 architecture 128 bit implementation.

// Platform specific macros and functions, for
// MS-VS and Linux

#if defined (_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

#else // Other than Visual Studio

#include <stdint.h>

#endif 

void murmur(const void* key, int len, uint32_t seed, void* out);

