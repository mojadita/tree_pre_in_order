/* bt.c -- build a random tree and print it in preorder
 *         and inorder.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Nov 24 22:01:58 EET 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD
 */

#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"

#define F(_f) __FILE__":%d: " _f, __LINE__

#define PRINT_PASS1     (1 << 0)
#define PRINT_PASS2     (1 << 1)
#define PRINT_INORDER   (1 << 2)
#define PRINT_PREORDER  (1 << 3)
#define PRINT_TREE      (1 << 4)

int flags = PRINT_PASS2 | PRINT_INORDER | PRINT_TREE; /* config flags */

char *sep; /* print separator */

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

void clear_tree()
{
    if (tree) free(tree);
    tree_n = tree_cap = 0;
}

void process(char *name, FILE *f)
{
    unsigned v;

    while (fscanf(f, "%u", &v) == 1)
        add_to_tree(v);

    struct node *root = build(tree, tree_n, NULL);

    if (flags & PRINT_PASS1) {
        if (flags & PRINT_PREORDER) {
            sep = "preorder1: ";
            print_preorder(root, print, NULL);
            puts("");
        }
        if (flags & PRINT_INORDER) {
            sep = "inorder1: ";
            print_inorder(root);
            puts("");
        }
        if (flags & PRINT_TREE) {
            tree_print(root);
        }
    }

    unsigned id = 0;
    print_preorder(root, renumber, &id);

    if (flags & PRINT_PASS2) {
        if (flags & PRINT_PREORDER) {
            sep = "preorder2: ";
            print_preorder(root, print, NULL);
            puts("");
        }
        if (flags & PRINT_INORDER) {
            sep = "inorder2: ";
            print_inorder(root);
            puts("");
        }
        if (flags & PRINT_TREE) {
            tree_print(root);
        }
    }
    clear_tree();
}

int main(int argc, char **argv)
{
    int opt;

    while((opt = getopt(argc, argv, "12iptau")) != EOF) {
        switch (opt) {
        case '1': flags ^= PRINT_PASS1; break;
        case '2': flags ^= PRINT_PASS2; break;
        case 'i': flags ^= PRINT_INORDER; break;
        case 'p': flags ^= PRINT_PREORDER; break;
        case 't': flags ^= PRINT_TREE; break;
        case 'a': o_fmt = &ascii; break;
        case 'u': o_fmt = &utf8; break;
        } /* switch */
    } /* while */

    argc -= optind;
    argv += optind;

    if (argc) {
        int i;
        for (i = 0; i < argc; i++) {
            FILE *f = fopen(argv[i], "rt");
            if (!f) {
                fprintf(stderr,
                    F("%s: %s\n"),
                    argv[i], strerror(errno));
                exit(EXIT_FAILURE);
            }
            process(argv[i], f);
            fclose(f);
        }
    } else {
        process("stdin", stdin);
    }
}
