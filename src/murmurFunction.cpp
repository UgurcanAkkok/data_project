#include "murmurFunction.hpp"

#if defined (_MSC_VER)

#define ALWAYS_INLINE __forceinline

#include <stdlib.h>

#define ROTATE(x,y) _rotl64(x,y)
#define LARGE_CONST(x) (x)

#else

#define ALWAYS_INLINE inline __attribute__((always_inline))

inline uint64_t rotate(uint64_t n, int8_t d){
    return (n << d) | (n >> (64 - d));
}

#define ROTATE(x,y) rotate(x,y)
#define LARGE_CONST(x) (x##LLU)

#endif

ALWAYS_INLINE uint64_t getpart(const uint64_t * whole, int index){
    return whole[index];
}

// Mix the bits
// Forcing avalanche effect
ALWAYS_INLINE uint64_t mix(uint64_t a){
    a ^= a >> 33;
    a *= LARGE_CONST(0xff51afd7ed558ccd);
    a ^= a >> 33;
    a *= LARGE_CONST(0xc4ceb9fe1a85ec53);
    a ^= a >> 33;

    return a;
}

void murmur(const void *key, int len, uint32_t seed, uint64_t output[2]){

    const uint8_t * bytes = (const uint8_t *) key;
    const int blocksLen = len / 16;

    uint64_t hash1 = seed;
    uint64_t hash2 = seed;

    const uint64_t const1 = LARGE_CONST(0x87c37b91114253d5);
    const uint64_t const2 = LARGE_CONST(0x4cf5ad432745937f);

    const uint64_t * blocks = (const uint64_t *) (bytes);

    for (int i = 0; i < blocksLen; i++){
        uint64_t part1 = getpart(blocks, i*2 + 0);
        uint64_t part2 = getpart(blocks, i*2 + 1);
 
        part1 *= const1; 
        part1 = ROTATE(part1, 31); 
        part1 *= const2;

        hash1 ^= part1;
        hash1 = ROTATE(hash1,27);
        hash1 += hash2; 
        hash1 = hash1 * 5 + 0x52dce729;

        part2 *= const2;
        part2 = ROTATE(part2,33); 
        part2 *= const1;

        hash2 ^= part2;
        hash2 = ROTATE(hash2, 31);
        hash2 += hash1;
        hash2 = hash2 * 5+ 0x38495ab5;
    }

    // Remaining bits
    const uint8_t * tail = (const uint8_t *)(bytes + blocksLen*16);
    uint64_t k1 = 0;
    uint64_t k2 = 0;

    switch(len & 15){
        case 15: k2 ^= ((uint64_t) tail[14]) << 48;
        case 14: k2 ^= ((uint64_t) tail[13]) << 40;
        case 13: k2 ^= ((uint64_t) tail[12]) << 32;
        case 12: k2 ^= ((uint64_t) tail[11]) << 24;
        case 11: k2 ^= ((uint64_t) tail[10]) << 16;
        case 10: k2 ^= ((uint64_t) tail[ 9]) <<  8;
        case  9: k2 ^= ((uint64_t) tail[ 8]) <<  0;
                 k2 *= const2; k2 = ROTATE(k2,33);
                 k2 *= const1; hash2 ^= k2;

        case  8: k1 ^= ((uint64_t) tail[ 7]) <<  56;
        case  7: k1 ^= ((uint64_t) tail[ 6]) <<  48;
        case  6: k1 ^= ((uint64_t) tail[ 5]) <<  40;
        case  5: k1 ^= ((uint64_t) tail[ 4]) <<  32;
        case  4: k1 ^= ((uint64_t) tail[ 3]) <<  24;
        case  3: k1 ^= ((uint64_t) tail[ 2]) <<  16;
        case  2: k1 ^= ((uint64_t) tail[ 1]) <<  8;
        case  1: k1 ^= ((uint64_t) tail[ 0]) <<  0;
                 k1 *= const1; k1 = ROTATE(k1,31);
                 k1 *= const2; hash1 ^= k1;
    }

    // Final operations
    hash1 ^= len;
    hash2 ^= len;

    hash1 += hash2;
    hash2 += hash1;

    hash1 = mix(hash1);
    hash2 = mix(hash2);

    hash1 += hash2;
    hash2 += hash1;

    output[0] = hash1;
    output[1] = hash2;

}
