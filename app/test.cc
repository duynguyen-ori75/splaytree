#include <gtest/gtest.h>

extern "C" {
#include "splaytree.h"
}

struct data_node {
  int key;

  splay_node node;
};

int cmp_func(splay_node *lhs, splay_node *rhs) {
  int leftKey   = _get_entry(lhs, data_node, node)->key;
  int rightKey  = _get_entry(rhs, data_node, node)->key;
  return leftKey - rightKey;
}

TEST(SplayTree, SplayInsertAndSearch) {
  data_node data[100];
  splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 0; i < 100; i ++) {
    data[i].key = i * 2 + 1;
    splay_insert(&tree, &data[i].node, cmp_func);
  }

  data_node query, *result;
  splay_node *cur;
  int expectedKey;
  for(int i = 0; i < 200; i ++) {
    query.key = i;
    cur = splay_search(&tree, &query.node, cmp_func);
    if (i % 2) {
      ASSERT_EQ(cur, tree.root);
      result = _get_entry(cur, data_node, node);
      ASSERT_EQ(result->key, i);
    } else {
      ASSERT_EQ(cur, nullptr);
    }

    cur = splay_search_lower(&tree, &query.node, cmp_func);
    if (cur <= 0) {
      ASSERT_EQ(cur, nullptr);
    } else {
      result = _get_entry(cur, data_node, node);
      expectedKey = (i % 2) ? i : i - 1;
      ASSERT_EQ(result->key, expectedKey);
    }

    cur = splay_search_greater(&tree, &query.node, cmp_func);
    result = _get_entry(cur, data_node, node);
    expectedKey = (i % 2) ? i : i + 1;
    ASSERT_EQ(result->key, expectedKey);
  }
}

TEST(SplayTree, SplayRemove) {
  data_node data[200];
  splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 0; i < 200; i ++) {
    data[i].key = i;
    splay_insert(&tree, &data[i].node, cmp_func);
  }

  data_node query, *result;
  splay_node *cur;
  for(int i = 0; i < 100; i ++) {
    query.key = rand() % 200;

    splay_delete(&tree, &query.node, cmp_func);
    cur = splay_search(&tree, &query.node, cmp_func);
    ASSERT_EQ(cur, nullptr);

    cur = splay_search_greater(&tree, &query.node, cmp_func);
    if (cur) {
      result = _get_entry(cur, data_node, node);
      ASSERT_GT(result->key, query.key);
    }
  }
}

TEST(SplayTree, SplayFirstAndLast) {
  data_node data[200];
  splay_tree tree;
  splay_tree_init(&tree);

  for(int i = 0; i < 200; i ++) {
    data[i].key = i;
    splay_insert(&tree, &data[i].node, cmp_func);
  }

  splay_node *cur = splay_first(&tree, true);
  data_node *result = _get_entry(cur, data_node, node);
  ASSERT_EQ(cur, tree.root);
  ASSERT_EQ(cur->left, nullptr);
  ASSERT_EQ(result->key, 0);

  cur = splay_last(&tree, true);
  result = _get_entry(cur, data_node, node);
  ASSERT_EQ(cur, tree.root);
  ASSERT_EQ(cur->right, nullptr);
  ASSERT_EQ(result->key, 199);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}