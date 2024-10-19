#include "../include/queue.h"

Queue::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
    data = new string[capacity];
}

Queue::Queue() : capacity(30), front(0), rear(-1), size(0) {
    data = new string[capacity]; //Размер списка
}

Queue::~Queue() {
    delete[] data;
}

bool Queue::isempty() {
    return size == 0;
}

void Queue::push(string value) {
    if (size == capacity) {
        throw overflow_error("Очередь переполнена"); // Проверка на переполнение
    }
    rear = (rear + 1) % capacity; // Циклическое увеличение индекса
    data[rear] = value; // Добавление элемента
    size++; // Увеличение размера очереди
}

string Queue::pop() {
    if (size == 0) {
        throw underflow_error("Очередь пуста"); // Проверка на пустоту
    }
    string value = data[front]; // Сохранение значения для возврата
    front = (front + 1) % capacity; // Циклическое увеличение индекса
    size--; // Уменьшение размера очереди
    return value; // Возврат удаленного элемента
}

string Queue::peek() {
    if (isempty()) {
        throw underflow_error("Очередь пуста"); // Проверка на пустоту
    }
    return data[front];
}

int Queue::Size() {
    return size;
}
