#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rbtree.h"
#include "queue.h"

typedef enum {
	QUEUE = 1U,
	LINKED_LIST,
	BINARY_SEARCH_TREE,
	RED_BLACK_TREE
}test_lib_t;

static rbtree test_rbtree;

int test_comp_func(const void *key1, const void *key2)
{
	int ret_val = -1;
	if (*(int *)key1 == *(int *)key2)
	{
		ret_val = 0;
	}
	else if (*(int *)key1 <= *(int *)key2)
	{
		ret_val = -1;
	}
	else if (*(int *)key1 > *(int *)key2)
	{
		ret_val = 1;
	} else {

	}
	return ret_val;
}

static void test_rbtree_insert(rbtree *tree)
{
	rbtree_node *node;
	
	node = (rbtree_node *)malloc(sizeof(rbtree_node));
	if (node != NULL)
	{
		node->color = RBCOLOR_RED;
		node->left = node->right = node->parent = &tree->null_node;
		node->key = malloc(sizeof(int));
		*(int *)(node->key) = rand();
		
		printf("Node key = %d \n ", *(int *)(node->key));

		rbtree_insert(tree, node);
	}
}

static void tes_rbtree_find(rbtree *tree)
{
	int key;
	rbtree_node *node;
	
	printf("Enter the key to search the node\n");
	scanf("%d", &key);
	node = rbtree_search(tree, (void *)&key);
	if (node)
	{
		printf("Found the node with key %d key of node = %d \n", key, *(int *)(node->key));
	} else {
		printf(" node with key %d key doesn't exist \n", key);
	}
}

static void rbtree_test()
{
	int i;

	printf("Testing the red black tree \n");
	
	rbtree_init(&test_rbtree, test_comp_func);

	for ( i = 0; i < 100; i++)
	{
		test_rbtree_insert(&test_rbtree);
	}

	tes_rbtree_find(&test_rbtree);
}


static void queue_test()
{
	uint8_t queue_bufffer[100U] = {0U};
	ring_queue_t test_queue = {0};
	uint8_t item = 0U;
	printf("Testing the Queue \n");
	if (!ring_queue_init(&test_queue, queue_bufffer, 100U)) {
		printf("Error initializing the Queue \n");
	}

	for (size_t i = 0; i < 103; i++)
	{
		item = (rand() % UINT8_MAX);
		if (!ring_queue_enqueue(&test_queue, item)) {
			printf("failed to insert an item %d in a queue \n", item);
		}
	}

	for (size_t i = 0; i < 103; i++) {
		if (!ring_queue_dequeue(&test_queue, &item)) {
		
		printf("failed to remove an item from a queue \n");
	}
	}
	
}

int main(void)
{
	const char *menu = "\n 1.QUEUE \n 2.Linked List \n3.Binary search Tree \n4.Red black tree \n5.Exit\n";

	while (1)
	{
		printf(" Enter Test from \n = %s", menu);
		test_lib_t test_case = (test_lib_t)(getchar() - '0');
		switch (test_case)
		{
		case QUEUE:
			queue_test();
			break;

		case LINKED_LIST:
			break;

		case BINARY_SEARCH_TREE:
			
			break;

		case RED_BLACK_TREE:
			rbtree_test();
			break;

		default:	
			break;
		}
	}
}

