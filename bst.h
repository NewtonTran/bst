#include <stdbool.h>

// IMPORTANT: YOU MAY NOT MAKE ANY CHANGES TO THIS FILE

extern const int PRE_ORDER;
extern const int IN_ORDER;
extern const int POST_ORDER;


struct bstnode {
    int item;
    struct bstnode *left;
    struct bstnode *right;
    int size;
};

struct bst {
    struct bstnode *root;
};


// bst_create(void) returns a pointer to a dynamically allocated new (empty) 
//   bst
// effects : allocates memory (caller must call destroy)
// time : O(1)
struct bst *bst_create(void);


// bst_destroy(t) deallocates all dynamically allocated memory 
//   within the entire bst
// requires : t is not NULL and t must be from a previous bst_create
// effects : the memory at t is invalid (freed)
// time : O(n)
void bst_destroy(struct bst *t);


// bst_size(t) returns the number of nodes in the bst
// requires : t is not NULL
// time : O(1)
int bst_size(struct bst *t);


// bst_insert(i,t) inserts the item i into the bst t
// requires : t is not NULL
// effects : mutates t to contain i, or does nothing 
//   if i is already contained in t
// time : O(h) where h is the height of the tree
void bst_insert(int i, struct bst *t);


// bst_find(i,t) returns true if i is in t, returns false otherwise
// requires : t is not NULL
// time : O(h) where h is the height of the tree
bool bst_find(int i, struct bst *t);


// bst_select(k,t) returns the k'th element from t in sorted order
// requires : t is not NULL and t has at least k + 1 items
// time : O(h) where h is the height of the tree
int bst_select(int k, struct bst *t);


// bst_remove(i,t) removes item i from bst t
// requires : t is not NULL and i is in t
// effects : mutates t to no longer contain i
// time : O(h) where h is the height of the tree
// note : use the strategy for removing a node 
//   from a bst described in the course notes
void bst_remove (int i, struct bst *t);


// bst_range(start,end,t) returns the number of items in t that are 
//   between the values of start and end (inclusive)
// requires : t is not NULL and start <= end
// time : O(n)
int bst_range (int start, int end, struct bst *t);


// bst_print(o,t) prints the bst to the screen in order o
// example : given a bst with the following structure
//             4
//           /   \
//          2     5
//         / \
//        1   3
//   pre-order print : [4,2,1,3,5]\n
//   in-order print : [1,2,3,4,5]\n
//   post-order print : [1,3,2,5,4]\n
// requires : t is not NULL and o is a valid order
// effects : prints output
// time : O(n)
void bst_print (int o, struct bst *t);


// bst_to_sorted_array(t) returns a pointer to a dynamically allocated array
//   which contains all of the items from t in sorted order
// requires : t is not NULL
// effects : allocates memory (caller must free)
// time : O(n)
int *bst_to_sorted_array(struct bst *t);


// sorted_array_to_bst(arr,len) returns a pointer to a dynamically allocated
//   bst which contains all of the items from arr such that the returned bst
//   is balanced. 
// note : the definition of a balanced binary tree is that, for every node 
//   in the tree, the heights of the left and right sub trees differ by 
//   at most 1
// requires : arr is sorted
// time : O(nlogn)
// bonus : O(n) time
struct bst *sorted_array_to_bst(int *arr, int len);


// bst_rebalance(t) changes t so that it contains all of the same items,
//   but the tree is balanced
// effects : mutates t so that it is a balanced tree
// time : O(nlogn)
void bst_rebalance(struct bst *t);
