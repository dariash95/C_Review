#include <stdint.h>
#include <stdio.h>

void sort(uint32_t *p_array, size_t len){

    uint32_t temp = 0;

	if (p_array == NULL || len <= 1){
		return;
	}

	for (size_t i = 0; i < len; i++){
		size_t min_index = i;

		for (size_t j = i+1; j < len; j++){
			if (p_array[j] < p_array[min_index]){
				min_index = j;
				//printf("New min: %d\n", p_array[j]);
			}
		}

		if (min_index != i){
		    temp = p_array[i];
            p_array[i] = p_array[min_index];
            p_array[min_index] = temp;
		}
	}
}

int main(void){
    uint32_t array[] = {20, 10, 40, 10, 30, 20};
    size_t arr_len = (sizeof(array)/sizeof(array[0]));

    sort(array, arr_len);

    for (int i = 0; i < arr_len; i++){
    	printf("%d \t", array[i]);
    }

    return 0;
}
