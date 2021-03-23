# Splay tree

A highly-performant, zero-allocation, generic Top-down Splay tree container C implementation

## Author

Duy Nguyen <duynguyen.ori75@gmail.com>

## Build

Prerequisites for test and benchmark: [googletest](https://github.com/google/googletest) and [gbenchmark](https://github.com/google/benchmark)

```sh
make
```

## How to use

(refer to [app/example.c](app/example.c))

Below example describes how to use the splay tree as an ordered set of int

```C
struct set_node {
  int key;

  struct splay_node node;
};

int cmp_func(struct splay_node *lhs, struct splay_node *rhs) {
  int leftKey   = _get_entry(lhs, data_node, node)->key;
  int rightKey  = _get_entry(rhs, data_node, node)->key;
  return leftKey - rightKey;
}
```

* Tree initialization

```C
struct splay_tree tree;
splay_tree_init(&tree);
```

* Insert operation

```C
data[i].key = i * 2 + 1;
splay_insert(&tree, &data[i].node, cmp_func);
```

* Search operation

```C
struct set_node query, *result;
struct splay_node *cur;
query.key = i;
cur = splay_search(&tree, &query.node, cmp_func);
result = _get_entry(cur, set_node, node);
```

* Delete operation

```C
query.key = rand() % 200;
splay_delete(&tree, &query.node, cmp_func);
```

## Benchmark

### Competitor

- [AVL Tree](https://github.com/greensky00/avltree) by Jung-Sang Ahn
- [Red-black Tree](https://github.com/greensky00/avltree/blob/master/rbtree/rbtree.c) by Andrea Arcangeli and David Woodhouse
  - Thank Jung-Sang Ahn for his excellent wrapper
- [STL Set](https://en.cppreference.com/w/cpp/container/set)

### Setup

For benchmark implementation, please check `app/bench.cc`

Machine setup (info from google benchmark output):

```shell
Run on (12 X 4600 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
```

### Insert result

```shell
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BM_SplayTree_Append                      1063859 ns      1063843 ns          614
BM_AVLTree_Append                        6093468 ns      6093298 ns          111
BM_RBTree_Append                        10684335 ns     10684150 ns           64
BM_SETSet_Append                        11836129 ns     11835528 ns           57
BM_SplayTree_InsertNormalDistribution    1508689 ns      1508672 ns          449
BM_AVLTree_InsertNormalDistribution      4542861 ns      4542757 ns          155
BM_RBTree_InsertNormalDistribution       4234119 ns      4234045 ns          163
BM_STLSet_InsertNormalDistribution       3179226 ns      3179136 ns          224
```

## DOING

- [ ] Add parent node to `struct SplayNode`
  - This can improve `Next` & `Prev` performance
- [ ] Compare it with other BST such as AVL tree
  - [x] Append workload
  - [x] Insert normal-distributed data
  - [ ] Loop sequentially
  - [ ] Random access workload
  - [ ] Read normal-distributed data
  - [ ] Delete sequentially
  - [ ] Delete randomly