#ifndef tree_h
#define tree_h

#include "utility.h"

struct NodeT {
    int data;
    NodeT* left;
    NodeT* right;

    NodeT(int value);
};

struct CompleteBinaryTree {
    NodeT* root; //Главная часть в бинарном дереве
    size_t size;

    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void insert(int value); //Функция добавления элемента
    bool isEmpty() const;
    void _insert(int value, NodeT* nodeb);
    bool search(NodeT* nodet, int value); //функция поиска
    bool isComplete(NodeT* nodet, int index, int totalNodes); // проверка на complete
    bool isComplete();
    string toString(NodeT* node) const;
    void printTree(NodeT* node);
    void clear(NodeT* nodet); // освобождение памяти
};

#include "../src/complete_binary_tree.cpp"

#endif // TREE_H
