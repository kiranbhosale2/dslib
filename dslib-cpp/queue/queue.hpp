#ifndef _QUEUE_HPP
#define _QUEUE_HPP

#include <stdint.h> 
/*
* @file queue.h
 * @brief 
 * This file contains the implementation of ring/circular queue in C++
 * 
 */
 
template <typename T>
class Queue
{
	public:
		Queue(T* ptr, size_t maxSize):readPtr(0), writePtr(0), queueSize(0), maxSize(maxSize), queue(ptr) {}	
		~Queue() {}
		Queue(const Queue&) = delete;
		Queue& operator=(const Queue&) = delete;
		Queue(Queue&&) = delete;
		Queue& operator=(Queue&&) = delete;
		bool enqueue(T data) {
			bool itemQueued = false;
			if ((nullptr != queue) && (queueSize < maxSize)) {
				queue[writePtr] = data;
				writePtr = ((writePtr + 1) % maxSize);
				queueSize++;
				itemQueued = true;
			}
			return itemQueued;
		}	
		bool dequeue(T* data) {
			bool itemDequeued = false;
			if ((nullptr != queue) && (nullptr != data) && (queueSize > 0)) {
				*data = queue[readPtr];
				readPtr = ((readPtr + 1) % maxSize);
				queueSize--;
				itemDequeued = true;
			}
			return itemDequeued;
		}
		bool isFull() {
			return (queueSize == maxSize);
		}
		bool isEmpty() {
			return (queueSize == 0);
		}
		size_t size() {
			return queueSize;
		}

	private:
		size_t readPtr;
		size_t writePtr;
		size_t queueSize;
		size_t maxSize;
		T* queue;
};

#endif	// _QUEUE_HPP