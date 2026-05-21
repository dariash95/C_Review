#include "stdio.h"
#include "stdint.h"

void swap_array(uint32_t *p_array, int32_t begin, int32_t end);
void display_array(uint32_t const *const p_array, int len);
void rotate_array(uint32_t *p_array, int len, int pos);

int main (void){
	printf("Enter the array length: ");
	int32_t len = 0;
	scanf("%d", &len);

	while (len == 0){
		printf("The number of elements must be bigger than 0\n");
		printf("Enter the array length: ");
		int len = 0;
		scanf("%d", &len);
	}

	uint32_t array[len];

	for (int i = 0; i < len; i++){
		printf("Enter element in position %d: ", i);
		scanf("%d", &array[i]);
	}

	printf("Enter the number of positions to shift: ");
	int k = 0;
	scanf("%d", &k);

	printf("Before shifting\n");
	display_array(array, len);


	rotate_array(array, len, k);
	printf("After shifting\n");
	display_array(array, len);


}

void rotate_array(uint32_t *p_array, int len, int pos){

	if (pos == 0){
		printf("No shifts implemented\n");
		return;
	} else if (len < pos){
		printf("The number of shifts exceeds the number of positions in the array\n");
		return;
	}

	swap_array(p_array, 0, (len-pos-1));
	swap_array(p_array, len-pos, len-1);
	swap_array(p_array, 0, len-1);

}

void swap_array(uint32_t *p_array, int32_t begin, int32_t end){

	uint32_t *p_beginning = p_array+begin;
	uint32_t *p_end = p_array+end;
	uint32_t temp;

	while (p_beginning < p_end){
		temp = *p_beginning;
		*p_beginning = *p_end;
		*p_end = temp;

		p_beginning++;
		p_end--;
	}
}

void display_array(uint32_t const *const p_array, int len){

	for (int i = 0; i <len; i++){
		printf("%d\t", p_array[i]);
	}
}

