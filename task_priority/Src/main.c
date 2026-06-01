#include <stdint.h>
#include <stdio.h>

int8_t get_highest_priority_task(uint32_t ready_queue) {

	int8_t task_number = 0;

    // Check if the queue is totally empty first
	if (ready_queue == 0){
		return -1;
	}

    // Find the position of the FIRST set bit (from the right/LSB)
	/*	for (int i = 0; i < 32; i++){
		if ((ready_queue >> i) & 1){
			task_number = i;
			break;
		}
	}
	 *
	 */

	// No loops. Deterministic execution!
	task_number = (__builtin_ctz(ready_queue));

    return task_number;
}

int main(void)
{
    /* Loop forever */
	for(;;);
}
