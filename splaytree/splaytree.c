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

#ifndef INLINE
  #ifdef __linux__
    #define INLINE static inline
  #else
    #define INLINE
  #endif
#endif

#include "splaytree.h"

INLINE struct splay_node *_right_rotate(struct splay_node *x) {
  struct splay_node *y = x->left;
  x->left = y->right;
  y->right = x;
  return y;
}

INLINE struct splay_node *_left_rotate(struct splay_node *x) {
  struct splay_node *y = x->right;
  x->right = y->left;
  y->left = x;
  return y;
}

INLINE void _init_splay_node(struct splay_node* p) {
  p->left = p->right = NULL;
#ifdef _SPLAY_SIBLING_POINTER
  p->prev = p->next = NULL;
#endif
}

struct splay_node *_splay(struct splay_node *root,
                          struct splay_node *query,
                          compare_func *func) {
  if (!root) return root;
  struct splay_node N;
  N.left = N.right = NULL;
  struct splay_node *left_t, *right_t;
  left_t = right_t = &N;

  for (;;) {
    int cmp = func(root, query);
    if (cmp == 0) break;

    if (cmp > 0) {
      if (!root->left) break;

      if (func(root->left, query) > 0) {
        root = _right_rotate(root);
        if (!root->left) break;
      }
      right_t->left = root;
      right_t = root;
      root = root->left;
    } else {
      if (!root->right) break;

      if (func(root->right, query) < 0) {
        root = _left_rotate(root);
        if(!root->right) break;
      }

      left_t->right = root;
			left_t = root;
			root = root->right;
    }
  }

  left_t->right = root->left;
  right_t->left = root->right;
  root->left = N.right;
  root->right = N.left;
  return root;
}

/**
 * @brief    Below is the implementation of all public functions
 */
void splay_tree_init(struct splay_tree *tree) {
  tree->root = NULL;
}

void splay_insert(struct splay_tree *tree, struct splay_node *node, compare_func *func) {
  _init_splay_node(node);

  if (tree->root) {
    tree->root = _splay(tree->root, node, func);
    int cmp = func(tree->root, node);
    if (cmp == 0) return;
    if (cmp > 0) {
      node->right       = tree->root;
      node->left        = tree->root->left;
      tree->root->left  = NULL;
#ifdef _SPLAY_SIBLING_POINTER
      node->next        = tree->root;
      node->prev        = tree->root->prev;
      if (tree->root->prev) {
        tree->root->prev->next = node;
      }
      tree->root->prev  = node;
#endif
    } else {
      node->left        = tree->root;
      node->right       = tree->root->right;
      tree->root->right = NULL;
#ifdef _SPLAY_SIBLING_POINTER
      node->prev        = tree->root;
      node->next        = tree->root->next;
      if (tree->root->next) {
        tree->root->next->prev = node;
      }
      tree->root->next  = node;
#endif
    }
  }

  tree->root = node;
}

void splay_delete(struct splay_tree *tree, struct splay_node *node, compare_func *func) {
  if (!tree->root) return;

  tree->root = _splay(tree->root, node, func);
  if (func(tree->root, node) != 0) return;

  if (!tree->root->left) {
#ifdef _SPLAY_SIBLING_POINTER
    if (tree->root->next)
      tree->root->next->prev = NULL;
    tree->root->next = NULL;
#endif
    tree->root = tree->root->right;
  } else {
    struct splay_node **root = &tree->root;
    // splay the biggest node of the left subtree to the top, and then attach current right-subtree to that node
    struct splay_node *pp = NULL, *p;
    for (p = (*root)->left; p->right; p = p->right) {
      pp = p;
    }
    if (pp) {
      pp->right = p->left;
      p->left = (*root)->left;
      (*root)->left = p;
    }

    p->right = (*root)->right;
#ifdef _SPLAY_SIBLING_POINTER
    p->next = (*root)->next;
    if ((*root)->next) {
      (*root)->next->prev = p;
    }
#endif
    *root = p;
  }
}

struct splay_node* splay_search(struct splay_tree *tree, struct splay_node *node, compare_func *func) {
  tree->root = _splay(tree->root, node, func);
  if (func(tree->root, node) == 0) {
    return tree->root;
  }

  return NULL;
}

struct splay_node* splay_search_lower(struct splay_tree *tree, struct splay_node *node, compare_func *func) {
  tree->root = _splay(tree->root, node, func);
  if (func(tree->root, node) <= 0) {
    return tree->root;
  }

  if (!tree->root->left) return NULL;
  struct splay_node *cur;

  for (cur = tree->root->left; cur->right; cur = cur->right) {}
  return cur;
}

struct splay_node* splay_search_greater(struct splay_tree *tree, struct splay_node *node, compare_func *func) {
  tree->root = _splay(tree->root, node, func);
  if (func(tree->root, node) >= 0) {
    return tree->root;
  }

  if (!tree->root->right) return NULL;
  struct splay_node *cur;

  for (cur = tree->root->right; cur->left; cur = cur->left) {}
  return cur;
}

struct splay_node* splay_first(struct splay_tree *tree, bool to_splay) {
  if (!tree->root) return NULL;
  struct splay_node *p, *pp = NULL;
  for(p = tree->root; p->left; p = p->left) {
    pp = p;
  }
  if (pp && to_splay) {
    pp->left = p->right;
    p->right = tree->root;
    tree->root = p;
  }
  return p;
}

struct splay_node* splay_last(struct splay_tree *tree, bool to_splay) {
  if (!tree->root) return NULL;
  struct splay_node *p, *pp = NULL;
  for(p = tree->root; p->right; p = p->right) {
    pp = p;
  }
  if (pp && to_splay) {
    pp->right = p->left;
    p->left = tree->root;
    tree->root = p;
  }
  return p;
}

struct splay_node* splay_prev(struct splay_tree *tree, struct splay_node *node, compare_func *func) {

#ifdef _SPLAY_SIBLING_POINTER
  return node->prev;
#endif

  struct splay_node *p;
  if (node->left) goto move_prev;
  tree->root = _splay(tree->root, node, func);

move_prev:
  for(p = node->left; p && p->right; p = p->right) {}
  return p;
}

struct splay_node* splay_next(struct splay_tree *tree, struct splay_node *node, compare_func *func) {

#ifdef _SPLAY_SIBLING_POINTER
  return node->next;
#endif

  struct splay_node *p;
  if (node->right) goto move_next;
  tree->root = _splay(tree->root, node, func);

move_next:
  for(p = node->right; p && p->left; p = p->left) {}
  return p;
}