/*
 * main.c
 *
 *  Created on: May 18, 2026
 *      Author: danie
 */

#include "stdio.h"
#include "stdint.h"

int sum (int n){

	int sum_result = 0;

	if (n == 1){
		return 1;
	}

	sum_result = n + sum(n-1);

	return sum_result;
}

int main (void){

	int num;
	printf("Please enter the number up until which you want to count: ");
	scanf("%d", &num);

	int result = sum(num);

	printf("%d", result);

	return 0;
}

