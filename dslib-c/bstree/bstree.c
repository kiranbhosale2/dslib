/*
 * Copyright 2018-20 Kiran Bhosale
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

/* Binary search tree Utility Functions */
static bstree_node *bstree_minimum(bstree *tree, bstree_node *node)
{
	bstree_node *min_node;
	
	min_node = node ->left;
	
	while (min_node != tree->null)
	{
		min_node = min_node->left;
	}

	return min_node;
}

void bstree_insert(bstree *tree, bstree_node *node)
{
	bstree_node *x, *y;

	y = NULL;
	x = tree->root;
	while(x != tree->null)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;

	if (y == tree->null)
	{
		tree->root = node;
	}
	else
	{
		if (node->key < y->key)
		{
			y->left = node;
		}
		else
		{
			y->right = node;
		}
	}
}

static void bstree_transplant(bstree *tree, bstree_node *x, bstree_node *y)
{
	if (x->parent == tree->null)
	{
		tree->root = x;
		return;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	if (y != tree->null)
	{
		y->parent = x->parent;
	}
}

bstree_node * bstree_search(bstree *tree, const void *key)
{
	int ret_val;
	bstree_node *node;

	node = tree->root;
	while (node != tree->null)
	{
		ret_val = tree->comp((void *)node->key, key);
		if (ret_val == 0)
		{
			return node; /* Found the node with a key */
		}
		
		node = ret_val < 0 ? node->left : node->right;
	}

	return node != tree->null ? node : NULL;
}

void bstree_delete(bstree *tree, bstree_node *node)
{
	if (node->left == tree->null)
	{
		bstree_transplant(tree, node, node->right);
	}
	else if (node->right == tree->null)
	{
		bstree_transplant(tree, node, node->left);
	} 
	else
	{
		bstree_node *y = bstree_minimum(tree, node->right);
		if (y->parent != node)
		{
			bstree_transplant(tree, y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}

		bstree_transplant(tree, node, y);

		y->left = node->left;
		y->left->parent = y;
	}
}

/*
* The BST init function
*/
void bstree_init(bstree *tree, bstree_comp_func *comp)
{
	tree->null_node.left = tree->null_node.right = tree->null_node.parent = &tree->null_node;
	tree->null = &tree->null_node;
	tree->root = &tree->null_node;
	tree->comp = comp;
}
