#ifndef _RBTREE_H
#define _RBTREE_H

/*
 @file rbtree.h
 @brief Red/Black Tree
 */

/*
Some useful terms:
1) Grandparent of the node: Parent of node's parent.
2) Uncle node: The right or left child (depending on whether the parent 
of node is left or right child respectively) of the grandparent of the current
node.

Red black tree Insertion: 
The node is inserted, in manner similar to binary search trees, but this insertion
might cause violation of some of the properties of red black trees. We call an
auxiliary function insert_fixup() to preserve these properties
(Please refer CLRS chapter 13 for red black tree properties).

Case 1 : The color of  uncle is red 
In this case we color both the parent of z and its uncle black, and
its grandparent red and we move z to its grandparent. This continues until 
the root. At the end end of loop, root is made black to preserve the property 2
(The root can't be red)

case 2 : The color of uncle is black and node is a right child
case 3 : The color of uncle is black and node is a left child
In case 2 and 3, the color of z's uncle is red. We distinguish these cases depending
on whether the z is right child (case 2) or left child (case 3) of its parent. In case z
is right child, we move z to its parent and left rotate it, resulting in case 3. Please
note that this rotation has neither affected the property 5 (there can't be 2 subsequent
red nodes), nor the property 3, which states that the number of black nodes
from node to the leaf nodes are same. 
In case 3, we color the parent of node to black, preserving the  property 5, but still the 
property 3 might have been violated, so we color the grandparent of node to red and 
right rotate it.
*/
typedef enum
{
	RBCOLOR_BLACK,
	RBCOLOR_RED,
} rbtree_color;

typedef struct rbtree_node
{
	rbtree_color color;
	const void *key;
	struct rbtree_node *parent;
	struct rbtree_node *left;
	struct rbtree_node *right;
} rbtree_node;

/**
 * The type of function use to compare key value of tree node.
 * @return
 *  0 if the keys are equal
 * < 0 if key1 is lower than key2
 * > 0 if key1 is greater than key2.*/

typedef int rbtree_comp_func(const void *key1, const void *key2);


typedef int comp_func(const void *key1, const void *key2);
typedef struct 
{
	rbtree_node null_node;
	rbtree_node *null;
	rbtree_node *root;
	comp_func *comp;
} rbtree;

/*
Search the node with a matching key
return a node if found
param @tree - the red black tree instance
param @key - The key to match
*/
rbtree_node *rbtree_search(rbtree *tree, const void *key);

/*
Delete the given node from the red black tree
param @tree - the red black tree instance
param @key - Node to be deleted
*/
void rbtree_delete(rbtree *tree, rbtree_node *node);

/*
Insert the  node in a red black tree. The color changes will be made accordingly,
So that the tree is balanced
param @tree - address of the red black tree variable.
param @key - Node to be inserted
*/
int rbtree_insert(rbtree *tree, rbtree_node *node);

/*
Initialize the red black tree. This will initialize the nullll node to point to itself and root node to point to a null node.
param @tree - address of the red black tree variable.
param @comp - the tree compare function. Please refer above notes for this function
param @key - Node to be deleted
*/
void rbtree_init(rbtree *tree, rbtree_comp_func *comp);
#endif

