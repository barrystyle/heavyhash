#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <obtc.h>

uint8_t genesis_block[80] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf5, 0xfe, 0xbb, 0xad, 0x19, 0x86, 0x4a, 0x69, 0x00, 0xb6, 0xce, 0x84, 0x28, 0x75, 0x11, 0xe6, 0xe7, 0x46, 0x22, 0x9c, 0xe6, 0x23, 0x9f, 0xf3, 0xdf, 0x74, 0x81, 0x65, 0x47, 0x78, 0xa4, 0xc4, 0xd3, 0xe1, 0x5d, 0x60, 0xff, 0xff, 0x00, 0x1c, 0x07, 0x47, 0xd0, 0x42 };

int main()
{
	uint8_t hash[32];
	opticalbtc_hash((const char*)&genesis_block, (char*)&hash, sizeof(genesis_block));

	for (int i=31; i>-1; i--) {
		printf("%02hhx", hash[i]);
	}
	printf("\n");

	return 0;
}
