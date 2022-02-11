//! heavyhash extracted from optical bitcoin
//! 2022 barrystyle

#include <stdint.h>
#include <stdlib.h>

#include <heavyhash.h>
#include <openssl/sha.h>
#include <uint256.h>
#include <xoshiro256pp.h>
#include <matrix-utils/singular/Svd.h>

bool Is4BitPrecision(const uint64_t matrix[64*64])
{
    for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 64; ++j) {
            if (matrix[ i*64 + j] > 0xF)
                return false;
        }
    }
    return true;
}

bool IsFullRank(const uint64_t matrix_[64*64])
{
    double matrix__ [64*64];
    singular::Matrix<64, 64> matrix;
    for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 64; ++j) {
            matrix__[64*i + j] = (double) matrix_[64*i + j];
        }
    }
    matrix.fill(matrix__);
    singular::Svd< 64, 64 >::USV usv = singular::Svd< 64, 64 >::decomposeUSV(matrix);
    const singular::DiagonalMatrix< 64, 64 >& singularValues = singular::Svd< 64, 64 >::getS(usv);
    return singular::Svd< 64, 64 >::isFullRank(singularValues, 64);
}

void GenerateHeavyHashMatrix(uint256 matrix_seed, uint64_t matrix[64*64])
{
    XoShiRo256PlusPlus generator(matrix_seed);
    do {
        for (int i = 0; i < 64; ++i) {
            for (int j = 0; j < 64; j += 16) {
                uint64_t value = generator();
                for (int shift = 0; shift < 16; ++shift) {
                    matrix[64*i + j + shift] =  (value >> (4 * shift)) & 0xF;
                }
            }
        }
    } while (!Is4BitPrecision(matrix) || !IsFullRank(matrix));
}

void serialize_heavyhash(uint64_t matrix[64*64], const char* in, char* out, int len)
{
    CHeavyHash ctx(matrix);
    ctx.Write((const unsigned char*)in, len);
    ctx.Finalize((unsigned char*)out);
}

void opticalbtc_hash(const char* in, char* out, int len)
{
    uint8_t *ptr = (uint8_t*) in+4;
    uint256 seed, hashprev;
    memcpy(&hashprev, ptr, 32);

    CSHA3_256().Write(hashprev.begin(), 32).Finalize(seed.begin());
    uint64_t matrix[64*64];
    GenerateHeavyHashMatrix(seed, matrix);
    serialize_heavyhash(matrix, in, out, len);
}
