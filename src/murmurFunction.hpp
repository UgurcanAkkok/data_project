#ifndef MURMUR3_HASH_FUNCTION_HPP
#define MURMUR3_HASH_FUNCTION_HPP

#if defined (_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

#else // Other than Visual Studio

#include <stdint.h>

#endif 
void murmur(const void* key, int len, uint32_t seed, uint64_t out[2]);

#endif
