/* prtree.c -- prints a binary tree in-order with
 *             lines indicating left/right children.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Nov 25 08:41:46 EET 2019
 * Copyright: (c) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <string.h>

#include "node.h"

#ifndef USE_UTF8
#define USE_UTF8	0
#endif

struct strings ascii = {
	.both_arms   = "+->",
	.left_arm    = "v->",
	.right_arm   = "^->",
	.no_arms     = "o->",
	.lnode       = "`--",
	.rnode       = ",--",
	.shoulder    = "|  ",
	.no_shoulder = "   ",
	.root_right  = ">>> ",
	.root_node   = "=== ",
	.root_left   = "<<< ",
}, utf8 = {
	.both_arms   = "\xe2\x94\xbc\xe2\x94\x80",
	.left_arm    = "\xe2\x94\xac\xe2\x94\x80",
	.right_arm   = "\xe2\x94\xb4\xe2\x94\x80",
	.no_arms     = "\xe2\x94\x80\xe2\x94\x80",
	.lnode       = "\xe2\x94\x94\xe2\x94\x80",
	.rnode       = "\xe2\x94\x8c\xe2\x94\x80",
	.shoulder    = "\xe2\x94\x82 ",
	.no_shoulder = "  ",
	.root_right  = ">",
	.root_node   = "=",
	.root_left   = "<",
}, *o_fmt = &ascii;

#include "node.h"

static char pr_buf[256];
static int pr_n = 0;

static int node_printNode(
	const struct node *n,
	const char *pfx,
	const char *pfx2)
{
	int res = printf("%s%s%s(%d)\n", pr_buf, pfx, pfx2, n->id);
	return res;
} /* node_printNode */

static void node_printL(const struct node *n, const char *prf);
static void node_printR(const struct node *n, const char *prf);
		
static void node_printL(
	const struct node *n,
	const char *prf)
{
	int l = pr_n;
	strcpy(pr_buf + pr_n, prf);
	pr_n += strlen(prf);

	/* RECURSIVE CALL FOR THE RIGHT SIDE */
	if (n->right)
		node_printR(n->right, o_fmt->shoulder);

	/* THE NODE */
	node_printNode(n, o_fmt->lnode,
		n->right
			? (n->left
				? o_fmt->both_arms
				: o_fmt->right_arm)
			: (n->left
				? o_fmt->left_arm
				: o_fmt->no_arms));

	/* RECURSIVE CALL FOR THE LEFT SIDE. */
	if (n->left)
		node_printL(n->left, o_fmt->no_shoulder);

	/* restore */
	pr_n = l;
	pr_buf[l] = '\0';
} /* node_printL */

static void node_printR(
	const struct node *n,
	const char *prf)
{
	int l = pr_n;
	strcpy(pr_buf + pr_n, prf);
	pr_n += strlen(prf);

	/* RECURSIVE CALL FOR THE RIGHT SIDE */
	if (n->right)
		node_printR(n->right, o_fmt->no_shoulder);

	/* the node */
	node_printNode(n, o_fmt->rnode,
		n->right
			? (n->left
				? o_fmt->both_arms
				: o_fmt->right_arm) /* only right */
			: (n->left
				? o_fmt->left_arm
				: o_fmt->no_arms)); /* none */

	/* RECURSIVE CALL FOR THE LEFT SIDE. */
	if (n->left)
		node_printL(n->left, o_fmt->shoulder);

	/* restore */
	pr_n = l;
	pr_buf[l] = '\0';
} /* node_printR */

void tree_print(const struct node *root) 
{
	if (!root) return;

	/* CALL FOR THE RIGHT SIDE */
	if (root->right)
		node_printR(root->right, o_fmt->root_right);

	/* the node */
	node_printNode(root, o_fmt->root_node,
		root->right
			? (root->left
				? o_fmt->both_arms
				: o_fmt->right_arm) /* only right */
			: (root->left
				? o_fmt->left_arm
				: o_fmt->no_arms)); /* none */

	/* RECURSIVE CALL FOR THE LEFT SIDE. */
	if (root->left)
		node_printL(root->left, o_fmt->root_left);

} /* node_print */
