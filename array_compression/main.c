#include <stdio.h>
#include <stdint.h>

void compact_buffer(uint8_t *p_buf, size_t len){

	size_t p_next_index = 0;

	for (int i = 0; i < len; i++){
		if(p_buf[i] != 0){
			p_buf[p_next_index] = p_buf[i];
			p_next_index++;
		}
	}

	// Fill the rest with zeros
	for (int i = p_next_index; i < len; i++){
	    p_buf[i] = 0;
	}
}

int main()
{
    uint8_t array[] = {0x12, 0x00, 0x34, 0x00, 0x55, 0x00, 0x78, 0x00};

    size_t arr_len = (sizeof(array)/sizeof(array[0]));

    compact_buffer(array, arr_len);

    for (int i = 0; i < arr_len; i++){
        printf("0x%x\n", array[i]);
    }

    return 0;
}
