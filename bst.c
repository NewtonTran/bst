#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

// IMPORTANT: DO NOT CHANGE THESE VALUES
const int PRE_ORDER = 0;
const int IN_ORDER = 1;
const int POST_ORDER = 2;

// INTEGRITY STATEMENT (modify if necessary)
// I received help from the following sources:
// None. I am the sole author of this work 

// sign this statement by removing the line below and entering your name
// Name: Newton Tran
// login ID: n23tran

// implementation:

// see bst.h for details.

struct bst *bst_create(void) {
  struct bst *new_bst = malloc(1 * sizeof(struct bst));
  new_bst->root = NULL;
  return new_bst;
}


// bstnode_destroy(node) frees all dynamically allocated memory within the
//   entire bst rooted at node.
// requires: node != NULL
// effects: the memory in bst rooted at node is invalid.
// time: O(n) where n is the size of the tree.
static void bstnode_destroy(struct bstnode *node) {
  if (node->left != NULL) {
    bstnode_destroy(node->left);
  }
  if (node->right != NULL) {
    bstnode_destroy(node->right);
  }
  free(node);
}


void bst_destroy(struct bst *t) {
  assert(t != NULL);
  if (t->root != NULL) { 
    bstnode_destroy(t->root);
  }
  free(t);
}


int bst_size(struct bst *t) {
  assert(t != NULL);
  if (t->root == NULL) {
    return 0;
  }
  else {
    return t->root->size;
  }
}


// bstnode_insert(i, node) inserts a new item into the tree rooted at node.
// requires: i is not already in the tree rooted at node, node != NULL.
// effects: mutates the tree.
// time: O(h) where h is the height of the tree.
static void bstnode_insert(int i, struct bstnode *node) {
  if (i < node->item) {
    if (node->left == NULL) {
      struct bstnode *new_node = malloc(1 * sizeof(struct bstnode));
      node->left = new_node;
      new_node->item = i;
      new_node->left = NULL;
      new_node->right = NULL;
      new_node->size = 1;
    }
    else {
      bstnode_insert(i, node->left);
    }
  }
  else {
    if (node->right == NULL) {
      struct bstnode *new_node = malloc(1 * sizeof(struct bstnode));
      node->right = new_node;
      new_node->item = i;
      new_node->left = NULL;
      new_node->right = NULL;
      new_node->size = 1;
    }
    else {
      bstnode_insert(i, node->right);
    }
  }
  ++(node->size);
}


void bst_insert(int i, struct bst *t) {
  assert(t != NULL);
  if (bst_find(i, t)) {
    return;
  }
  if (t->root == NULL) {
    struct bstnode *temp = malloc(1 * sizeof(struct bstnode));
    temp->item = i;
    temp->size = 1;
    temp->left = NULL;
    temp->right = NULL;
    t->root = temp;
  }
  else {
    bstnode_insert(i, t->root);
  }
}


// bstnode_find(i, node) returns true if i is within the bst rooted at node.
//   otherwise, false is returned.
// time: O(h) where h is the height of the tree.
static bool bstnode_find(int i, struct bstnode *node) {
  if (node == NULL) {
    return false;
  }
  else if (i == node->item) {
    return true;
  }
  else if (i < node->item) {
    return bstnode_find(i, node->left);
  }
  else {
    return bstnode_find(i, node->right);
  }
}


bool bst_find(int i, struct bst *t) {
  assert(t != NULL);
  return bstnode_find(i, t->root);
}


// bstnode_select(k, node) returns the kth element of the bst rooted at node.
// requires: node != NULL and there are atleast k + 1 elements in the tree.
// time: O(h) where h is the height of the tree.
static int bstnode_select(int k, struct bstnode *node) {
  int left_size = 0;
  if (node->left != NULL) {
    left_size = node->left->size;
  }
  if (k < left_size) {
    return bstnode_select(k, node->left);
  }
  else if (k == left_size) {
    return node->item;
  }
  else {
    return bstnode_select(k - left_size - 1, node->right);
  }
}


int bst_select(int k, struct bst *t) {
  assert(t != NULL);
  assert(k >= 0);
  assert(k <= t->root->size);
  return bstnode_select(k, t->root);
}


// bstnode_remove(i, node) removes i from the bst rooted at node, then returns
//   a pointer to the updated root of the tree.
// effects: mutates the bst rooted at node.
// time: O(h) where h is the height of the tree.
static struct bstnode *bstnode_remove(int i, struct bstnode *node) {
  if (node == NULL) return NULL;
  if (i < node->item) {
    --(node->size);
    node->left = bstnode_remove(i, node->left);
  } 
  else if (i > node->item) {
    --(node->size);
    node->right = bstnode_remove(i, node->right);
  } 
  else if (node->left == NULL) {
    struct bstnode *temp = node->right;
    free(node);
    return temp;
  } 
  else if (node->right == NULL) {
    struct bstnode *temp = node->left;
    free(node);
    return temp;
  } 
  else {
    --(node->size);
    struct bstnode *next = node->right;
    while (next->left) {
      next = next->left;
    }
    node->item = next->item;
    node->right = bstnode_remove(next->item, node->right);
  }
  return node;
}


void bst_remove(int i, struct bst *t) {
  assert(t != NULL);
  assert(bst_find(i, t));
  t->root = bstnode_remove(i, t->root);
}


int bst_range(int start, int end, struct bst *t) {
  assert(t != NULL);
  assert(start <= end);
  int *arr = bst_to_sorted_array(t);
  int i = 0;
  int count = 0;
  while (i < t->root->size) {
    if ((arr[i] >= start) && (arr[i] <= end)) {
      ++count;
    }
    ++i;
    if (arr[i] > end) {
      break;
    }
  }
  free(arr);
  return count;
}


// find_last_pre(node) returns the last node to be printed in pre-order from
//   the tree rooted at node.
// requires: node != NULL
// time: O(h) where h is the height of the tree.
static int find_last_pre(struct bstnode *node) {
  assert(node != NULL);
  struct bstnode *last_node = node;
  while (last_node->right) {
    last_node = last_node->right;
  }
  if (last_node->left == NULL) {
    return last_node->item;
  }
  else {
    while (last_node->left) {
      last_node = last_node->left;
    }
    return find_last_pre(last_node);
  }
}


// bstnode_print_pre(node, last) prints the elements of the bst rooted at node 
// in pre-order to the screen.
// effects: prints a bst to the screen.
// time: O(n)
static void bstnode_print_pre(struct bstnode *node, int last) {
  if (node == NULL) {
    return;
  }
  else if (node->item == last) {
    printf("%d", node->item);
  }
  else {
    printf("%d,", node->item);
  }
  bstnode_print_pre(node->left, last);
  bstnode_print_pre(node->right, last);
}


// bstnode_print_in(node, last) prints the elements of the bst rooted at node 
//   in order to the screen.
// effects: prints a bst to the screen.
// time: O(n)
static void bstnode_print_in(struct bstnode *node, int last) {
  if (node == NULL) {
    return;
  }
  bstnode_print_in(node->left, last);
  if (node->item == last) {
    printf("%d", node->item);
  }
  else {
    printf("%d,", node->item);
  }
  bstnode_print_in(node->right, last);
}


// bstnode_print_post(node, last) prints the elements of the bst rooted at node 
//   in post-order to the screen.
// effects: prints a bst to the screen.
// time: O(n)
static void bstnode_print_post(struct bstnode *node, int last) {
  if (node == NULL) {
    return;
  }
  bstnode_print_post(node->left, last);
  bstnode_print_post(node->right, last);
  if (node->item == last) {
    printf("%d", node->item);
  }
  else {
    printf("%d,", node->item);
  }
}


// bstnode_print_in(node, last) prints the elements of the bst rooted at node 
//   in o order.
// effects: prints a bst to the screen.
// time: O(n)
static void bstnode_print_wrap(int o, struct bstnode *node) {
  int last;
  if (o == 0) {
    last = find_last_pre(node);
  }
  else if (o == 1) {
    last = bstnode_select(node->size - 1, node);
  }
  else {
    last = node->item;
  }
  printf("[");
  if (o == 0) {
    bstnode_print_pre(node, last);
  }
  else if (o == 1) {
    bstnode_print_in(node, last);
  }
  else {
    bstnode_print_post(node, last);
  }
  printf("]\n");
}


void bst_print (int o, struct bst *t) {
  assert(t != NULL);
  assert(o >= 0);
  assert(o <= 2);
  if (t->root == NULL) {
    printf("[]\n");
  }
  else {
    bstnode_print_wrap(o, t->root);
  }
}


// insert_nodes(arr, start, size, node) inserts the elements of the bst rooted
//   at node into arr.
// effects: mutates arr.
// time: O(n)
static void insert_nodes(int *arr, int start, int size, struct bstnode *node) {
  if (node == NULL){
    return;
  }
  else if (start >= size) {
    return;
  }
  else if (node->left != NULL) {
    arr[start + node->left->size] = node->item;
  }
  else {
    arr[start] = node->item;
  }
  int left_size = 0;
  if (node->left != NULL) {
    left_size = node->left->size;
  }
  insert_nodes(arr, start, size, node->left);
  insert_nodes(arr, start + left_size + 1, size, node->right);
}


int *bst_to_sorted_array(struct bst *t) {
  assert(t != NULL);
  if (t->root == NULL) {
    return NULL;
  }
  int *arr = malloc(t->root->size * sizeof(int));
  insert_nodes(arr, 0, t->root->size, t->root);
  return arr;
}


// sorted_array_to_bstnode(arr, start, end) puts the elements of arr into a
//   bst and the address to the bst is returned.
// effects: memory is allocated for the new bst.
// time: O(n)
static struct bstnode *sorted_array_to_bstnode(int *arr, int start, int end) {
  if (start > end) {
    return NULL;
  }
  struct bstnode *new_node = malloc(1 * sizeof(struct bstnode));
  int mid = (start + end) / 2;
  new_node->item = arr[mid];
  new_node->size = end - start + 1;
  new_node->left = sorted_array_to_bstnode(arr, start, mid - 1);
  new_node->right = sorted_array_to_bstnode(arr, mid + 1, end);
  return new_node;
}


// this function has time O(n) for bonus
struct bst *sorted_array_to_bst(int *arr, int len) {
  struct bst *new_bst = bst_create();
  if (len == 0) {
    return new_bst;
  }
  new_bst->root = sorted_array_to_bstnode(arr, 0, len - 1);
  return new_bst;
}


// this function has time O(n), not O(nlogn) as stated in bst.h
void bst_rebalance(struct bst *t) {
  assert(t != NULL);
  int *arr = bst_to_sorted_array(t);
  struct bst *balanced_bst = sorted_array_to_bst(arr, t->root->size);
  bstnode_destroy(t->root);
  t->root = balanced_bst->root;
  free(balanced_bst);
  free(arr);
}