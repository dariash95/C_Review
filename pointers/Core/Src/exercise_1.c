#include "stdio.h"
#include "stdint.h"



int exercise_1(int){

	char a_var = 100;
	printf("Address of variable a: %p \n", &a_var);

	char *p_a_var_addr = (char*)&a_var;

	char value_stored = *p_a_var_addr;

	printf("Value stored in a_var : %d \n", value_stored);

	*p_a_var_addr = 65;
	printf("Value stored in a_var : %d \n", *p_a_var_addr);

	return 0;
}

long long int g_data = 0x12345678FF443356;

int exercise_2(int){

	char *pAddress1 = (char*)&g_data;
	// Note that is only one byte retrieved due to the type of the pointer
	printf("Value at address %p is %x \n", pAddress1, *pAddress1);

	int *pAddress2 = (int*)&g_data;
	printf("Value at address %p is %x \n", pAddress2, *pAddress2);

	// Short: 2 bytes
	short *pAddress3 = (short*)&g_data;
	printf("Value at address %p is %x \n", pAddress3, *pAddress3);

	long long int *pAddress4 = (long long int*)&g_data;
	printf("Value at address %p is %llx \n", pAddress4, *pAddress4);

}

int exercise_3(int){

	char *pAddress1 = (char*)&g_data;
	printf("Address%p is %x \n", pAddress1);
	printf("Value stored: %d \n", *pAddress1); // prints 56

	pAddress1++;

	printf("Address%p is %x \n", pAddress1);
	printf("Value stored: %d \n", *pAddress1); // prints 33

}

int odd_even(int32_t num){

	if (num & 1){
		return 1;
	} else {
		return 0;
	}
}

#define SET_MASK 0x90

void setting_bit(void){

	int32_t number;
	int32_t result;

	printf("Enter a number: ");
	scanf("%ld", &number);

	result = number | SET_MASK;
}

#define CLEAR_MASK 0x70

void clearing_bit(void){

	int32_t number;
	int32_t result;

	printf("Enter a number: ");
	scanf("%ld", &number);

	result = number & ~(CLEAR_MASK);

}


void test (void){

	int32_t number;

	printf("Enter a number: ");
	scanf("%ld", &number);

	int result = odd_even(number);

	if (result){
		printf("%ld number is odd", number);
	} else {
		printf("%ld number is even", number);
	}
}
