/*
Copyright (C) 2021-present Duy Nguyen <duynguyen.ori75@gmail.com>
All rights reserved.

Last modification: Mar 14, 2021

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _DUYNGUYEN_SPLAY_TREE
#define _DUYNGUYEN_SPLAY_TREE

#include "stdint.h"

#define _get_entry(ELEM, STRUCT, MEMBER) ((STRUCT *) ((int8_t *) (ELEM) - offsetof (STRUCT, MEMBER)))

#ifdef __cplusplus

#include <cstdio>

extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>

struct splay_node {
  struct splay_node *left, *right;

#ifdef _SPLAY_SIBLING_POINTER
  struct splay_node *prev, next;
#endif
};

struct splay_tree {
  struct splay_node *root;
};

typedef int compare_func (struct splay_node *a, struct splay_node *b);

void splay_tree_init(struct splay_tree *tree);
void splay_insert(struct splay_tree *tree, struct splay_node *node, compare_func *func);
void splay_delete(struct splay_tree *tree, struct splay_node *node, compare_func *func);

struct splay_node* splay_search(struct splay_tree *tree, struct splay_node *node, compare_func *func);
struct splay_node* splay_search_lower(struct splay_tree *tree, struct splay_node *node, compare_func *func);
struct splay_node* splay_search_greater(struct splay_tree *tree, struct splay_node *node, compare_func *func);
struct splay_node* splay_first(struct splay_tree *tree, bool to_splay);
struct splay_node* splay_last(struct splay_tree *tree, bool to_splay);
struct splay_node* splay_prev(struct splay_tree *tree, struct splay_node *node, compare_func *func);
struct splay_node* splay_next(struct splay_tree *tree, struct splay_node *node, compare_func *func);

#ifdef __cplusplus
}
#endif

#endif