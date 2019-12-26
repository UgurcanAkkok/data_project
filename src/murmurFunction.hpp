#ifndef MURMUR3_HASH_FUNCTION_HPP
#define MURMUR3_HASH_FUNCTION_HPP

#include <stdint.h>

void murmur(const void* key, int len, uint32_t seed, uint64_t out[2]);

#endif
