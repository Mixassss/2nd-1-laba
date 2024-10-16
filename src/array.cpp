#include "../include/arr.h"

Array::Array() : size(0), razmer(0) {
    arr = new string[razmer];
}

Array::~Array() {
    delete[] arr; //Освобождение места
}

void Array::ShowArray() const {
    for (size_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void Array::addToEnd(string value) {
    string *newArr = new string[size + 1]; //Добавление нового массива, который увеличен на 1
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }
    newArr[size] = value;
    delete[] arr;
    arr = newArr;
    size++;//Увеличение длины массива   
}

void Array::addAtIndex(size_t index, string value) {
    if (index > size) {
        throw out_of_range("Index out of range");
    }
    if (size == razmer) {
        resize(); // если заполнен - увеличить
    }
    for (size_t i = size; i > index; --i) {
        arr[i] = arr[i - 1]; // Сдвигаем элементы вправо
    }
    arr[index] = value;
    ++size;
}

string Array::getIndex(size_t index) {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}
    
void Array::removeAtIndex(size_t index) {
    if (index >= size) return;
    string *newArr = new string[size - 1];
    for(size_t i = 0; i < index; ++i) {
            newArr[i] = arr[i];
    }
    for(size_t i = index + 1; i < size; ++i) {
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void Array::replaceAtIndex(size_t index, string value) {
    if(index >= size) return;
    arr[index] = value; //Замена элемента
}

size_t Array::getSize() const {
    return size; // Возвращаем текущее количество элементов
}

void Array::resize() {
    razmer *= 2; // Увеличиваем вместимость в 2 раза
    string* newArr = new string[razmer];
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}
