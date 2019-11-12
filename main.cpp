#include <cstdio>
#include <cstdlib>
#include <cassert>

enum DIRECTION {
    HEAD,
    LEFT,
    RIGHT
};

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

node_t *getLeftNode(node_t *node);

node_t *getRightNode(node_t *node);

tree_t *makeTree(void *headValue);

void deleteNode(node_t *node);

void deleteTree(tree_t *tree);

void addLeftNode(tree_t *tree, node_t *node, void *value);

void addLeftNode(node_t *node, node_t *existingNode);

void addRightNode(tree_t *tree, node_t *node, void *value);

void addRightNode(node_t *node, node_t *existingNode);

void treeDump(tree_t *tree, char *filename, char *(*valueDump)(void *) = nullptr);

void nodeDump(node_t *node, FILE *dumpFile, DIRECTION dir);

void nodePrint(node_t *node, FILE *dumpFile, DIRECTION dir);

void treeSerialize(tree_t *tree, char *filename, char *(serializeValue)(void *));

void nodeSerialize(node_t *node, FILE* serialized, char *(serializeValue)(void *));

char *serializeValue(void *val) {
    return "STUB";
}

int main() {
    tree_t *tree = makeTree(nullptr);
    addLeftNode(tree, tree->head, nullptr);
    addRightNode(tree, tree->head, nullptr);

    addLeftNode(tree, getRightNode(tree->head), nullptr);
    addRightNode(tree, getRightNode(tree->head), nullptr);

    addLeftNode(tree, getLeftNode(tree->head), nullptr);
    addRightNode(tree, getLeftNode(tree->head), nullptr);

    addRightNode(tree, getLeftNode(getRightNode(tree->head)), nullptr);

    treeDump(tree, "testDump.dot");
    treeSerialize(tree, "serialized.txt", serializeValue);
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

    if (node->left)
        deleteNode(node->left);

    if (node->right)
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

/**
 * Function that gets right node
 * @param node Pointer to node
 * @return Pointer to right node
 */

node_t *getRightNode(node_t *node) {
    assert(node);

    return node->right;
}

/**
 * Function that gets parent node
 * @param node Pointer to node
 * @return Pointer to parent node
 */

node_t *getParent(node_t *node) {
    assert(node);

    return node->parent;
}

/**
 * Function that prints out node declaration in DOT format
 * @param node Pointer to node_t
 * @param dumpFile Pointer to FILE
 * @param dir Node direction (left, right or head)
 */

void nodePrint(node_t *node, FILE *dumpFile, DIRECTION dir) {
    fprintf(dumpFile,
            "node%p[shape=record, label=\"{%p | {PARENT|%p} | {{LEFT |<left> %p} | {RIGHT |<right> %p}}}\", style=filled, ",
            node, node, node->parent, node->left, node->right);
    if (dir == RIGHT)
        fprintf(dumpFile, "fillcolor=springgreen];\n");
    else if (dir == LEFT)
        fprintf(dumpFile, "fillcolor=indianred];\n");
    else if (dir == HEAD)
        fprintf(dumpFile, "fillcolor=mediumturquoise];\n");
}

/**
 * Function that recursively dumps nodes in DOT format
 * @param node Pointer to node_t
 * @param dumpFile Pointer to FILE
 * @param dir Node direction (left, right or head)
 */

void nodeDump(node_t *node, FILE *dumpFile, DIRECTION dir) {
    assert(node);
    assert(dumpFile);
    if (node->parent)
        if (dir == LEFT)
            fprintf(dumpFile, "node%p -> node%p:left;\nnode%p:left -> node%p;\n", node, node->parent, node->parent,
                    node);
        else if (dir == RIGHT)
            fprintf(dumpFile, "node%p -> node%p:right;\nnode%p:right -> node%p;\n", node, node->parent, node->parent,
                    node);

    if (node->left) {
        nodePrint(node->left, dumpFile, LEFT);
        nodeDump(node->left, dumpFile, LEFT);
    }

    if (node->right) {
        nodePrint(node->right, dumpFile, RIGHT);
        nodeDump(node->right, dumpFile, RIGHT);
    }
}

/**
 * Tree dumper
 * @param tree Pointer to tree_t
 * @param filename Dump file name
 * @param valueDump Optional function that renders tree value. Takes void pointer as an argument
 */

void treeDump(tree_t *tree, char *filename, char *(*valueDump)(void *)) {
    assert(tree);
    assert(filename);

    FILE *dumpFile = fopen(filename, "w");
    fprintf(dumpFile, "digraph {\nconcentrate=true\n");

    nodePrint(tree->head, dumpFile, HEAD);
    nodeDump(tree->head, dumpFile, HEAD);

    fprintf(dumpFile, "}\n");
    fclose(dumpFile);
}

void nodeSerialize(node_t *node, FILE* serialized, char *(serializeValue)(void *)) {
    assert(serialized);
    assert(node);
    assert(serializeValue);

    fprintf(serialized, "{ ");
    fprintf(serialized, "\"%s\" " ,serializeValue(node->value));

    if (node->left)
        nodeSerialize(node->left, serialized, serializeValue);
    else
        fprintf(serialized, "nil ");

    if (node->right)
        nodeSerialize(node->right, serialized, serializeValue);
    else
        fprintf(serialized, "nil ");

    fprintf(serialized, "} ");
}

void treeSerialize(tree_t *tree, char *filename, char *(serializeValue)(void *)) {
    assert(tree);
    assert(filename);
    FILE *serialized = fopen(filename, "w");

    nodeSerialize(tree->head, serialized, serializeValue);

    fclose(serialized);
}

