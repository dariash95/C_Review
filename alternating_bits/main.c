/*
 * main.c
 *
 *  Created on: Jun 19, 2026
 *      Author: danie
 */

#include <stdint.h>
#include <stdbool.h>

bool hasAlternatingBits(int n) {

	uint32_t x = (n ^ (n>>1));

	return (((x+1) & x) == 0);
}

