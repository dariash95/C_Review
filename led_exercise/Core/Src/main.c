/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"

#define RCC_APB2ENR_ADDR 	0x40021018
#define GPIOx_CRH_ADDR 		0x40011004
#define GPIOx_ODR			0x4001100C

#define GPIOC_CONFIG_MASK	0x00F00000 // 0b1111 0000 0000 0000 0000 0000
#define GPIOC_SETTING_MASK	0x00100000 //0b0001 0000 0000 0000 0000 0000

int main (void){

	volatile uint32_t *pRCCAPBEEnAddr = (uint32_t*)RCC_APB2ENR_ADDR;
	volatile uint32_t *pGPIOCCRAddr = (uint32_t*)GPIOx_CRH_ADDR;
	volatile uint32_t *pGPIOCOutAddr = (uint32_t*)GPIOx_ODR;

	// Enable Clock
	uint32_t RCCRegValue = *pRCCAPBEEnAddr;
	RCCRegValue |= 0x10; // Set bit 4

	/* Alternative with bit-shifting
	 * RCCRegValue |= (1 << 4);
	 */
	*pRCCAPBEEnAddr = RCCRegValue;

	/* Configure Pin C13 as output
	 	 Bits to configure:
			23 22
			0  0
			21 20
			0  1
	 */

	// First *clear* the positions
	*pGPIOCCRAddr &= ~GPIOC_CONFIG_MASK;
	/*
	 * Alternative with bit shifting
	 * *pGPIOCCRAddr &= ~(FF << 20)
	 */

	// Set bit 20
	*pGPIOCCRAddr |= GPIOC_SETTING_MASK;

	// Turn on Led by resetting bit 13 IT IS ACTIVE LOW!
	*pGPIOCOutAddr |= 0b0000000000000000;

	while(1);
}

void bit_extraction(void){

	volatile uint32_t *pRCCAPBEEnAddr = (uint32_t*)RCC_APB2ENR_ADDR;
	uint32_t RCCRegValue = *pRCCAPBEEnAddr;

	// Extract bits 9th to 14th from the register
	uint8_t bitFields = (RCCRegValue & (0x3F << 9)) >> 9;

	/*
	 * Alternative
	 * uint8_t bitFields = (RCCRegValue >> 9) & 0x3F;
	 */

}

