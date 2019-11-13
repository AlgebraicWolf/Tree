//
// Created by alexey on 14.11.2019.
//

#include "Tree.h"

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

void nodePrint(node_t *node, FILE *dumpFile, DIRECTION dir, char *(*valueDump)(void *)) {
    fprintf(dumpFile,
            "node%p[shape=record, label=\"{%p | {PARENT|%p}", node, node, node->parent);

    if (valueDump) {
        fprintf(dumpFile, "| %s", valueDump(node->value));
    }

    fprintf(dumpFile, " | {{LEFT |<left> %p} | {RIGHT |<right> %p}}}\", style=filled, ", node->left, node->right);
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

void nodeDump(node_t *node, FILE *dumpFile, DIRECTION dir, char *(*valueDump)(void *)) {
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
        nodePrint(node->left, dumpFile, LEFT, valueDump);
        nodeDump(node->left, dumpFile, LEFT, valueDump);
    }

    if (node->right) {
        nodePrint(node->right, dumpFile, RIGHT, valueDump);
        nodeDump(node->right, dumpFile, RIGHT, valueDump);
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

    nodePrint(tree->head, dumpFile, HEAD, valueDump);
    nodeDump(tree->head, dumpFile, HEAD, valueDump);

    fprintf(dumpFile, "}\n");
    fclose(dumpFile);
}

/**
 * Function that recursively serializes nodes
 * @param node Pointer to node_t
 * @param serialized Pointer to FILE to write to
 * @param serializeValue Pointer to value serializer function
 */

void nodeSerialize(node_t *node, FILE *serialized, char *(serializeValue)(void *)) {
    assert(serialized);
    assert(node);
    assert(serializeValue);


    fprintf(serialized, "\"%s\" ", serializeValue(node->value));

    if (node->left) {
        fprintf(serialized, "{ ");
        nodeSerialize(node->left, serialized, serializeValue);
        fprintf(serialized, "} ");
    } else if (node->right)
        fprintf(serialized, "$ ");

    if (node->right) {
        fprintf(serialized, "{ ");
        nodeSerialize(node->right, serialized, serializeValue);
        fprintf(serialized, "} ");
    }
    //else
    //fprintf(serialized, "$ ");
}

/**
 * Function that serializes tree
 * @param tree Pointer to tree_t
 * @param filename Filename to write to
 * @param serializeValue Function that serializes value
 */

void treeSerialize(tree_t *tree, char *filename, char *(serializeValue)(void *)) {
    assert(tree);
    assert(filename);
    FILE *serialized = fopen(filename, "w");
    fprintf(serialized, "{ ");

    nodeSerialize(tree->head, serialized, serializeValue);

    fprintf(serialized, "}");

    fclose(serialized);
}

char *findClosed(char *str, char opened, char closed) {
    int depth = 0;
    while (*str && (*str != closed || depth > 1)) {
        if (*str == opened)
            depth++;
        else if (*str == closed)
            depth--;
        str++;
    }

    return str;
}

void nodeDeserialize(tree_t *tree, node_t *node, char *serialized, void *(*deserializeValue)(char *)) {
    assert(node);
    assert(serialized);

    serialized = strchr(serialized, '"') + 1;
    char *end = strchr(serialized, '"');
    *end = '\0';
    void *value = deserializeValue(serialized);
    node->value = value;
    serialized = end + 1;

    char *leftSkip = strchr(serialized, '$');

    serialized = strchr(serialized, '{');
    if (!serialized)
        return;

    end = findClosed(serialized, '{', '}');
    if (!end)
        return;

    serialized++;
    *end = '\0';


    if (leftSkip >= serialized || !leftSkip) {
        node->left = makeNode(node, nullptr, nullptr, nullptr);
        tree->size++;
        nodeDeserialize(tree, node->left, serialized, deserializeValue);


        serialized = end + 1;

        serialized = strchr(serialized, '{');
        if (!serialized)
            return;

        end = findClosed(serialized, '{', '}');
        if (!end)
            return;

        serialized++;
        *end = '\0';
    }
    node->right = makeNode(node, nullptr, nullptr, nullptr);
    tree->size++;
    nodeDeserialize(tree, node->right, serialized, deserializeValue);
}

tree_t *treeDeserialize(char *serialized, void *(*deserializeValue)(char *)) {
    assert(serialized);
    assert(deserializeValue);
    tree_t *restored = makeTree(nullptr);

    serialized = strchr(serialized, '{') + 1;
    char *end = strrchr(serialized, '}');
    *end = '\0';

    nodeDeserialize(restored, restored->head, serialized, deserializeValue);
    return restored;
}