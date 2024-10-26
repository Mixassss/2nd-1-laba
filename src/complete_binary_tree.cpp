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

void CompleteBinaryTree::print() {
    printTree(root, 0);
    cout << endl;
}

string CompleteBinaryTree::toString() {
    return _toString(root);
}

void CompleteBinaryTree::insert(int value) {
    root = _insert(root, value);
    size++;
}

NodeT* CompleteBinaryTree::_insert(NodeT* nodeb, int value) {
    if (nodeb == nullptr) { // Если текущий узел равен нулю
        return new NodeT(value); // Создаем новый узел и возвращаем его
    }

    if (value < nodeb->data) { // Сравниваем значения
        nodeb->left = _insert(nodeb->left, value); // Рекурсивно вставляем в левое поддерево
    } else {
        nodeb->right = _insert(nodeb->right, value); // Рекурсивно вставляем в правое поддерево
    }

    return nodeb; // Возвращаем текущий узел
}

bool CompleteBinaryTree::search(NodeT* nodet, int value) {
    if (nodet == nullptr) return false; // Если нет значений
    if (nodet->data == value) return true;
    return search(nodet->left, value) || search(nodet->right, value);
}

bool CompleteBinaryTree::isComplete() {
    int nodetCount = countNodes(root);
    return isComplete(root, 0, size);
}

bool CompleteBinaryTree::isComplete(NodeT* nodet, int index, int totalNodes) {
    if (nodet == nullptr) return true; // Если узел пустой, это считается полным
    if (index >= totalNodes) return false; // Если индекс больше или равен количеству узлов, не полное

    return isComplete(nodet->left, 2 * index + 1, totalNodes) && // Проверяем рекурсивно для левого и правого поддеревьев
           isComplete(nodet->right, 2 * index + 2, totalNodes);
}

int CompleteBinaryTree::countNodes(NodeT* nodet) {
    if (nodet == nullptr) return 0;
    return 1 + countNodes(nodet->left) + countNodes(nodet->right);
}

string CompleteBinaryTree::_toString(NodeT* nodet) {
    if (nodet == nullptr) return "";

    ostringstream oss;
    oss << nodet->data << " "; // Добавляем текущий узел

    oss << _toString(nodet->left); // Рекурсивно добавляем элементы из левого поддерева
    oss << _toString(nodet->right); // Рекурсивно добавляем элементы из правого поддерева

    return oss.str();
}

void CompleteBinaryTree::printTree(NodeT* node, int depth) {
    if (node == nullptr) return;
    printTree(node->right, depth + 1);
    cout << setw(4 * depth) << " " << node->data << endl;
    printTree(node->left, depth + 1);
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
