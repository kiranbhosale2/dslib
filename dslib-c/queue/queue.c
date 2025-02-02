#include <stddef.h>
#include <stdbool.h>
#include "queue.h"

static bool ring_queue_is_full(ring_queue_t *queue) {
	return (queue->queue_size == queue->max_size);
}

static bool ring_queue_is_empty(ring_queue_t *queue) {
	return ((0U != queue->read_pointer) && (0U != queue->read_pointer) && (queue->read_pointer == queue->write_pointer));
}

bool ring_queue_init(ring_queue_t *queue, uint8_t *ring_queue_buffer, size_t ring_queue_size) 
{
	bool queue_initialized = false;
	if ((NULL != queue) && (NULL != ring_queue_buffer)) {

		queue->write_pointer = 0U;	
		queue->read_pointer = 0U;	
		queue->queue_size = 0U;	
		queue->max_size = ring_queue_size;
		queue->buffer = ring_queue_buffer;	
		queue_initialized = true;
	}

	return queue_initialized;
}

bool ring_queue_enqueue(ring_queue_t *queue, uint8_t data) 
{
	bool item_queued = false;
	if ((NULL != queue) && (!ring_queue_is_full(queue))) {

		queue->buffer[queue->write_pointer] = data;
		queue->write_pointer = ((queue->write_pointer + 1) % queue->max_size);
		queue->queue_size++;
		item_queued = true;
	}

	return item_queued;
}


bool ring_queue_dequeue(ring_queue_t *queue, uint8_t *data) 
{
	bool item_dequeued = false;
	if ((NULL != queue) && (NULL != data) && (!ring_queue_is_empty(queue))) {

		*data = queue->buffer[queue->read_pointer];
		queue->read_pointer = ((queue->read_pointer + 1) % queue->max_size);
		queue->queue_size--;
		item_dequeued = true;
	}

	return item_dequeued;
}
