#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void custom_memcpy(const void *p_src, void *p_dest, size_t n){

	if ((p_src == NULL) || (n == 0) || p_dest == NULL){
		return;
	}

	// Pointer typecasting

	// For 4-byte blocks
	const uint32_t *p_src_32 = (uint32_t*)p_src;
	uint32_t *p_dest_32 = (uint32_t*)p_dest;

	// For 1-byte blocks
	const uint8_t *p_src_8 = (uint8_t*)p_src;
	uint8_t *p_dest_8 = (uint8_t*)p_dest;


	// Check for alignment
	bool aligned = false;

	// Mask 3 -> not addresses that end in 2 or 1
	// We need to use the typecast to uintptr_t so the compiler performs the modulo
	 if ((((uintptr_t)p_src_32 & 0x3) == 0) && (((uintptr_t)p_dest_32 & 0x3) == 0)){
		aligned = true;
	}

	/*
	 * We need to use the typecast to uintptr_t so the compiler performs the modulo
	if (((uintptr_t)p_src_32 % 4 == 0) && ((uintptr_t)p_dest_32 % 4 == 0)){
		aligned = true;
	}
	*/

	int mem_blocks = n/4;
	int mem_rem = n%4;
	int aux_end_loop = aligned ? mem_rem : n;

	// Only if memories are aligned. It not, copy byte by byte
	if (mem_blocks >= 1 && aligned){
		// Copy 4-bytes of memory
		for(int i = 0; i < mem_blocks; i++){
			p_dest_32[i] = p_src_32[i];
		}
	}

	// Copy rest
	if (!aligned || mem_rem) {
		int dest_index = 0;
		// Calculate index for the remaining bytes
		if (mem_blocks >= 1 && aligned) {
			dest_index = mem_blocks*4;
		}

		// Copy byte by byte the rest byte by byte
		for (int i = 0; i < aux_end_loop; i++){
			p_dest_8[dest_index+i] = p_src_8[dest_index+i];
		}
	}

	return;
}

int main(void) {

    uint8_t source_packet[14] = {
        0xAA, 0xBB, 0xCC, 0xDD, // Word 1
        0x11, 0x22, 0x33, 0x44, // Word 2
        0x55, 0x66, 0x77, 0x88, // Word 3
        0x99, 0xEE             // Trailing Bytes (Remainder of 2)
    };

    uint8_t destination_buffer[14] = {0};

    custom_memcpy(source_packet, destination_buffer, sizeof(source_packet));

    printf("Source Data:      ");
    for (size_t i = 0; i < sizeof(source_packet); i++) {
        printf("%02X ", source_packet[i]);
    }
    printf("\n");

    printf("Destination Copy: ");
    for (size_t i = 0; i < sizeof(destination_buffer); i++) {
        printf("%02X ", destination_buffer[i]);
    }
    printf("\n\n");

    return 0;
}
