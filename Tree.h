//
// Created by alexey on 14.11.2019.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H
#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<cstring>

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

void nodeSerialize(node_t *node, FILE *serialized, char *(serializeValue)(void *));

tree_t *treeDeserialize(char *serialized, void *(*deserializeValue)(char *));
#endif //TREE_TREE_H
