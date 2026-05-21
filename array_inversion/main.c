#include "stdio.h"
#include "stdint.h"

void display_array(int const *const array, int len);

int main(void){

	printf("Enter the number of elements in your array: ");

	int array_len;
	scanf("%d", &array_len);

	int og_array[array_len];

	for (int i = 0; i < array_len; i++){
		printf("Enter array element %d: ", i);
		scanf("%d", &og_array[i]);
	}

	printf("Array before inversion\n");

	display_array(og_array,array_len);

	printf("Array after inversion\n");

	return 0;
}


void reverse_array(int *p_array, int len){

	int beginning = 0;
	int end = len-1;
	int temp;

	// Check that the array size is > 1
	if (len <= 1){
		return;
	}

	while (beginning < end){
		temp = p_array[beginning];
		p_array[beginning] = p_array[end];
		p_array[end] = temp;

		beginning++;
		end--;
	}
}


void reverse_array_pointers(int *p_array, int len){

	int *p_beginning = p_array;
	int *p_end = (p_array + len -1);
	int temp;

	// Check that the array size is > 1
	if (len <= 1){
		return;
	}

	while (p_beginning < p_end){
		temp = *p_beginning;
		*p_beginning= *p_end;
		*p_end = temp;

		p_beginning++;
		p_end--;
	}
}

void display_array(int const *const p_array, int len){

	for (int i = 0; i <len; i++){
		printf("%d\t", p_array[i]);
	}
}
