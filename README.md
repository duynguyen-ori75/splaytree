# Splay tree

An extremely-performant, zero-allocation, generic Top-down Splay tree container C implementation

See [Benchmark](README.md#Benchmark) for more information

## Author

Duy Nguyen <duynguyen.ori75@gmail.com>

## Build

Prerequisites for test and benchmark: [googletest](https://github.com/google/googletest) and [gbenchmark](https://github.com/google/benchmark)

```sh
make
```

## How to use

(refer to [app/example.c](app/example.c))

The below example describes how to use the splay tree as an ordered set of int

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
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
BM_SplayTree_Append                             830776 ns       830315 ns          787
BM_AVLTree_Append                              6341931 ns      6323088 ns          109
BM_RBTree_Append                              10318031 ns     10317710 ns           66
BM_SETSet_Append                              12867489 ns     12866331 ns           52
BM_SplayTree_InsertRandom                     24312953 ns     24312061 ns           29
BM_AVLTree_InsertRandom                       16879571 ns     16879077 ns           45
BM_RBTree_InsertRandom                        15648496 ns     15647667 ns           45
BM_STLSet_InsertRandom                        15884286 ns     15883431 ns           44
```

### Read

```shell
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
BM_SplayTree_LoopSequentially                   187054 ns       187039 ns         3925
BM_AVLTree_LoopSequentially                     212804 ns       212792 ns         2693
BM_RBTree_LoopSequentially                      195317 ns       195311 ns         3498
BM_SplayTree_SearchRandomly                   10500778 ns     10500449 ns           62
BM_AVLTree_SearchRandomly                     11503245 ns     11502942 ns           59
BM_RBTree_SearchRandomly                      13729135 ns     13728468 ns           50
```

### Delete

```shell
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
BM_SplayTree_DeleteSequentially/manual_time     626204 ns      1432835 ns         1090
BM_AVLTree_DeleteSequentially/manual_time      1076986 ns      7078598 ns          636
BM_RBTree_DeleteSequentially/manual_time        919476 ns     11364359 ns          816
BM_STLSet_DeleteSequentially/manual_time       5635167 ns     14522470 ns          100
BM_SplayTree_DeleteRandomly/manual_time       12537206 ns     13379025 ns           55
BM_AVLTree_DeleteRandomly/manual_time         13497176 ns     19570971 ns           55
BM_RBTree_DeleteRandomly/manual_time          13382582 ns     23816548 ns           53
BM_STLSet_DeleteRandomly/manual_time          11097296 ns     16613821 ns           60
```
