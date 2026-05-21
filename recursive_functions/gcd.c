/*
 * gcd.c
 *
 *  Created on: May 18, 2026
 *      Author: danie
 */

#include "stdio.h"
#include "stdint.h"

int gcd_find(int n1, int n2){

	// Formula gcd(a,b) = gcd(b, a mod b)
	int gcd;

	if (n2 == 0){
		return n1;
	}

	gcd = gcd_find(n2, n1%n2);

	return gcd;
}


int main (void){

	int num1, num2, gcd;
	printf("Please enter the first number: ");
	scanf("%d", &num1);

	printf("Please enter the second number: ");
	scanf("%d", &num2);

	gcd = gcd_find(num1, num2);

	printf("The GCD is %d", gcd);
}


