/* bt.c -- build a random tree and print it in preorder
 *		   and inorder.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Nov 24 22:01:58 EET 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"


int prob = 5000,
	id = 0;

char *sep;


void print(struct node *n, unsigned *unused)
{
	printf("%s%u", sep, n->id);
	sep = ", ";
}

void renumber(struct node *n, unsigned *id)
{
	n->id = (*id)++;
}

void print_preorder(
	struct node *n,
	void (*f)(struct node *n, unsigned *p),
	unsigned *p)
{
	if (!n) return;
	f(n, p);
	print_preorder(n->left, f, p);
	print_preorder(n->right, f, p);
}

void print_inorder(struct node *n)
{
	if (!n) return;
	print_inorder(n->left);
	printf("%s%d", sep, n->id); sep = ", ";
	print_inorder(n->right);
}

unsigned *tree;
int tree_n;
int tree_cap;

void add_to_tree(unsigned v)
{
	if (!tree) {
		tree_cap = 10;
		tree = malloc(10 * sizeof *tree);
		assert(tree != NULL);
	}
	if (tree_n == tree_cap) { /* grow */
		tree_cap <<= 1;
		tree = realloc(tree, tree_cap * sizeof *tree);
		assert(tree != NULL);
	}
	tree[tree_n++] = v;
}


int main(int argc, char **argv)
{
	unsigned v;
	while (scanf("%u", &v) == 1)
		add_to_tree(v);

	struct node *root = build(tree, tree_n, NULL);
	sep = "preorder: "; print_preorder(root, print, NULL); puts("");
	sep = "inorder: "; print_inorder(root); puts("");
	node_print(root);

	unsigned id = 0;
	print_preorder(root, renumber, &id);

	sep = "preorder2: "; print_preorder(root, print, NULL); puts("");
	sep = "inorder: "; print_inorder(root); puts("");
	node_print(root);

}

