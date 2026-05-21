#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void swap_arrays(uint32_t *p_array_1, uint32_t *p_array_2, int len){

	uint32_t aux;

	for (int i = 0; i < len; i++){
		aux = p_array_1[i];
		p_array_1[i] = p_array_2[i];
		p_array_2[i] = aux;
	}

}

int main (void) {
	int len_array_1, len_array_2, len;

	uint32_t array_1[len_array_1];
	uint32_t array_2[len_array_2];

	printf("Enter the elements of array 1 ");
	scanf("%d", &len_array_1);
	printf("\n Enter the elements of array 2 ");
	scanf("%d", &len_array_2);
	printf("\n");

	len = len_array_1 < len_array_2 ? len_array_1 : len_array_2;

	for (int i = 0; i < len_array_1; i++){
		printf("Enter the element %d of array 1 ", i);
		scanf("%lu", &array_1[i]);
	}

	for (int i = 0; i < len_array_2; i++){
		printf("Enter the element %d of array 2 ", i);
		scanf("%lu", &array_2[i]);
	}

	swap_arrays(array_1, array_2, len);

	return 0;
}

float calculate_average(uint16_t *p_readings, int len){

	uint32_t sum = 0;

	if (len == 0){
		return 0;
	}

	for (int i = 0; i <len; i++){
		sum += p_readings[i];
	}

	return sum/len;
}

uint16_t find_peak(uint16_t *p_voltages, int len){

	uint16_t max = 0;

	if (len == 0){
		return 0;
	}

	for (int i = 0; i <len; i++){
		if (p_voltages[i] >= max){
			max = p_voltages[i];
		}
	}

	return max;
}

bool check_threshold(uint8_t *p_buffer, int len, uint8_t threshold){

	for (int i = 0; i < len; i++) {
		if (p_buffer[i] > threshold) {
			return true;
		}
	}

	return false;
}

void swap_array(uint32_t *p_array, int len){

	uint32_t temp;
	int i = 0;
	int j = len -1;

	while (i < j){
		temp = p_array[i];
		p_array[i] = p_array[j];
		p_array[j] = temp;
		i++;
		j--;
	}
}
