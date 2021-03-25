#include <set>
#include <random>
#include <iostream>

#include <benchmark/benchmark.h>

#include "splaytree.h"
#include "avltree.h"
#include "rbwrap.h"

#define NUMBER_ELEMENTS 100000

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 2 * NUMBER_ELEMENTS);

int values[NUMBER_ELEMENTS];

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
inline int compare(T2 *lhs, T2 *rhs) {
  T *aa = _get_entry(lhs, T, node);
  T *bb = _get_entry(rhs, T, node);
  if (aa->key == bb->key) return 0;
  return aa->key - bb->key;
}

// all benchmarks
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

static void BM_SETSet_Append(benchmark::State& state) {
  for (auto _ : state) {
    std::set<int> data;

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data.insert(idx + 1);
    }
  }
}

static void BM_SplayTree_InsertRandom(benchmark::State& state) {
  for (auto _ : state) {
    struct splay_tree tree;
    struct kv_node data[NUMBER_ELEMENTS];

    splay_tree_init(&tree);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = values[idx];
      splay_insert(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
    }
  }
}

static void BM_AVLTree_InsertRandom(benchmark::State& state) {
  for (auto _ : state) {
    struct avl_tree tree;
    struct kv_node_avl data[NUMBER_ELEMENTS];

    avl_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = values[idx];
      avl_insert(&tree, &data[idx].node, compare<kv_node_avl, struct avl_node>);
    }
  }
}

static void BM_RBTree_InsertRandom(benchmark::State& state) {
  for (auto _ : state) {
    struct rb_root tree;
    struct kv_node_rb data[NUMBER_ELEMENTS];

    rb_root_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = values[idx];
      rbwrap_insert(&tree, &data[idx].node, compare<kv_node_rb, struct rb_node>);
    }
  }
}

static void BM_STLSet_InsertRandom(benchmark::State& state) {
  for (auto _ : state) {
    std::set<int> data;

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data.insert(values[idx]);
    }
  }
}

static void BM_SplayTree_LoopSequentially(benchmark::State& state) {
  struct splay_tree tree;
  struct kv_node data[NUMBER_ELEMENTS];

  splay_tree_init(&tree);

  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    data[idx].key = idx + 1;
    splay_insert(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
  }
  for (auto _ : state) {
    splay_node *cur = splay_first(&tree);
    for(int idx = 1; idx < NUMBER_ELEMENTS; idx ++) {
      cur = splay_next(&tree, cur, compare<kv_node, struct splay_node>);
    }
  }
}

static void BM_AVLTree_LoopSequentially(benchmark::State& state) {
  struct avl_tree tree;
  struct kv_node_avl data[NUMBER_ELEMENTS];

  avl_init(&tree, NULL);

  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    data[idx].key = idx + 1;
    avl_insert(&tree, &data[idx].node, compare<kv_node_avl, struct avl_node>);
  }
  for (auto _ : state) {
    avl_node *cur = avl_first(&tree);
    for(int idx = 1; idx < NUMBER_ELEMENTS; idx ++) {
      cur = avl_next(cur);
    }
  }
}

static void BM_RBTree_LoopSequentially(benchmark::State& state) {
  struct rb_root tree;
  struct kv_node_rb data[NUMBER_ELEMENTS];

  rb_root_init(&tree, NULL);

  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    data[idx].key = idx + 1;
    rbwrap_insert(&tree, &data[idx].node, compare<kv_node_rb, struct rb_node>);
  }
  for (auto _ : state) {
    rb_node *cur = rb_first(&tree);
    for(int idx = 1; idx < NUMBER_ELEMENTS; idx ++) {
      cur = rb_next(cur);
    }
  }
}

static void BM_SplayTree_SearchRandomly(benchmark::State& state) {
  struct splay_tree tree;
  struct kv_node data[NUMBER_ELEMENTS];

  splay_tree_init(&tree);

  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    data[idx].key = idx + 1;
    splay_insert(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
  }

  for (auto _ : state) {
    kv_node query;
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      query.key = values[idx];
      auto cur = splay_search(&tree, &query.node, compare<kv_node, struct splay_node>);
    }
  }
}

static void BM_AVLTree_SearchRandomly(benchmark::State& state) {
  struct avl_tree tree;
  struct kv_node_avl data[NUMBER_ELEMENTS];

  avl_init(&tree, NULL);

  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    data[idx].key = idx + 1;
    avl_insert(&tree, &data[idx].node, compare<kv_node_avl, struct avl_node>);
  }

  for (auto _ : state) {
    kv_node_avl query;
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      query.key = values[idx];
      auto cur = avl_search(&tree, &query.node, compare<kv_node_avl, struct avl_node>);
    }
  }
}

static void BM_RBTree_SearchRandomly(benchmark::State& state) {
  struct rb_root tree;
  struct kv_node_rb data[NUMBER_ELEMENTS];

  rb_root_init(&tree, NULL);

  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    data[idx].key = idx + 1;
    rbwrap_insert(&tree, &data[idx].node, compare<kv_node_rb, struct rb_node>);
  }

  for (auto _ : state) {
    kv_node_rb query;
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      query.key = values[idx];
      auto cur = rbwrap_search(&tree, &query.node, compare<kv_node_rb, struct rb_node>);
    }
  }
}

static void BM_SplayTree_AppendAndDeleteSequentially(benchmark::State& state) {
  struct splay_tree tree;
  struct kv_node data[NUMBER_ELEMENTS];

  for (auto _ : state) {
    splay_tree_init(&tree);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      splay_insert(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
    }

    for(int idx = NUMBER_ELEMENTS - 1; idx >= 0; idx --) {
      splay_delete(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
    }
  }
}

static void BM_AVLTree_AppendAndDeleteSequentially(benchmark::State& state) {
  struct avl_tree tree;
  struct kv_node_avl data[NUMBER_ELEMENTS];

  for (auto _ : state) {
    avl_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      avl_insert(&tree, &data[idx].node, compare<kv_node_avl, struct avl_node>);
    }

    for(int idx = NUMBER_ELEMENTS - 1; idx >= 0; idx --) {
      avl_remove(&tree, &data[idx].node);
    }
  }
}

static void BM_RBTree_AppendAndDeleteSequentially(benchmark::State& state) {
  struct rb_root tree;
  struct kv_node_rb data[NUMBER_ELEMENTS];

  for (auto _ : state) {
    rb_root_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      rbwrap_insert(&tree, &data[idx].node, compare<kv_node_rb, struct rb_node>);
    }

    for(int idx = NUMBER_ELEMENTS - 1; idx >= 0; idx --) {
      rb_erase(&data[idx].node, &tree);
    }
  }
}

static void BM_STLSet_AppendAndDeleteSequentially(benchmark::State& state) {
  std::set<int> data;

  for (auto _ : state) {
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data.insert(idx + 1);
    }

    for(int idx = NUMBER_ELEMENTS - 1; idx >= 0; idx --) {
      data.erase(idx + 1);
    }
  }
}

static void BM_SplayTree_AppendAndDeleteRandomly(benchmark::State& state) {
  struct splay_tree tree;
  struct kv_node data[NUMBER_ELEMENTS];

  for (auto _ : state) {
    splay_tree_init(&tree);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      splay_insert(&tree, &data[idx].node, compare<kv_node, struct splay_node>);
    }

    kv_node query;
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      query.key = values[idx];
      splay_delete(&tree, &query.node, compare<kv_node, struct splay_node>);
    }
  }
}

static void BM_AVLTree_AppendAndDeleteRandomly(benchmark::State& state) {
  struct avl_tree tree;
  struct kv_node_avl data[NUMBER_ELEMENTS];

  for (auto _ : state) {
    avl_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      avl_insert(&tree, &data[idx].node, compare<kv_node_avl, struct avl_node>);
    }

    kv_node_avl query;
    avl_node *cursor;
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      query.key = values[idx];
      cursor = avl_search(&tree, &query.node, compare<kv_node_avl, struct avl_node>);
      avl_remove(&tree, cursor);
    }
  }
}

static void BM_RBTree_AppendAndDeleteRandomly(benchmark::State& state) {
  struct rb_root tree;
  struct kv_node_rb data[NUMBER_ELEMENTS];

  for (auto _ : state) {
    rb_root_init(&tree, NULL);

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data[idx].key = idx + 1;
      rbwrap_insert(&tree, &data[idx].node, compare<kv_node_rb, struct rb_node>);
    }

    kv_node_rb query;
    rb_node *cursor;
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      query.key = values[idx];
      cursor = rbwrap_search(&tree, &query.node, compare<kv_node_rb, struct rb_node>);
      rb_erase(cursor, &tree);
    }
  }
}

static void BM_STLSet_AppendAndDeleteRandomly(benchmark::State& state) {
  std::set<int> data;

  for (auto _ : state) {
    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data.insert(idx + 1);
    }

    for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
      data.erase(values[idx]);
    }
  }
}

BENCHMARK(BM_SplayTree_Append);
BENCHMARK(BM_AVLTree_Append);
BENCHMARK(BM_RBTree_Append);
BENCHMARK(BM_SETSet_Append);
BENCHMARK(BM_SplayTree_InsertRandom);
BENCHMARK(BM_AVLTree_InsertRandom);
BENCHMARK(BM_RBTree_InsertRandom);
BENCHMARK(BM_STLSet_InsertRandom);
BENCHMARK(BM_SplayTree_LoopSequentially);
BENCHMARK(BM_AVLTree_LoopSequentially);
BENCHMARK(BM_RBTree_LoopSequentially);
BENCHMARK(BM_SplayTree_SearchRandomly);
BENCHMARK(BM_AVLTree_SearchRandomly);
BENCHMARK(BM_RBTree_SearchRandomly);
BENCHMARK(BM_SplayTree_AppendAndDeleteSequentially);
BENCHMARK(BM_AVLTree_AppendAndDeleteSequentially);
BENCHMARK(BM_RBTree_AppendAndDeleteSequentially);
BENCHMARK(BM_STLSet_AppendAndDeleteSequentially);
BENCHMARK(BM_SplayTree_AppendAndDeleteRandomly);
BENCHMARK(BM_AVLTree_AppendAndDeleteRandomly);
BENCHMARK(BM_RBTree_AppendAndDeleteRandomly);
BENCHMARK(BM_STLSet_AppendAndDeleteRandomly);

int main(int argc, char** argv)
{
  // construct discrete normal distribution for benchmarking
  for(int idx = 0; idx < NUMBER_ELEMENTS; idx ++) {
    values[idx] = distribution(generator);
  }

  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}