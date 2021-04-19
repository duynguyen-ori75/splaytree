/*
 * Copyright 2013 Jung-Sang Ahn <jungsang.ahn@gmail.com>.
 * All Rights Reserved.
 */

#include "rbwrap.h"

void rbwrap_init(struct rb_root *root, void *aux)
{
  root->rb_node = NULL;
  root->aux = aux;
}

struct rb_node * __rbwrap_insert(struct rb_root *root, struct rb_node *node, rbwrap_cmp_func *func)
{
  struct rb_node ** p = &root->rb_node;
  struct rb_node * parent = NULL;
  int cmp;

  while (*p)
  {
    parent = *p;

    cmp = func(node, *p);
    if (cmp < 0)
      p = &(*p)->rb_left;
    else if (cmp > 0)
      p = &(*p)->rb_right;
    else
      return *p;
  }

  if (parent) {
    rb_link_node(node, parent, p);
#ifdef _RB_NEXT_POINTER
    if(func(parent, node) > 0) {
      node->next = parent;
      node->prev = parent->prev;
      if (parent->prev) parent->prev->next = node;
      parent->prev = node;
    } else {
      node->prev = parent;
      node->next = parent->next;
      if (parent->next) parent->next->prev = node;
      parent->next = node;
    }
#endif
  } else
    rb_root_init(root, node);

  return NULL;
}

struct rb_node * rbwrap_insert(struct rb_root *root, struct rb_node *node, rbwrap_cmp_func *func)
{
  struct rb_node *ret;
  if ((ret = __rbwrap_insert(root, node, func)))
    goto out;
  rb_insert_color(node, root);
 out:
  return ret;
}

struct rb_node * rbwrap_search(struct rb_root *root, struct rb_node *node, rbwrap_cmp_func *func)
{
  struct rb_node * n = root->rb_node;
  int cmp;
  //struct page * page;

  while (n)
  {
    cmp = func(node, n);
    if (cmp < 0)
      n = n->rb_left;
    else if (cmp > 0)
      n = n->rb_right;
    else
      return n;
  }
  return NULL;
}



