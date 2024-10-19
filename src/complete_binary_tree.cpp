#include "../include/tree.h"

NodeT::NodeT(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
}

CompleteBinaryTree::CompleteBinaryTree() {
    root = nullptr;
    size = 0;
}

bool CompleteBinaryTree::isEmpty() const {
    return size == 0;
}

void CompleteBinaryTree::insert(int value) {
    NodeT* newNode = new NodeT(value);
    if(root == nullptr) { //Если главная часть равна нулю
        root = newNode; //то присваиваем новую ноду
    } else {
        _insert(value, root);
    }
    size++;
}

void CompleteBinaryTree::_insert(int value, NodeT* nodeb) {
    if(value < nodeb->data) { //Сравниваем значения
        if(nodeb->left == nullptr) {
            nodeb->left = new NodeT(value);
        } else {
            _insert(value, nodeb->left); //Рекурсивно вставляем новое значение
        }

    } else {
        if(nodeb->right == nullptr) {
            nodeb->right = new NodeT(value);
        } else {
            _insert(value, nodeb->right);
        }
    }
}

bool CompleteBinaryTree::search(NodeT* nodet, int value) {
    if (nodet == nullptr) return false; // Если нет значений
    if (nodet->data == value) return true;
    return search(nodet->left, value) || search(nodet->right, value);
}

bool CompleteBinaryTree::isComplete() {
    return isComplete(root, 0, size);
}

bool CompleteBinaryTree::isComplete(NodeT* nodet, int index, int totalNodes) {
    if (nodet == nullptr) return true; // Если узел пустой, это считается полным
    if (index >= totalNodes) return false; // Если индекс больше или равен количеству узлов, не полное

    // Проверяем рекурсивно для левого и правого поддеревьев
    return isComplete(nodet->left, 2 * index + 1, totalNodes) &&
           isComplete(nodet->right, 2 * (index + 1), totalNodes);
}

string CompleteBinaryTree::toString(NodeT* node) const {
    if (node == nullptr) return "";
    return toString(node->left) + to_string(node->data) + " " + toString(node->right);
}

void CompleteBinaryTree::printTree(NodeT* node) {
    if (node == nullptr) return;
    printTree(node->right);
    cout << setw(4) << " " << node->data << endl;
    printTree(node->left);
}

void CompleteBinaryTree::clear(NodeT* nodet) {
    if (nodet == nullptr) return;
    clear(nodet->left);
    clear(nodet->right);
    delete nodet;
}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}
