/* bt.c -- build a tree based on a random sequence of inorder
 *         and print it in preorder and inorder.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Nov 25 14:35:35 EET 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD
 */

#include <assert.h>
#include <stdlib.h>

#include "node.h"

struct node *build(const unsigned *l, int sz, struct node *parent)
{
    if (sz == 0) return NULL;

    struct node *res = malloc(sizeof *res);
    assert(res != NULL);

    int i, im = -1;
    unsigned m = ~0;
    for (i = 0; i < sz; i++) {
        const unsigned c = l[i];
        if (c < m) {
            m = c;
            im = i;
        }
    }
    assert (im >= 0 && im < sz);

    res->id = m;
    res->parent = parent;
    res->left = build(l, im, res);
    res->right = build(l + im + 1, sz - im - 1, res);
    return res;
}
