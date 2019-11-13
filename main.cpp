#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include "Tree.h"

void *deserializeValue(char *str) {
    int *val = (int *) calloc(1, sizeof(int));
    sscanf(str, "%d", val);
    return val;
}

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
//    int vals[8] = {1, 2, 3, 4, 5, 6, 7, 8};
//    tree_t *tree = makeTree(&vals[0]);
//    addLeftNode(tree, tree->head, &vals[1]);
//    addRightNode(tree, tree->head, &vals[2]);
//
//    addLeftNode(tree, getRightNode(tree->head), &vals[3]);
//    addRightNode(tree, getRightNode(tree->head), &vals[4]);
//
//    addLeftNode(tree, getLeftNode(tree->head), &vals[5]);
//    addRightNode(tree, getLeftNode(tree->head), &vals[6]);
//
//    addRightNode(tree, getLeftNode(getRightNode(tree->head)), &vals[7]);
//
//    treeDump(tree, "testDump.dot", valueDump);
//    treeSerialize(tree, "serialized.txt", serializeValue);
//    return 0;
    FILE *ser = fopen("serialized.txt", "r");
    fseek(ser, 0, SEEK_END);
    int len = ftell(ser);
    rewind(ser);
    char *buf = (char *) calloc(len + 1, sizeof(char));
    fread(buf, sizeof(char), len, ser);
    tree_t *newTree = treeDeserialize(buf, deserializeValue);
    fclose(ser);
    treeDump(newTree, "restored.dot", valueDump);
    return 0;
}

