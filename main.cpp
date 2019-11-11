#include <cstdio>
#include <cstdlib>
#include <cassert>

struct node_t {
    node_t *left;
    node_t *right;
    node_t *parent;
    void *value;
};

struct tree_t {
    node_t *head;
    size_t size;
};



int main() {
    return 0;
}

/**
 * Tree "constructor" i. e. function that creates tree
 * @param headValue Value for tree head
 * @return Pointer to tree_t
 */

tree_t *makeTree(void *headValue) {
    auto *tree = (tree_t *) calloc (1, sizeof(tree_t));
    auto *head = (node_t *) calloc (1, sizeof(node_t));
    head->value = headValue;
    tree->size = 1;
    tree->head = head;
    return tree;
}