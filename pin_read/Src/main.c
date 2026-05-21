#include "stdio.h"
#include "stdint.h"


#define RCC_APB2ENR_ADDR 	0x40021018

#define GPIOA_CRL_ADDR 		0x40010800
#define GPIOC_CRH_ADDR 		0x40011004

#define GPIOC_ODR			0x4001100C
#define GPIOA_IDR			0x40010808

#define GPIOA_CONFIG_MASK	0x00F00000 // 0b1111 0000 0000 0000 0000 0000
#define GPIOC_CONFIG_MASK	0x00F00000 // 0b1111 0000 0000 0000 0000 0000
#define GPIOC_SETTING_MASK	0x00100000 //0b0001 0000 0000 0000 0000 0000

#define GPIOA_PIN5_MASK		0x05

int main (void){

	uint32_t volatile *const pRCCAPBEEnAddr = (uint32_t*)RCC_APB2ENR_ADDR;
	uint32_t volatile *const pGPIOCCRAddr = (uint32_t*)GPIOC_CRH_ADDR;
	uint32_t volatile *const pGPIOACRAddr = (uint32_t*)GPIOA_CRL_ADDR;
	uint32_t volatile *const pGPIOCOutAddr = (uint32_t*)GPIOC_ODR;
	uint32_t const volatile *const pGPIOAInAddr = (uint32_t*)GPIOA_IDR;

	// Enable Clock
	uint32_t RCCRegValue = *pRCCAPBEEnAddr;
	RCCRegValue |= 0x14; // Set bit 4 and 2 to enable GPIOA and GPIOC
	*pRCCAPBEEnAddr = RCCRegValue;

	/* Configure Pin A5 as input */
	// First *clear* the positions
	*pGPIOACRAddr &= ~GPIOA_CONFIG_MASK;

	// Set bit 23
	*pGPIOACRAddr |= (1 << 23);

	/* Configure Pin C13 as output */
	// First *clear* the positions
	*pGPIOCCRAddr &= ~GPIOC_CONFIG_MASK;

	// Set bit 20
	*pGPIOCCRAddr |= GPIOC_SETTING_MASK;

	// Turn off LED
	*pGPIOCOutAddr |= (1 << 13);

	uint8_t gpioAPinStatus; // Because it may change unexpectedly

	while(1){
		// Read pin status
		gpioAPinStatus = ((*pGPIOAInAddr) & 0x10) >> 5;
		// To test
		//gpioAPinStatus = !gpioAPinStatus;


		if (gpioAPinStatus){
			*pGPIOCOutAddr &= ~(1 << 13);
		} else{
			*pGPIOCOutAddr |= (1 << 13);
		}
	}
}

