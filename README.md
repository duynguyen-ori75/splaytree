# Splay tree

A highly-performant, zero-allocation, generic Top-down Splay tree container C implementation
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
-----------------------------------------------------------------------------------
Benchmark                                         Time             CPU   Iterations
-----------------------------------------------------------------------------------
BM_SplayTree_Append                          893396 ns       893380 ns          745
BM_AVLTree_Append                           6732141 ns      6731827 ns          108
BM_RBTree_Append                           11641723 ns     11640964 ns           60
BM_SETSet_Append                           13476920 ns     13474503 ns           49
BM_SplayTree_InsertRandom                  30806665 ns     30804999 ns           24
BM_AVLTree_InsertRandom                    21056514 ns     21055038 ns           36
BM_RBTree_InsertRandom                     18100314 ns     18099266 ns           33
BM_STLSet_InsertRandom                     21124374 ns     21123272 ns           29
```

### Read

```shell
-----------------------------------------------------------------------------------
Benchmark                                         Time             CPU   Iterations
-----------------------------------------------------------------------------------
BM_SplayTree_LoopSequentially                303221 ns       303212 ns         3146
BM_AVLTree_LoopSequentially                  257261 ns       257235 ns         2597
BM_RBTree_LoopSequentially                   621691 ns       621688 ns         1162
BM_SplayTree_SearchRandomly                12602530 ns     12602084 ns           54
BM_AVLTree_SearchRandomly                  18538304 ns     18537981 ns           50
BM_RBTree_SearchRandomly                   25190172 ns     25188291 ns           26

```

### Delete

```shell
-----------------------------------------------------------------------------------
Benchmark                                         Time             CPU   Iterations
-----------------------------------------------------------------------------------
BM_SplayTree_AppendAndDeleteSequentially    2803788 ns      2803400 ns          341
BM_AVLTree_AppendAndDeleteSequentially      8889289 ns      8888874 ns           83
BM_RBTree_AppendAndDeleteSequentially      12369922 ns     12369579 ns           56
BM_STLSet_AppendAndDeleteSequentially      18282490 ns     18282198 ns           31
BM_SplayTree_AppendAndDeleteRandomly       25137365 ns     25135925 ns           44
BM_AVLTree_AppendAndDeleteRandomly         23279374 ns     23278243 ns           26
BM_RBTree_AppendAndDeleteRandomly          26932176 ns     26931465 ns           27
BM_STLSet_AppendAndDeleteRandomly          22129408 ns     22127794 ns           30
```

## DOING

- [ ] Add parent node to `struct SplayNode`
  - This can improve `Next` & `Prev` performance