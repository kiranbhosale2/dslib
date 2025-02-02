// Created: 2021-04-10 16:00
#include <iostream>
#include "queue.hpp"  
#include "list.hpp"  
 enum class test_case_num_t 
{
	QUEUE = 1U,
	LINKED_LIST,
	BINARY_SEARCH_TREE,
	RED_BLACK_TREE,
	EXIT
};

using namespace std;

static void testFunction(test_case_num_t testId)
{
	uint8_t queue_bufffer[100U] = {0U};
	uint8_t item = 0U;
	Queue testque(queue_bufffer, sizeof(queue_bufffer));
    List<uint8_t> testList;

	for (size_t i = 0; i < 103; i++)
	{
		item = (rand() % UINT8_MAX);
        if (testId == test_case_num_t::QUEUE)
        {
            if (!testque.enqueue(item)) 
            {
                cout << "failed to add an item to a queue" << endl;
            }
            cout << "Item added to queue (hex) :" << hex << static_cast<int>(item) << dec << endl;
        }
        else if (testId == test_case_num_t::LINKED_LIST)
        {
            testList.pushFront(item);
            cout << "Item added to list (hex) :" << hex << static_cast<int>(item) << dec << endl;
        }
	}

    for (size_t i = 0; i < 103; i++)
	{
        uint8_t item = 0U;
        if (testId == test_case_num_t::QUEUE)
        {
            if (!testque.dequeue(&item)) 
            {
                cout << "failed to add an item to a queue" << endl;
            }
            cout << "Item removed from queue (hex) :" << hex << static_cast<int>(item) << dec << endl;
        }
        else if (testId == test_case_num_t::LINKED_LIST)
        {
            auto item = testList.popBack();
            cout << "Item removed from list (hex) :" << hex << static_cast<int>(item) << dec << endl;
        }
	}	
}

int main(void)
{
    testFunction(test_case_num_t::QUEUE);
    testFunction(test_case_num_t::LINKED_LIST);
}
