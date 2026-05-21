/*
	You are writing a driver for a PWM (Pulse Width Modulation) peripheral. The hardware manual says the Control Register (CTRL_REG) is located at address 0x40001000. It is a 16-bit register with the following layout:

	Bits [0-2]: Prescaler (3 bits). Values 0-7.

	Bit [3]: Enable Bit (1 = ON, 0 = OFF).

	Bits [4-7]: Mode Select (4 bits).

	Bits [8-15]: Duty Cycle (8 bits).

	Your Task:
	Write a C function void set_pwm_prescaler(uint8_t scale) that updates only the 3-bit Prescaler (Bits 0-2) while keeping all other bits (3-15) exactly as they were.
 */

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct {
	uint16_t prescaler: 3;
	uint16_t enable: 1;
	uint16_t mode: 4;
	uint16_t duty: 8;
}PwmCtrlReg;

volatile PwmCtrlReg *pwm_reg = (volatile PwmCtrlReg*)0x40001000;

// Moved the assignment into a function
void init_pwm_hardware(void) {
    pwm_reg->duty = 0xA5;
}


void set_pwm_prescaler(uint8_t scale){

	volatile uint16_t *ctl_reg_add = (volatile uint16_t *)0x40001000;
	uint16_t ctl_reg_value = *ctl_reg_add;
	*ctl_reg_add = (ctl_reg_value & 0xFFF8) |(scale & 0x07) ;

	// Check check if the Enable Bit (Bit 3) is currently set
	bool b3_check = (*ctl_reg_add & 0x0008) == 8 ? true : false;

	// READ the 8-bit Duty Cycle (Bits 8-15) and store it
	uint16_t current_duty = (*ctl_reg_add & 0xFF00) >> 8;
}

void spi_transmit_byte(uint8_t data){
	volatile uint16_t *p_spi_status_reg = (volatile uint16_t *)0x40002000;
	volatile uint16_t *p_spi_data_reg = (volatile uint16_t *)0x40002004;
	uint8_t busy = 0;

	while (!(*p_spi_status_reg & 0x1));
	*p_spi_data_reg = data;
	while (((*p_spi_status_reg & 0x2) >> 1) & 0x1);
}


uint8_t check_motor_health(void){
	volatile uint16_t *p_fault_reg = (volatile uint16_t*)0x40003000;

	if ((*p_fault_reg & 0x1) | (*p_fault_reg & 0x2) | (*p_fault_reg & 0x4)) {
		*p_fault_reg = (*p_fault_reg & ~(0x80)) | (1 << 7);
		return 0;
	} else if (((*p_fault_reg & 0x1) == 0) && ((*p_fault_reg & 0x2) == 0) && ((*p_fault_reg & 0x4) == 0)) {
		return 1;
	}
}

/*
 * Better code
 *
 * uint8_t check_motor_health(void) {
    volatile uint16_t *p_fault_reg = (volatile uint16_t*)0x40003000;

    // Read once into a local variable (Shadowing)
    uint16_t current_status = *p_fault_reg;

    // Use a single mask (0x07) to check Bits 0, 1, and 2
    if (current_status & 0x07) {
        // A fault is present. Set ONLY bit 7.
        *p_fault_reg |= (1 << 7);
        return 0;
    } else {
        // No faults present in the bits we checked
        return 1;
    }
}
 *
 *
 */

#define MASK 0b0000000000110000


void set_timer_fast(void){
	volatile uint16_t *p_timer_reg = (volatile uint16_t *)0x40004000;
	*p_timer_reg = (*p_timer_reg & ~(MASK)) | (1 << 4);

}
