#include <stdlib.h>
#include <stdio.h>

#include "splaytree.h"

struct set_node {
  int key;

  struct splay_node node;
};

int cmp_func(struct splay_node *lhs, struct splay_node *rhs) {
  int leftKey   = _get_entry(lhs, struct set_node, node)->key;
  int rightKey  = _get_entry(rhs, struct set_node, node)->key;
  return leftKey - rightKey;
}

int main(int argc, char **argv) {
  struct set_node data[100];
  struct splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 0; i < 100; i ++) {
    data[i].key = i * 2 + 1;
    splay_insert(&tree, &data[i].node, cmp_func);
  }

  struct set_node query, *result;
  struct splay_node *cur;
  for(int i = 0; i < 200; i ++) {
    query.key = i;
    cur = splay_search(&tree, &query.node, cmp_func);
    result = _get_entry(cur, struct set_node, node);
    if (cur) printf("key %d\n", result->key);
  }

  for(int i = 0; i < 100; i ++) {
    query.key = rand() % 200;
    splay_delete(&tree, &query.node, cmp_func);
  }
}