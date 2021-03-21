#include <benchmark/benchmark.h>

#include <set>

#include "splaytree.h"
#include "avltree.h"

#define NUMBER_ELEMENTS 100000

// custom structs
struct kv_node {
  struct splay_node node;
  int key;
};

struct kv_node_avl {
  struct avl_node node;
  int key;
};

// custom comparison funcs
int splay_compare(struct splay_node *lhs, struct splay_node *rhs) {
  kv_node *aa = _get_entry(lhs, struct kv_node, node);
  kv_node *bb = _get_entry(rhs, struct kv_node, node);
  if (aa->key == bb->key) return 0;
  return aa->key - bb->key;
}

int avl_compare(struct avl_node *lhs, struct avl_node *rhs, void *aux) {
  kv_node_avl *aa, *bb;
  aa = _get_entry(lhs, struct kv_node_avl, node);
  bb = _get_entry(rhs, struct kv_node_avl, node);
  if (aa->key < bb->key) return -1;
  else if (aa->key > bb->key) return 1;
  else return 0;
}

static void BM_SplayTree_Append(benchmark::State& state) {
  for (auto _ : state) {
    struct splay_tree tree;
    struct kv_node data[NUMBER_ELEMENTS];

    splay_tree_init(&tree);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      splay_insert(&tree, &data[idx].node, splay_compare);
    }
  }
}

static void BM_AVLTree_Append(benchmark::State& state) {
  for (auto _ : state) {
    struct avl_tree tree;
    struct kv_node_avl data[NUMBER_ELEMENTS];

    avl_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      avl_insert(&tree, &data[idx].node, avl_compare);
    }
  }
}

BENCHMARK(BM_SplayTree_Append);
BENCHMARK(BM_AVLTree_Append);

BENCHMARK_MAIN();