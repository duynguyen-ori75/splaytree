#include <unordered_set>

#include <gtest/gtest.h>

extern "C" {

#include "splaytree.h"
#include "rbwrap.h"

}

struct data_node {
public:
  int key;
  splay_node node;
};

class kv_node_rb {
public:
  int key;
  rb_node node;
};

// custom comparison funcs
template <typename T, typename T2>
inline int compare(T2 *lhs, T2 *rhs) {
  T *aa = _get_entry(lhs, T, node);
  T *bb = _get_entry(rhs, T, node);
  return aa->key - bb->key;
}

TEST(SplayTree, InsertAndSearch) {
  data_node data[100];
  splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 0; i < 100; i ++) {
    data[i].key = i * 2 + 1;
    splay_insert(&tree, &data[i].node, compare<data_node, struct splay_node>);
  }

  data_node query, *result;
  splay_node *cur;
  int expectedKey;
  for(int i = 0; i < 200; i ++) {
    query.key = i;
    cur = splay_search(&tree, &query.node, compare<data_node, struct splay_node>);
    if (i % 2) {
      ASSERT_EQ(cur, tree.root);
      result = _get_entry(cur, data_node, node);
      ASSERT_EQ(result->key, i);
    } else {
      ASSERT_EQ(cur, nullptr);
    }

    cur = splay_search_lower(&tree, &query.node, compare<data_node, struct splay_node>);
    if (cur <= 0) {
      ASSERT_EQ(cur, nullptr);
    } else {
      result = _get_entry(cur, data_node, node);
      expectedKey = (i % 2) ? i : i - 1;
      ASSERT_EQ(result->key, expectedKey);
    }

    cur = splay_search_greater(&tree, &query.node, compare<data_node, struct splay_node>);
    result = _get_entry(cur, data_node, node);
    expectedKey = (i % 2) ? i : i + 1;
    ASSERT_EQ(result->key, expectedKey);
  }
}

TEST(SplayTree, InsertRandomly) {
  data_node data[1000];
  splay_tree tree;
  splay_tree_init(&tree);
  std::unordered_set<int> correct;

  for(int i = 0; i < 1000; i ++) {
    data[i].key = rand() % 10000;
    correct.insert(data[i].key);
    splay_insert(&tree, &data[i].node, compare<data_node, struct splay_node>);
  }

  data_node query, *result;
  splay_node *cur;
  for (int expectedKey: correct) {
    query.key = expectedKey;
    cur = splay_search(&tree, &query.node, compare<data_node, struct splay_node>);
    result = _get_entry(cur, data_node, node);
    ASSERT_EQ(result->key, expectedKey);
  }
}

TEST(SplayTree, RemoveOps) {
  data_node data[200];
  splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 0; i < 200; i ++) {
    data[i].key = i;
    splay_insert(&tree, &data[i].node, compare<data_node, struct splay_node>);
  }

  data_node query, *result;
  splay_node *cur, *nextCur, *prevCur;
  for(int i = 0; i < 100; i ++) {
    query.key = rand() % 200;
    cur = splay_search(&tree, &query.node, compare<data_node, struct splay_node>);
    prevCur = splay_prev(&tree, cur, compare<data_node, struct splay_node>);
    nextCur = splay_next(&tree, cur, compare<data_node, struct splay_node>);

    splay_delete(&tree, &query.node, compare<data_node, struct splay_node>);
    cur = splay_search(&tree, &query.node, compare<data_node, struct splay_node>);
    ASSERT_EQ(cur, nullptr);

    if (prevCur) {
      result = _get_entry(prevCur, data_node, node);
      ASSERT_LT(result->key, query.key);
    }

    if (nextCur) {
      result = _get_entry(nextCur, data_node, node);
      ASSERT_GT(result->key, query.key);
    }

    cur = splay_search_greater(&tree, &query.node, compare<data_node, struct splay_node>);
    if (cur) {
      result = _get_entry(cur, data_node, node);
      ASSERT_GT(result->key, query.key);
    }

    cur = splay_search_lower(&tree, &query.node, compare<data_node, struct splay_node>);
    if (cur) {
      result = _get_entry(cur, data_node, node);
      ASSERT_LT(result->key, query.key);
    }
  }
}

TEST(SplayTree, CursorOperator) {
  data_node data[201];
  splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 1; i <= 200; i ++) {
    data[i].key = i;
    splay_insert(&tree, &data[i].node, compare<data_node, struct splay_node>);
  }

  splay_node *cur = splay_first(&tree);
  data_node *result = _get_entry(cur, data_node, node);
  ASSERT_EQ(cur, tree.root);
  ASSERT_EQ(cur->left, nullptr);
  ASSERT_EQ(result->key, 1);
  for(int i = 2; i <= 201; i ++) {
    cur = splay_next(&tree, cur, compare<data_node, struct splay_node>);
    if (i == 201) {
      ASSERT_TRUE(cur == nullptr);
      break;
    }
    ASSERT_TRUE(cur != nullptr);
    data_node *result = _get_entry(cur, data_node, node);
    ASSERT_EQ(result->key, i);
  }

  cur = splay_last(&tree);
  result = _get_entry(cur, data_node, node);
  ASSERT_EQ(cur, tree.root);
  ASSERT_EQ(cur->right, nullptr);
  ASSERT_EQ(result->key, 200);
  for(int i = 199; i >= 0; i --) {
    cur = splay_prev(&tree, cur, compare<data_node, struct splay_node>);
    if (i == 0) {
      ASSERT_TRUE(cur == nullptr);
      break;
    }
    ASSERT_TRUE(cur != nullptr);
    data_node *result = _get_entry(cur, data_node, node);
    ASSERT_EQ(result->key, i);
  }
}

TEST(RedBlackTree, CursorOperation) {
  kv_node_rb data[201];
  rb_root tree;
  rb_root_init(&tree, NULL);

  for(int i = 1; i <= 200; i ++) {
    data[i].key = i;
    rbwrap_insert(&tree, &data[i].node, compare<kv_node_rb, struct rb_node>);
  }

  rb_node *cur = rb_first(&tree);
  kv_node_rb *result = _get_entry(cur, kv_node_rb, node);
  ASSERT_EQ(cur->rb_left, nullptr);
  ASSERT_EQ(result->key, 1);
  for(int i = 2; i <= 201; i ++) {
    cur = rb_next(cur);
    if (i == 201) {
      ASSERT_TRUE(cur == nullptr);
      break;
    }
    ASSERT_TRUE(cur != nullptr);
    kv_node_rb *result = _get_entry(cur, kv_node_rb, node);
    ASSERT_EQ(result->key, i);
  }

  cur = rb_last(&tree);
  result = _get_entry(cur, kv_node_rb, node);
  ASSERT_EQ(cur->rb_right, nullptr);
  ASSERT_EQ(result->key, 200);
  for(int i = 199; i >= 0; i --) {
    cur = rb_prev(cur);
    if (i == 0) {
      ASSERT_TRUE(cur == nullptr);
      break;
    }
    ASSERT_TRUE(cur != nullptr);
    kv_node_rb *result = _get_entry(cur, kv_node_rb, node);
    ASSERT_EQ(result->key, i);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}