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
------------------------------------------------------------------------
Benchmark                              Time             CPU   Iterations
------------------------------------------------------------------------
BM_SplayTree_Append               764542 ns       764535 ns          821
BM_AVLTree_Append                6107497 ns      6107414 ns          112
BM_RBTree_Append                11673277 ns     11673082 ns           60
BM_SETSet_Append                11605675 ns     11605418 ns           47
BM_SplayTree_InsertRandom       23544878 ns     23544370 ns           30
BM_AVLTree_InsertRandom         15789308 ns     15788826 ns           43
BM_RBTree_InsertRandom          14514992 ns     14514668 ns           49
BM_STLSet_InsertRandom          15506062 ns     15505384 ns           44
```

### Read

```shell
------------------------------------------------------------------------
Benchmark                              Time             CPU   Iterations
------------------------------------------------------------------------
BM_SplayTree_LoopSequentially     175229 ns       175226 ns         3899
BM_AVLTree_LoopSequentially       205498 ns       205486 ns         3450
BM_RBTree_LoopSequentially        459855 ns       459850 ns         1744
BM_SplayTree_SearchRandomly     21681570 ns     21681261 ns           32
BM_AVLTree_SearchRandomly       25166856 ns     25166369 ns           29
BM_RBTree_SearchRandomly        23416536 ns     23415394 ns           35

```

## DOING

- [ ] Add parent node to `struct SplayNode`
  - This can improve `Next` & `Prev` performance
- [ ] Compare it with other BST such as AVL tree
  - [x] Append workload
  - [x] Insert randomly
  - [x] Loop sequentially
  - [x] Read random data
  - [ ] Delete sequentially
  - [ ] Delete randomly