
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER_SIZE 4

struct CircularBuffer{
	uint8_t volatile head;
	uint8_t volatile tail;
	uint8_t volatile count;
	int8_t buffer[BUFFER_SIZE];
};

bool buffer_empty(struct CircularBuffer *p_buffer) {
    return (p_buffer->count == 0);
}

bool buffer_full(struct CircularBuffer *p_buffer){

	return (p_buffer->count == BUFFER_SIZE);
}

void initialize_buffer(struct CircularBuffer *p_buffer){
	p_buffer->head = 0;
	p_buffer->tail = 0;
	p_buffer->count = 0;
}

void write_to_buffer(struct CircularBuffer *p_buffer, int8_t data){

	if (buffer_full(p_buffer)){
		printf("Buffer full, can't add another element\n");
		return;
	}

	// Insert element
	p_buffer->buffer[p_buffer->head] = data;

	// Increment head pointer and wrap around
	p_buffer->head++;

	if (p_buffer->head >= BUFFER_SIZE){
		p_buffer->head = 0;
	}

	p_buffer->count++;
}

int8_t read_from_buffer(struct CircularBuffer *p_buffer){

	// Check that buffer is not empty
	if (buffer_empty(p_buffer)){
		printf("Buffer is empty\n");
		return 0;
	}

	// Extract data
	int8_t data = p_buffer->buffer[p_buffer->tail];

	// Increment tail pointer and wrap around
	p_buffer->tail++;
	if (p_buffer->tail >= BUFFER_SIZE){
		p_buffer->tail = 0;
	}

	p_buffer->count--;

	return data;
}


int main(void)
{

	struct CircularBuffer my_circular_buffer;
	int8_t data_extracted;

	initialize_buffer(&my_circular_buffer);

	write_to_buffer(&my_circular_buffer, 2);
	write_to_buffer(&my_circular_buffer, 4);
	write_to_buffer(&my_circular_buffer, 6);
	write_to_buffer(&my_circular_buffer, 8);
	write_to_buffer(&my_circular_buffer, 10);

	data_extracted = read_from_buffer(&my_circular_buffer);
	write_to_buffer(&my_circular_buffer, 10);

    /* Loop forever */
	for(;;);
}
