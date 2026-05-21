/*
	Imagine you have a 64-bit machine. You receive a packet of data from a sensor into a raw memory buffer. The buffer starts at a memory address (let's call it 0x2000).

	The hardware documentation tells you the packet is laid out like this:

	Offset +0: A 1-byte Status Code (uint8_t).

	Offset +1: A 1-byte Error Flag (uint8_t).

	Offset +2: A 2-byte Sensor Value (uint16_t).

	Offset +4: A 4-byte Timestamp (uint32_t).

	Your Task: Write a C function called process_packet that takes a raw void *ptr (the start of the buffer) and extracts these values using only pointer arithmetic and casting.
 */

#include <stdio.h>
#include <stdint.h>

void process_packet(void *p_packet_addr){

	uint8_t *p_base_addr = p_packet_addr;

	uint8_t status_code;
	uint8_t error;
	uint16_t sensor_val;
	uint32_t timestamp;

	status_code = *p_base_addr;
	error = *(p_base_addr + 1);
	sensor_val = *(uint16_t*)(p_base_addr + 2);
	timestamp = *(uint32_t*)(p_base_addr + 4);

	/* Another way to access sensor_val
	 *
	 * msb_sensor_value = *(uint8_t*)(p_base_addr + 2);
	 * lsb_sensor_value = *(uint8_t*)(p_base_addr + 3);
	 *
	 * sensor_val = (msb_sensor_value << 8) | lsb_sensor_value;
	 *
	 */


	/* Another way to access timestamp
	 *
	 * timestamp_1 = *(uint8_t*)(p_base_addr + 4);
	 * timestamp_2 = *(uint8_t*)(p_base_addr + 5);
	 * timestamp_3 = *(uint8_t*)(p_base_addr + 6);
	 * timestamp_4 = *(uint8_t*)(p_base_addr + 7);
	 *
	 * timestamp = (timestamp_1 << 24) | (timestamp_2 << 16) | (timestamp_3 << 8) | timestamp_4;
	 *
	 */



}

void main (void){

};
