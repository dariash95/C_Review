#include <stdint.h>
#include <string.h>
#include <stdio.h>

void reverse_string(char *p_char, int str_len){

	if (!str_len){
		return;
	}

	char *p_beginning = p_char;
	char *p_end = p_char+str_len-1;
	uint8_t temp_char;

	while(p_beginning < p_end){
		temp_char = *p_beginning;
		*p_beginning = *p_end;
		*p_end = temp_char;

		p_beginning++;
		p_end--;
	}
}

void string_reverse_recurssion(char *p_beginning, char *p_end){

	uint8_t temp_char;

	if (p_beginning >= p_end){
		return;
	}

	temp_char = *p_beginning;
	*p_beginning = *p_end;
	*p_end = temp_char;

	p_beginning++;
	p_end--;

	string_reverse_recurssion(p_beginning, p_end);

	return;
}

int main (void){

	char og_string[100];
	int string_length = 0;

	printf("Enter the string to be reversed: ");
	scanf("%[^\n]s", og_string);

	printf("\n");

	string_length = strlen(og_string);

    printf("Original string: %s\n", og_string);
	printf("String length: %d", string_length);

	//reverse_string(og_string, string_length);

	char *p_beginnig = og_string;
	char *p_end = (og_string+string_length-1);

	string_reverse_recurssion(p_beginnig, p_end);

	printf("\nReversed string: %s", og_string);
}
