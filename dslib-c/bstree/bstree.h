/*
 * Copyright 2018-20, Kiran Bhosale
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */
#ifndef _BSTREE_
#define _BSTREE_ 

typedef struct bstree_node
{
	int data;
	int key;
	struct bstree_node *parent;
	struct bstree_node *left;
	struct bstree_node *right;
} bstree_node;


/**
 * The type of function use to compare key value of tree node.
 * @return
 *  0 if the keys are equal
 * < 0 if key1 is lower than key2
 * > 0 if key1 is greater than key2.*/

typedef int bstree_comp_func(const void *key1, const void *key2);

typedef struct 
{
	bstree_node null_node;
	bstree_node *null;
	bstree_node *root;
	bstree_comp_func *comp;
} bstree;

/*
Search the node with a matching key
return a node if found
param @tree - the red black tree instance
param @key - The key to match
*/
bstree_node *bstree_search(bstree *tree, const void *key);

/**
Insert the node in a tree
return none
params
@tree - The BST instance
@node - node to be inserted
 */
void bstree_insert(bstree *tree, bstree_node *node);

/**
Delete the node from a tree
return none
params
@tree - The BST instance
@node - node to be deleted
 */
void bstree_delete(bstree *tree, bstree_node *node);

/**
The type of function use to compare key value of tree node.
return none
params
@tree - The BST instance
@comp - the key compare function
 */
void bstree_init(bstree *tree, bstree_comp_func *comp);


#endif
