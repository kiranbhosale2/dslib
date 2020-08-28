#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

static rbtree test_rbtree;

int test_comp_func(const void *key1, const void *key2)
{
	if (*(int *)key1 == *(int *)key2)
	{
		return 0;
	}
	else if (*(int *)key1 <= *(int *)key2)
	{
		return -1;
	}
	else if (*(int *)key1 > *(int *)key2)
	{
		return 1;
	}
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
	}
}

static void rbtree_test()
{
	int i;
	int key;

	printf("Testing the red black tree \n");
	
	rbtree_init(&test_rbtree, test_comp_func);

	for ( i = 0; i < 100; i++)
	{
		test_rbtree_insert(&test_rbtree);
	}

	tes_rbtree_find(&test_rbtree);
}

int main(void)
{
	const char *menu = "\n 1.Test list \n2.Test BST \n3.Test Red black tree \n4.Exit\n";
	int cnt, data;
	unsigned char item;
	rbtree_node *node;

	while (1)
	{
		printf("Menu = %s", menu);
		item = getchar();
		item = item - '0';
		switch (item)
		{
		case 1:
			break;

		case 2:
			break;

		case 3:
			rbtree_test();
			break;

		case 4:
			break;

		default:	
			break;
		}
	}
}

