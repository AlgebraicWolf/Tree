#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

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
    char *str = (char *) calloc(11, sizeof(char));
    sprintf(str, "%d", *(int *) val);
    return str;
}

char *valueDump(void *val) {
    char *str = (char *) calloc(33, sizeof(char));
    sprintf(str, "{VALUE | %d}", *(int *) val);
    return str;
}

int main() {
    int vals[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    tree_t *tree = makeTree(&vals[0]);
    addLeftNode(tree, tree->head, &vals[1]);
    addRightNode(tree, tree->head, &vals[2]);

    addLeftNode(tree, getRightNode(tree->head), &vals[3]);
    addRightNode(tree, getRightNode(tree->head), &vals[4]);

    addLeftNode(tree, getLeftNode(tree->head), &vals[5]);
    addRightNode(tree, getLeftNode(tree->head), &vals[6]);

    addRightNode(tree, getLeftNode(getRightNode(tree->head)), &vals[7]);

    treeDump(tree, "testDump.dot", valueDump);
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

void nodePrint(node_t *node, FILE *dumpFile, DIRECTION dir, char *(*valueDump)(void *)) {
    fprintf(dumpFile,
            "node%p[shape=record, label=\"{%p | {PARENT|%p}", node, node, node->parent);

    if(valueDump) {
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

void nodeSerialize(node_t *node, FILE* serialized, char *(serializeValue)(void *)) {
    assert(serialized);
    assert(node);
    assert(serializeValue);


    fprintf(serialized, "\"%s\" " ,serializeValue(node->value));

    if (node->left) {
        fprintf(serialized, "{ ");
        nodeSerialize(node->left, serialized, serializeValue);
        fprintf(serialized, "} ");
    }
    else if(node->right)
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

tree_t *treeDeserialize(char *serialized, char *(*deserializeValue)(char *)) {
    assert(serialized);
    assert(deserializeValue);
    tree_t *restored = makeTree(nullptr);
}

void nodeDeserialize(node_t *node, char *serialized, void *(*deserializeValue)(char *)) {
    assert(node);
    assert(serialized);

    serialized = strchr(serialized, '{');
    char *end = strrchr(serialized, '}');

    *end = '\0';

    char *valStart = strchr(serialized, '"') + 1;
    char *valEnd = strchr(valStart, '"');

    *valEnd = '\0';
    node->value = deserializeValue(valStart);

    serialized = valEnd + 1;

    char *closestNil = strchr(serialized, '$');
    char *closestArg = strchr(serialized, '"');
    if (!closestArg && !closestNil)
        return;
    else if (closestArg == nullptr);
}