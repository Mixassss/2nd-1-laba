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

    void print();
    string toString();
    void insert(int value); //Функция добавления элемента
    NodeT* _insert(NodeT* nodeb, int value);
    bool search(NodeT* nodet, int value); //функция поиска
    bool isComplete(NodeT* nodet, int index, int totalNodes); // проверка на complete
    bool isComplete();
    int countNodes(NodeT* nodet);
    string _toString(NodeT* nodet);
    void printTree(NodeT* node, int depth);
    void clear(NodeT* nodet); // освобождение памяти
};

#include "../src/complete_binary_tree.cpp"

#endif // TREE_H
