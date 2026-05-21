#include <stdint.h>
#include <stdio.h>

int find_duplicates(uint32_t *p_array, size_t len){

	if (len == 0 || p_array == NULL){
		return 0;
	}

	size_t comp_index = 0;
	p_array[comp_index] = p_array[0];
	int count = 1;

	for (size_t i = 1; i <len; i++){
		if (p_array[i] != p_array[comp_index]){
			comp_index++;
			p_array[comp_index] = p_array[i];
			count++;
		}
	}

	return count;
}

int main(void){
    uint32_t array[] = {10, 10, 20, 20, 20, 30, 30, 40};
    size_t arr_len = (sizeof(array)/sizeof(array[0]));

    int duplicates = find_duplicates(array, arr_len);

    printf("Duplicates %d", duplicates);

    return 0;
}


