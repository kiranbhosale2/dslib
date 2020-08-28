#include <stddef.h>
#include "rbtree.h"

static void left_rotate(rbtree *tree, rbtree_node *x)
{
	rbtree_node *y;

	y = x->right;
	x->right = y->left;

	if (x->right != tree->null)
	{
		x->right->parent = x;
	}
	
	if (x->parent == tree->null)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	
	x->parent = y;
	y->left = x;
	
}

static void right_rotate(rbtree *tree, rbtree_node *x)
{
	rbtree_node *y;

	y = x->left;
	x->left = y->right;

	if (x->left != tree->null)
	{
		x->left->parent = x;
	}
	
	if (x->parent == tree->null)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	
	x->parent = y;
	y->right = x;
}

static void insert_fixup(rbtree *tree, rbtree_node *z)
{
	rbtree_node *y;
		
	while (z->parent->color == RBCOLOR_RED)
	{
		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if (y->color == RBCOLOR_RED)
			{
				y->color = RBCOLOR_BLACK;					/* Case 1 */
				z->parent->color = RBCOLOR_BLACK;			/* Case 1 */
				z->parent->parent->color = RBCOLOR_RED; 	/* Case 1 */
				z = z->parent->parent;
			}	
			else			 
			{	
				if (z == z->parent->right) 					/* Case 2 */
				{	
					z = z->parent;							/* Case 2 */
					left_rotate(tree, z);					/* Case 2 */
				}
				
				z->parent->color = RBCOLOR_BLACK;			/* Case 3 */
				z->parent->parent->color = RBCOLOR_RED;		/* Case 3 */
				right_rotate(tree, z->parent->parent);		/* Case 3 */
			}
		}
		else
		{
			y = z->parent->parent->left;
			if (y->color == RBCOLOR_RED)
			{
				y->color = RBCOLOR_BLACK;					/* Case 1 */
				z->parent->color = RBCOLOR_BLACK;			/* Case 1 */
				z->parent->parent->color = RBCOLOR_RED; 	/* Case 1 */
				z = z->parent->parent;
			}	
			else			 
			{	
				if (z == z->parent->left)						/* Case 2 */
				{	
					z = z->parent;							/* Case 2 */
					right_rotate(tree, z);					/* Case 2 */
				}
				
				z->parent->color = RBCOLOR_BLACK;			/* Case 3 */
				z->parent->parent->color = RBCOLOR_RED;	/* Case 3 */
				left_rotate(tree, z->parent->parent);			/* Case 3 */
			}
		}
	}
}

static void rbtree_transplant(rbtree *tree, rbtree_node *x, rbtree_node *y)
{
	if (x->parent == tree->null)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->parent = x->parent;
}

static void delete_fixup(rbtree *tree, rbtree_node *x)
{
	rbtree_node *w;
		
	while ((x != tree->root) && (x->color == RBCOLOR_BLACK))
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;

			if (w->color == RBCOLOR_RED)
			{
				x->parent->color = RBCOLOR_RED;
				w->color = RBCOLOR_BLACK;
				left_rotate(tree, x->parent);
				w = x->parent->right;
			}
		}
		else
		{
			w = x->parent->left;
		}
	}
}

/* Red black trees Utility Functions */
rbtree_node *rbtree_minimum(rbtree *tree, rbtree_node *node)
{
	rbtree_node *min_node;
	
	min_node = node ->left;
	
	while (min_node != tree->null)
	{
		min_node = min_node->left;
	}

	return min_node;
}

rbtree_node * rbtree_search(rbtree *tree, const void *key)
{
	int ret_val;
	rbtree_node *node;

	node = tree->root;
	while (node != tree->null)
	{
		ret_val = tree->comp(node->key, key);
		if (ret_val == 0)
		{
			return node; /* Found the node with a key */
		}
		
		node = ret_val < 0 ? node->left : node->right;
	}

	return node != tree->null ? node : NULL;
}

void rbtree_delete(rbtree *tree, rbtree_node *z)
{
	rbtree_node *x, *y;
	rbtree_color y_original_color;

	y = z;
	y_original_color = y->color;

	if (z->left == tree->null)
	{
		x =  z->right;
		rbtree_transplant(tree, z, z->right);
	}
	else if (z->right == tree->null)
	{
		x =  z->right;
		rbtree_transplant(tree, z, z->left);
	}
	else 
	{
		y = rbtree_minimum(tree, z->right);
		y_original_color = y->color;

		x = y->right;
		 if (y->parent == z)
		 {
		 	x->parent = y;
		 }
		 else
		 {
		 	y->right = z->right;
			y->right->parent = y;
		 }
	}

	if (y_original_color == RBCOLOR_BLACK)
	{
		delete_fixup(tree, x);
	}
}

int rbtree_insert(rbtree *tree, rbtree_node *node)
{
	int ret_val;
	rbtree_node *x, *y;

	y = tree->null;
	x = tree->root;

	while(x != tree->null)
	{
		y = x;
		ret_val = tree->comp(x->key, node->key);
		if (ret_val == 0)
		{
			return -1; /* node with a given key already exists, return */
		}

		x = ret_val < 0 ? x->left : x->right;
	}

	if (y == tree->null)
	{
		tree->root = node;
	}

	else 
	{
		ret_val = tree->comp(y->key, node->key);
		if (ret_val <= 0)
		{
			y->left = node;
		}
		else if (ret_val > 0)
		{
			y->right = node;
		}

		node->parent = y;
	}

	node->color = RBCOLOR_RED;

	insert_fixup(tree, node);

	return 0;
}

/*
* The Red black tree initialization function
*/
void rbtree_init(rbtree *tree, rbtree_comp_func *comp)
{
	tree->null_node.color = RBCOLOR_BLACK;
	tree->null_node.left = tree->null_node.right = tree->null_node.parent = &tree->null_node;
	tree->null = &tree->null_node;
	tree->root = tree->null;
	tree->comp = comp;
}
 

