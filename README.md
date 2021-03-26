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
BM_SplayTree_Append                            1017354 ns      1017263 ns          663
BM_AVLTree_Append                              6918081 ns      6917612 ns           96
BM_RBTree_Append                              10961181 ns     10960508 ns           63
BM_SETSet_Append                              13630910 ns     13630563 ns           49
BM_SplayTree_InsertRandom                     31168269 ns     31165379 ns           23
BM_AVLTree_InsertRandom                       24851447 ns     24850110 ns           33
BM_RBTree_InsertRandom                        18365015 ns     18358429 ns           35
BM_STLSet_InsertRandom                        26893658 ns     26891748 ns           28
```

### Read

```shell
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
BM_SplayTree_LoopSequentially                   250616 ns       250582 ns         2364
BM_AVLTree_LoopSequentially                     405245 ns       405237 ns         2381
BM_RBTree_LoopSequentially                      572293 ns       572270 ns         1295
BM_SplayTree_SearchRandomly                   15944143 ns     15939557 ns           52
BM_AVLTree_SearchRandomly                     15260678 ns     15259896 ns           43
BM_RBTree_SearchRandomly                      16419298 ns     16418330 ns           42
```

### Delete

```shell
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
BM_SplayTree_DeleteSequentially/manual_time     969269 ns      1986797 ns          689
BM_AVLTree_DeleteSequentially/manual_time      2159975 ns      8794835 ns          309
BM_RBTree_DeleteSequentially/manual_time       1595580 ns     12835528 ns          454
BM_STLSet_DeleteSequentially/manual_time       6897836 ns     18574547 ns          100
BM_SplayTree_DeleteRandomly/manual_time       16290044 ns     17275631 ns           41
BM_AVLTree_DeleteRandomly/manual_time         17672245 ns     24342404 ns           38
BM_RBTree_DeleteRandomly/manual_time          15505911 ns     26651997 ns           46
BM_STLSet_DeleteRandomly/manual_time          15731303 ns     24006003 ns           39
```

## DOING

- [ ] Add parent node to `struct SplayNode`
  - This can improve `Next` & `Prev` performance