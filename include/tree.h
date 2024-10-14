#ifndef tree_h
#define tree_h

#include "utility.h"

struct NodeT {
    string data;
    NodeT* left;
    NodeT* right;

    NodeT(string value);
};

struct CompleteBinaryTree {
    NodeT* root; //Главная часть в бинарном дереве
    size_t size;

    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void insert(string value); //Функция добавления элемента
    void _insert(string value, NodeT* nodeb);
    bool search(NodeT* nodet, string value); //функция поиска
    bool isComplete(NodeT* nodet, int index, int totalNodes); // проверка на complete
    bool isComplete();
    void clear(NodeT* nodet); // освобождение памяти
};
#endif // TREE_H
