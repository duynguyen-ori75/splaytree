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

### Insert

```shell
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BM_SplayTree_Append                      1070687 ns      1070671 ns          616
BM_AVLTree_Append                        6052282 ns      6052101 ns          110
BM_RBTree_Append                        10331639 ns     10331078 ns           67
BM_SETSet_Append                        11637510 ns     11637190 ns           59
BM_SplayTree_InsertNormalDistribution    1480339 ns      1480310 ns          462
BM_AVLTree_InsertNormalDistribution      4291937 ns      4291771 ns          163
BM_RBTree_InsertNormalDistribution       4239753 ns      4239613 ns          165
BM_STLSet_InsertNormalDistribution       3142497 ns      3142363 ns          224
```

### Read

```shell
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BM_SplayTree_LoopSequentially             169402 ns       169399 ns         4015
BM_AVLTree_LoopSequentially               194693 ns       194689 ns         3585
BM_RBTree_LoopSequentially                416551 ns       416548 ns         1670
BM_SplayTree_SearchRandomly             20572787 ns     20571949 ns           34
BM_AVLTree_SearchRandomly               18230235 ns     18229793 ns           38
BM_RBTree_SearchRandomly                17461417 ns     17461152 ns           40
```

## DOING

- [ ] Add parent node to `struct SplayNode`
  - This can improve `Next` & `Prev` performance
- [ ] Compare it with other BST such as AVL tree
  - [x] Append workload
  - [x] Insert normal-distributed data
  - [x] Loop sequentially
  - [x] Random access workload
  - [ ] Read normal-distributed data
  - [ ] Delete sequentially
  - [ ] Delete randomly