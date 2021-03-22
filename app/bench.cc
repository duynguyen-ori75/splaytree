#include <benchmark/benchmark.h>

#include <set>

#include "splaytree.h"
#include "avltree.h"
#include "rbwrap.h"

#define NUMBER_ELEMENTS 100000

// custom structs
class kv_node {
public:
  splay_node node;
  int key;
};

class kv_node_avl {
public:
  avl_node node;
  int key;
};

class kv_node_rb {
public:
  rb_node node;
  int key;
};

// custom comparison funcs
template <typename T, typename T2>
int compare(T2 *lhs, T2 *rhs) {
  auto *aa = _get_entry(lhs, T, node);
  auto *bb = _get_entry(rhs, T, node);
  if (aa->key == bb->key) return 0;
  return aa->key - bb->key;
}

static void BM_SplayTree_Append(benchmark::State& state) {
  for (auto _ : state) {
    struct splay_tree tree;
    struct kv_node data[NUMBER_ELEMENTS];

    splay_tree_init(&tree);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      splay_insert(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
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
      avl_insert(&tree, &data[idx].node, compare<kv_node_avl, struct avl_node>);
    }
  }
}

static void BM_RBTree_Append(benchmark::State& state) {
  for (auto _ : state) {
    struct rb_root tree;
    struct kv_node_rb data[NUMBER_ELEMENTS];

    rb_root_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      rbwrap_insert(&tree, &data[idx].node, compare<kv_node_rb, struct rb_node>);
    }
  }
}

BENCHMARK(BM_SplayTree_Append);
BENCHMARK(BM_AVLTree_Append);
BENCHMARK(BM_RBTree_Append);

BENCHMARK_MAIN();