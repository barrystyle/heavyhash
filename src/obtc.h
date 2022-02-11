#ifndef OBTC_H
#define OBTC_H

#include <uint256.h>

bool Is4BitPrecision(const uint64_t matrix[64*64]);
bool IsFullRank(const uint64_t matrix_[64*64]);
void GenerateHeavyHashMatrix(uint256 matrix_seed, uint64_t matrix[64*64]);
void serialize_heavyhash(uint64_t matrix[64*64], const char* in, char* out, int len);
void opticalbtc_hash(const char* in, char* out, int len);

#endif // OBTC_H
