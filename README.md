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

## Append 100000 records

```
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BM_SplayTree_Append                       389557 ns       389553 ns         1754
BM_AVLTree_Append                        6424796 ns      6424738 ns          106
BM_RBTree_Append                        10069917 ns     10069844 ns           68
BM_SplayTree_InsertNormalDistribution     577347 ns       577335 ns         1113
BM_AVLTree_InsertNormalDistribution      4316927 ns      4316852 ns          161
BM_RBTree_InsertNormalDistribution       4407875 ns      4407830 ns          159
```

## DOING

- [ ] Compare it with other BST such as AVL tree
  - [x] Append workload
  - [x] Insert normal distributed data
  - [ ] Loop sequentially workload
  - [ ] Random access workload
  - [ ] Pareto workload - aka 80/20
  - [ ] Delete sequentially
  - [ ] Delete randomly