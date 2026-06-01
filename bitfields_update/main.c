#include <stdint.h>

void update_bitfield(volatile uint32_t *reg, uint32_t new_value, uint8_t start_bit, uint8_t width) {

	if (width == 0){
		return;
	}

	// Create mask
	uint32_t mask = 1;

	for (int i = 1; i < width; i++){
		mask = (mask << 1) | 1;
	}

	mask = mask << start_bit;
	mask = ~mask;

	// Mask one-liner:
	// mask = (1 << width) - 1;

	// Clear
	*reg &= mask;

	// Update
	*reg |= (new_value << start_bit);

}

int main (void){

	volatile uint32_t *p_reg = (uint32_t)0x32256543;
	uint32_t new_value = 0x05;
	int8_t start_bit = 12;
	uint8_t width = 4;

	update_bitfield(p_reg, new_value, start_bit, width);

	return 0;
}
