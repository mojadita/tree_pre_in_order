/* node.h -- node of the tree.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Nov 24 21:55:56 EET 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD
 */
#ifndef _NODE_H
#define _NODE_H

struct node {
    int          id;
    struct node *parent;
    struct node *left;
    struct node *right;
};

extern struct strings {
    char *both_arms;
    char *left_arm;
    char *right_arm;
    char *no_arms;
    char *lnode;
    char *rnode;
    char *shoulder;
    char *no_shoulder;
    char *root_right;
    char *root_node;
    char *root_left;
} ascii, utf8, *o_fmt;

struct node *build(const unsigned *l, int sz, struct node *parent);
void tree_print(const struct node *n);

#endif /* _NODE_H */
