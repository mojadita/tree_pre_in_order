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

struct node *build_random(struct node *parent)
{
	if (prob < random() % 10000) return NULL;

	struct node *res = malloc(sizeof *res);
	assert(res != NULL);

	res->id		= id++;
	res->parent = parent;
	res->left	= build_random(res);
	res->right	= build_random(res);

	return res;
}

char *sep;

void print_preorder(struct node *n)
{
	if (!n) return;
	printf("%s%d", sep, n->id); sep = ", ";
	print_preorder(n->left);
	print_preorder(n->right);
}

void print_inorder(struct node *n)
{
	if (!n) return;
	print_inorder(n->left);
	printf("%s%d", sep, n->id); sep = ", ";
	print_inorder(n->right);
}

int main(int argc, char **argv)
{
	srandomdev();

	struct node *root = build_random(NULL);
	sep = "preorder: "; print_preorder(root); puts("");
	sep = "inorder: "; print_inorder(root); puts("");
	printf("Tree:\n");
	node_print(root);
}
