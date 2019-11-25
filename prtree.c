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

static char pr_buf[256];
static int pr_n = 0;

static int node_printNode(
	const struct node *n,
	const char *pfx)
{
	strcpy(pr_buf + pr_n, pfx);
	int res = printf("%s<%d>\n", pr_buf, n->id);
	pr_buf[pr_n] = '\0';
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

	/* WE HAVE USED UTF-8 STRINGS TO REPRESENT
	 * THE TREE AND ITS LEGS. */
	/* RECURSIVE CALL FOR THE RIGHT SIDE */
	if (n->right)
		node_printR(n->right, "\xe2\x94\x82");

	/* the node */
	node_printNode(n, n->right
		? (n->left
			? "\xe2\x94\x94\xe2\x94\xbc" /* both arms */
			: "\xe2\x94\x94\xe2\x94\xb4") /* only right */
		: (n->left
			? "\xe2\x94\x94\xe2\x94\xac" /* only left */
			: "\xe2\x94\x94\xe2\x94\x80")); /* none */

	/* RECURSIVE CALL FOR THE LEFT SIDE. */
	if (n->left)
		node_printL(n->left, " ");

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

	/* WE HAVE USED UTF-8 STRINGS TO REPRESENT
	 * THE TREE AND ITS LEGS. */
	/* RECURSIVE CALL FOR THE RIGHT SIDE */
	if (n->right)
		node_printR(n->right, " ");

	/* the node */
	node_printNode(n, n->right
		? (n->left
			? "\xe2\x94\x8c\xe2\x94\xbc" /* both arms */
			: "\xe2\x94\x8c\xe2\x94\xb4") /* only right */
		: (n->left
			? "\xe2\x94\x8c\xe2\x94\xac" /* only left */
			: "\xe2\x94\x8c\xe2\x94\x80")); /* none */

	/* RECURSIVE CALL FOR THE LEFT SIDE. */
	if (n->left)
		node_printL(n->left, "\xe2\x94\x82");

	/* restore */
	pr_n = l;
	pr_buf[l] = '\0';
} /* node_printR */

void node_print(const struct node *n) 
{
	if (!n) return;

	/* WE HAVE USED UTF-8 STRINGS TO REPRESENT
	 * THE TREE AND ITS LEGS. */
	/* CALL FOR THE RIGHT SIDE */
	if (n->right)
		node_printR(n->right, "");

	/* the node */
	node_printNode(n, n->right
		? (n->left
			? "\xe2\x94\xbc" /* both arms */
			: "\xe2\x94\xb4") /* only right */
		: (n->left
			? "\xe2\x94\xac" /* only left */
			: "\xe2\x94\x80")); /* none */

	/* RECURSIVE CALL FOR THE LEFT SIDE. */
	if (n->left)
		node_printL(n->left, "");

} /* node_print */
