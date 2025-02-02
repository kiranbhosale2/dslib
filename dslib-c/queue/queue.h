#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdint.h> 
/*
 @file queue.h
 @brief Red/Black Tree
 */

/**
 * @brief 
 * This is implementation of ring/cicrular queue. 
 * 
 */

typedef struct ring_queue
{
	size_t read_pointer;
	size_t write_pointer;
	size_t queue_size;
	size_t max_size;
	uint8_t *buffer;
} ring_queue_t;


/**
 * @brief 
 * assigns the bufffer and read/write indices 
 * @return true on success false otherwise
 */

bool ring_queue_init(ring_queue_t *queue, uint8_t *ring_queue_buffer, size_t ring_queue_size);

/**
 * @brief 
 *  inserts a single byte in a queue  
 * @return true on success(queue may be full) false otherwise
 */
bool ring_queue_enqueue(ring_queue_t *queue, uint8_t data) ;

/**
 * @brief 
 *  removed off a single byte from a queue  
 * @return true on success(queue may be empty) false otherwise
 */

bool ring_queue_dequeue(ring_queue_t *queue, uint8_t *data);
#endif

