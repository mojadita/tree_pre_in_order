/* node.h -- node of the tree.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Nov 24 21:55:56 EET 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD
 */
#ifndef _NODE_H
#define _NODE_H

struct node {
	int			 id;
	struct node *parent;
	struct node *left;
	struct node *right;
};

void node_print(const struct node *n);

#endif /* _NODE_H */
