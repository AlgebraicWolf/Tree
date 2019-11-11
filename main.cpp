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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}