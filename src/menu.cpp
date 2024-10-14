#include "../include/menu.h"

void aMenu(Node *tokens, Data &data) {
  string query = tokens->data;
  Array arr;

  if (data.str.empty()) return;
  istringstream stream(data.str);
  string word;
  while (stream >> word) {
    arr.addToEnd(word); // Добавляем слова из строки в массив
  }

  if (query == "MPUSH") {
    arr.addToEnd(tokens->next->next->data);
  } else if (query == "MINSERT") {
      size_t index = stoi(tokens->next->next->data);
      arr.addAtIndex(index, tokens->next->next->next->data);
  } else if (query == "MGET") {
      size_t index = stoi(tokens->next->next->data);
      cout << arr.getIndex(index) << endl;
  } else if (query == "MREPLACE") {
      size_t index = stoi(tokens->next->next->data);
      arr.replaceAtIndex(index, tokens->next->next->next->data);
  } else if (query == "MDEL") {
      size_t index = stoi(tokens->next->next->data);
      arr.removeAtIndex(index);
  } else if (query == "MLEN") {
      cout << arr.getSize() << endl;
  } else {
      cout << "Invalid request" << endl;
  }
  data.str.clear();
    
  // Формируем строку для вывода
  data.str += data.name + " ";
  for (size_t i = 0; i < arr.getSize(); i++) {
    data.str += arr.getIndex(i) + " ";
  }
}

void lsMenu(Node* tokens, Data &data) {
  string query = tokens->data;
  SinglyLinkedList SList;

  // Парсинг строки из data.str, если она не пустая
  if (!data.str.empty()) {
    parse(data.str);
  }

  if (query == "LPUSH") {
    SList.pushFront(tokens->next->next->data);
  } else if (query == "LADD") {
      SList.pushBack(tokens->next->next->data);
  } else if (query == "LREM") {
      SList.popBack();
  } else if (query == "LDEL") {
      SList.popFront();
  } else if (query == "LREMOVE") {
      string value = tokens->next->next->data;
      SList.removeAt(value);
  } else {
      cout << "Invalid request" << endl;
  }

  // Формируем строку из элементов списка
  Node* curNode = SList.head; // Инициализация указателя на голову списка
  data.str.clear(); // Очищаем строку перед формированием новой

  if (curNode) {
    data.str += data.name + " ";
    while (curNode) {
      data.str += curNode->data + " ";
      curNode = curNode->next;
    }
  }

  // Освобождаем память, занятую списком
  SList.clearSList();
}

Node* parse(const string &input) {
    Node* tokens = nullptr;
    SinglyLinkedList SList;
    istringstream iss(input);
    string token;

    while (iss >> token) {
        SList.pushBack(token);
    }

    return tokens;
}

void ldMenu(Node* tokens, Data &data) {
  string query = tokens->data;
  DoublyLinkedList DList;
  
  // Парсинг строки из data.str, если она не пустая
    if (!data.str.empty()) {
        parse(data.str);
    }

    if (query == "LPUSH") {
        DList.pushFront(tokens->next->next->data);
    } else if (query == "LADD") {
        DList.pushBack(tokens->next->next->data);
    } else if (query == "LREM") {
        DList.popBack();
    } else if (query == "LDEL") {
        DList.popFront();
    } else if (query == "LREMOVE") {
        string value = tokens->next->next->data;
        DList.removeAt(value);
    } else {
        cout << "Invalid request" << endl;
    }

    // Формируем строку из элементов списка
    DoubleNode* curNode = DList.head; // Инициализация указателя на голову списка
    data.str.clear(); // Очищаем строку перед формированием новой

    if (curNode) {
      data.str += data.name + " ";
      while (curNode) {
        data.str += curNode->data + " ";
        curNode = curNode->next;
    }
  }
}

void qMenu(Node* tokens, Data &data) {
  string query = tokens->data;
  Queue node(10); //Создаем очередь с изначальной вместимостью 10

  if(!data.str.empty()) {
    istringstream stream(data.str);
    string word;
    while (stream >> word) {
      node.push(word); // Добавляем слова из строки в очередь
    }
  }
  
  if (query == "QPUSH") {
    node.push(tokens->next->next->data);
    } else if (query == "QPOP") {
      if (!node.isempty()){
        node.pop();
        } else {
          cout << "The queue is empty" << endl;
          }
          } else {
            cout << "Invalid request" << endl;
  }
  
  data.str.clear();
    
    if (!node.isempty()) {
        data.str += data.name + " ";
        while (!node.isempty()) {
            data.str += node.peek() + " "; // Получаем элемент в начале очереди
            node.pop(); // Удаляем его из очереди
        }
    }
}

void sMenu(Node* tokens, Data& data) {
  string query = tokens->data;

  Stack stack(10); // Создаем стек с начальной вместимостью 10

    if (!data.str.empty()) {
        istringstream stream(data.str);
        string word;
        while (stream >> word) {
          stack.push(word); // Добавляем слова из строки в стек
        }
    }
    if(query == "SPUSH") {
      stack.push(tokens->next->next->data);
    } else if (query == "QPOP") {
    if (!stack.isEmpty()){
      stack.pop();
    }
  } else {
    cout << "Wrong query" << endl;
  }
  
  data.str.clear();
    
    if (!stack.isEmpty()) {
        data.str += data.name + " ";
        while (!stack.isEmpty()) {
            data.str += stack.peek() + " "; // Получаем элемент в начале стека
            stack.pop(); // Удаляем его из стека
        }
    }
}

void hMenu(Node *tokens, Data &data) {
  string query = tokens->data;
  Hash_table node; // Создаем экземпляр хэш-таблицы

  if (query == "HADD") { // Обработка различных запросов
    // Добавляем слова из data.str в хэш-таблицу
    if (!data.str.empty()) {
      istringstream stream(data.str);
      string key, value;
      while (stream >> key >> value) { // Предполагаем, что ключ и значение идут парами
        node.insert(key, value); // Вставляем пару ключ-значение в хэш-таблицу
      }
    }
  } else if (query == "HGET") {
      string result;
      if (node.get(tokens->next->data, result)) { // Получаем элемент из хэш-таблицы
        cout << result << endl; // Если элемент найден, выводим его значение
      } else {
        cout << false << endl; // Если элемент не найден
      }
    } else if (query == "HDEL") {
        if (node.remove(tokens->next->data)) { // Удаляем элемент из хэш-таблицы
          cout << "Deleted" << endl;
      } else {
          cout << "Key not found" << endl;
      }
    } else {
        cout << "Wrong query" << endl; // Обработка неправильного запроса
  }

  data.str.clear(); // Очищаем строку для следующего использования

  if (tokens->next) { // Проверяем, есть ли следующий элемент
    string key = tokens->next->data;
    string value;
    if (node.get(key, value)) { // Используем правильный ключ для получения
      data.str = key + " " + value; // Сохраняем результат в data.str
    } else {
        data.str = ""; // Если ничего не найдено, очищаем строку
    }
  }
}

void tMenu(Node *tokens, Data &data) {
  string query = tokens->data;
  CompleteBinaryTree tree; // Используем экземпляр дерева
    string name = tokens->next->data;

    if (!data.str.empty()) {
        istringstream stream(data.str);
        string word;
        while (stream >> word) {
            tree.insert(word); // Вставляем слова в дерево
        }
    }

    if (query == "TPUSH") {
        tree.insert(tokens->next->next->data); // Вставка нового элемента
    } else if (query == "TGET") {
        if (tree.search(tree.root, tokens->next->next->data)) { // Поиск элемента
            cout << true << endl;
        } else {
            cout << false << endl;
        }
    } else if (query == "TCHECK") { // Проверка на полное бинарное дерево
        if (tree.isComplete()) {
            cout << "The tree is complete." << endl;
        } else {
            cout << "The tree is not complete." << endl;
        }
    } else {
        cout << "Wrong query" << endl;
    }
}

void addToData(Data &data, NodeT *node) {
    if (node) {
        addToData(data, node->left);
        data.str += node->data + " "; // Используем node->data вместо node->key
        addToData(data, node->right);
    }
}

size_t stringToSize(const string &str) {
  istringstream stream(str);
  size_t res;
  stream >> res;

  return res;
}
