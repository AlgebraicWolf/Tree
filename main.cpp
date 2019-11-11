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

node_t *makeNode(node_t *parent, node_t *left, node_t *right, void *value);

tree_t *makeTree(void *headValue);

void deleteNode(node_t *node);

void deleteTree(tree_t *tree);

void addLeftNode(tree_t *tree, node_t *node, void *value);

void addLeftNode(node_t *node, node_t *existingNode);

int main() {
    return 0;
}

/**
 * Tree "constructor" i. e. function that creates tree
 * @param headValue Value for tree head
 * @return Pointer to tree_t
 */

tree_t *makeTree(void *headValue) {
    auto *tree = (tree_t *) calloc(1, sizeof(tree_t));
    node_t *head = makeNode(nullptr, nullptr, nullptr, headValue);
    tree->head = head;
    return tree;
}

/**
 * Node "constructor" i. e. function that creates tree
 * @param parent Pointer to parent node
 * @param left Pointer to left node
 * @param right Pointer to right node
 * @param value Pointer to value
 * @return Pointer to node_t
 */

node_t *makeNode(node_t *parent, node_t *left, node_t *right, void *value) {
    auto node = (node_t *) calloc(1, sizeof(node_t));

    node->parent = parent;
    node->left = left;
    node->right = right;
    node->value = value;

    return node;
}

/**
 * Node "destructor" i. e. function that deletes node AND ALL THE SUBNODES
 * @param node Pointer to node for deleting
 */

void deleteNode(node_t *node) {
    assert(node);

    if(node->left)
        deleteNode(node->left);

    if(node->right)
        deleteNode(node->right);

    free(node);
}

/**
 * Tree "destructor" i. e. function that deletes the whole tree
 * @param tree Pointer to the tree for deleting
 */

void deleteTree(tree_t *tree) {
    assert(tree);

    deleteNode(tree->head);
    tree->size = 0;

    free(tree);
}

/**
 * Function that adds left node
 * @param tree Pointer to tree for adding node
 * @param node Pointer to target node
 * @param value Pointer to value for new node
 */

void addLeftNode(tree_t *tree, node_t *node, void *value) {
    assert(node);
    assert(tree);

    node_t *newNode = makeNode(node, nullptr, nullptr, value);
    node->left = newNode;
    tree->size++;
}

/**
 * Function that adds node to the left. Due to tree size uncertaincy, function does not handle it
 * @param tree Pointer to tree for adding node
 * @param node Pointer to target node
 * @param existingNode Node for attaching
 */

void addLeftNode(node_t *node, node_t *existingNode) {
    assert(node);
    assert(existingNode);

    node->left = existingNode;
    existingNode->parent = node;
}

/**
 * Function that adds subtree to the left
 * @param tree Pointer to tree for subtree
 * @param node Pointer to target node
 * @param subtree Pointer to subtree
 */

void addLeftSubtree(tree_t *tree, node_t *node, tree_t *subtree) {
    assert(tree);
    assert(subtree);

    addLeftNode(node, subtree->head);

    tree->size += subtree->size;
    free(subtree);
}

/**
 * Function that adds right node
 * @param tree Pointer to tree for adding node
 * @param node Pointer to target node
 * @param value Pointer to value for new node
 */

void addRightNode(tree_t *tree, node_t *node, void *value) {
    assert(node);
    assert(tree);

    node_t *newNode = makeNode(node, nullptr, nullptr, value);
    node->right = newNode;
    tree->size++;
}

/**
 * Function that adds node to the right. Due to tree size uncertaincy, function does not handle it
 * @param tree Pointer to tree for adding node
 * @param node Pointer to target node
 * @param existingNode Node for attaching
 */

void addRightNode(node_t *node, node_t *existingNode) {
    assert(node);
    assert(existingNode);

    node->right = existingNode;
    existingNode->parent = node;
}

/**
 * Function that adds subtree to the right
 * @param tree Pointer to tree for subtree
 * @param node Pointer to target node
 * @param subtree Pointer to subtree
 */

void addRightSubtree(tree_t *tree, node_t *node, tree_t *subtree) {
    assert(tree);
    assert(subtree);

    addRightNode(node, subtree->head);

    tree->size += subtree->size;
    free(subtree);
}

/**
 * Function that gets left node
 * @param node Pointer to node
 * @return Pointer to left node
 */

node_t *getLeftNode(node_t *node) {
    assert(node);

    return node->left;
}