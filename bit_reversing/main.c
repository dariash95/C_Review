#include <stdint.h>
#include <stdio.h>

#define REG_32_ADDR 	0x20000008UL

uint32_t reverse_32_bits(uint32_t reg){

	uint32_t reversed = 0;
	uint32_t moving_bit = 0;

	for (int i = 0; i < 32; i ++){
		moving_bit = (reg >> i) & 1; // Only extracts the LSB
		reversed = (reversed << 1) | moving_bit; // Makes space for one extra bit and pushes the new extracted bit
	}

	return reversed;
}


int main (void){

	uint32_t volatile *pReg32 =(uint32_t*)REG_32_ADDR;
	*pReg32 = 0x4532AABC;
	uint32_t reversedReg = reverse_32_bits(*pReg32);

	printf("Reversed: %x", reversedReg);

	return 0;
}

