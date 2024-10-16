#include "../include/menu.h"

void write(const string& path, const string& text) { // Функция записи данных в файл
  ofstream fout(path);
  if (!fout.is_open()) {
    cout << "Не удалось открыть файл для записи" << endl;
    return;
  }
  fout << text;
}

string Ftext(const string& path, const string& nameStruct) { // Функция сохранения фулл текста файла без нужной структуры
  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл" << endl;
    return "";
  }

  string str, text;
  while (getline(fin, str)) { // Сохранение фулл текста в переменную
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens != nameStruct) {
      text += str + "\n";
    }
  }

  fin.close();
  return text;
}

Array aReadFile(const string& path, const string& nameStruct) {
  Array arr;
  string str;

  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл для чтения" << endl;
    return arr; // Возвращаем пустой массив, если не удалось открыть файл
  }

  while (getline(fin, str)) {
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
      if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
        while (getline(ss, tokens, ' ')) {
          arr.addToEnd(tokens); // Добавляем элементы в массив
        }
      }
  }
  fin.close();
  return arr;
}

void MPUSH (const string& data, const string& path, const string& value) {
  string ftext = Ftext(path, data);
  Array arr = aReadFile(path, data);

  string str;
  if (arr.getSize() != 0) {
    arr.addToEnd(value);
    str = data + ' ';
    for (size_t i = 0; i < arr.getSize(); ++i) {
      str += arr.getIndex(i) + ' ';
    }
    ftext += str;
    write(path, ftext);
  } else {
      str = data + ' ' + value;
      ftext += str;
      write(path, ftext);
    }
}

void MPUSHIND(const string& name, const string& value, size_t index, const string& path) {
  Array arr = aReadFile(path, name);
  if (index > arr.getSize()) {
    cout << "Индекс выходит за пределы массива!" << endl;
    return;
  }

  string str;
  arr.addAtIndex(index, value); // Используем функцию для добавления по индексу
  str = name + ' ';
  for (size_t i = 0; i < arr.getSize(); ++i) {
    str += arr.getIndex(i) + ' ';
  }  
  write(path, str);
}

void MREMOVE(const string& name, size_t index, const string& path) {
  Array arr = aReadFile(path, name);
  if (index >= arr.getSize()) {
    cout << "Индекс выходит за пределы массива!" << endl;
    return;
  } 
  arr.removeAtIndex(index);
    
  string str;
  str = name + ' ';
  for (size_t i = 0; i < arr.getSize(); ++i) {
    str += arr.getIndex(i) + ' ';
  }
  write(path, str);
}

void MREPLACE(const string& name, const string& value, size_t index, const string& path) {
  Array arr = aReadFile(path, name);
    
  if (index >= arr.getSize()) {
    cout << "Индекс выходит за пределы массива!" << endl;
    return;
  }
  arr.replaceAtIndex(index, value);
    
  string str;
  str = name + ' ';
  for (size_t i = 0; i < arr.getSize(); ++i) {
    str += arr.getIndex(i) + ' ';
  }
  write(path, str);
}

void MGET(string& data, size_t& index, const string& path) {
  Array arr = aReadFile(path, data);

  if (arr.getSize() != 0 && index < arr.getSize()) {
    cout << arr.getIndex(index) << endl; // Используем метод get для получения значения
  } else {
      throw out_of_range("Ошибка: Нет такого массива или индекс выходит за его размеры ");
  }
}

void MSIZE(const string& name, const string& path) {
  Array arr = aReadFile(path, name);

  if (arr.getSize() != 0) {
    cout << arr.getSize() << endl; // Выводим размер массива
  } else {
    throw out_of_range("Ошибка. Нет такого массива или он пуст ");
  }
}

void MPRINT(const string& name, const string& path) {
  Array arr = aReadFile(path, name);

  if (arr.getSize() != 0) {
    arr.ShowArray(); // Печатаем массив
  } else {
  throw out_of_range("Ошибка. Нет такого массива или он пуст ");
  }
}

void aMenu(const string& command, const string& path) { // Функция обработки команд массива
  string name, value;
  size_t index;

  if (command.find("MPUSH ") == 0) {
    string cons = command.substr(6); 
    stringstream stream(cons);
    stream >> name >> value;
    MPUSH(name, path, value);
  } else if (command.find("MPUSHIND ") == 0) {
    string cons = command.substr(9);
    stringstream stream(cons);
    stream >> name >> value >> index;
    MPUSHIND(name, value, index, path);
  } else if (command.find("MREMOVE ") == 0) {
    string cons = command.substr(8);
    stringstream stream(cons);
    stream >> name >> index;
    MREMOVE(name, index, path);
  } else if (command.find("MREPLACE ") == 0) {
    string cons = command.substr(9);
    stringstream stream(cons);
    stream >> name >> value >> index;
    MREPLACE(name, value, index, path);
  } else if (command.find("MGET ") == 0) {
    string cons = command.substr(5);
    stringstream stream(cons);
    stream >> name >> index;
    MGET(name, index, path);
  } else if (command.find("MSIZE ") == 0) {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name;
    MSIZE(name, path);
  } else if (command.find("MPRINT ") == 0) {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name;
    MPRINT(name, path);
  } else {
    throw out_of_range("Ошибка. Нет такой команды ");
  }
}

SinglyLinkedList slReadFile(const string& path, const string& nameStruct) {
  SinglyLinkedList data;
  string str;

  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл для чтения" << endl;
    return data; // Возвращаем пустой массив, если не удалось открыть файл
  }

  while (getline(fin, str)) {
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
      while (getline(ss, tokens, ' ')) {
        data.pushBack(tokens); // Добавляем элементы в массив
      }
    }
  }
  fin.close();
  return data;
}

void LPUSH(const string& name, const string& value, const string& path, const string& check) {
  string textfull = Ftext(path, name);
  SinglyLinkedList data = slReadFile(path, name);

  if (!data.isEmpty()) {
    (check == "back") ? data.pushBack(value) : data.pushFront(value);
    string str = name + ' ';
    Node* current = data.getHead(); // Значение текущего элемента
    while (current) {
      str += current->data + ' ';
      current = current->next;
      }
    textfull += str;
    write(path, textfull);
  } else {
      string str = name + ' ' + value;
      write(path, str); // перезаписываем новый элемент
  }
}

void LPOP(const string& name, const string& path, const string& check) {
  SinglyLinkedList data = slReadFile(path, name);
  string textfull = Ftext(path, name);

  if (!data.isEmpty()) {
    (check == "back") ? data.popBack() : data.popFront();
    string str = name + ' ';
    Node* current = data.getHead(); // Значение текущего элемента
    while (current) {
      str += current->data + ' ';
      current = current->next;
    }
    textfull += str;
    write(path, textfull);
    } else {
      throw out_of_range("Ошибка: нет такого списка или он пуст");
    }
}

void LREMOVE(const string& name, const string& value, const string& path) {
  string textfull = Ftext(path, name);
  SinglyLinkedList data = slReadFile(path, name);

  if (!data.isEmpty()) {
    data.removeAt(value); // Удаляем элемент
    string str = name + ' ';
    Node* current = data.getHead(); // Значение текущего элемента
    while (current) {
      str += current->data + ' ';
      current = current->next;
      }
    textfull += str;
    write(path, textfull);
    } else {
      throw out_of_range("Ошибка, нет такого списка или он пуст!");
  }
}

void LGET(const string& name, const string& value, const string& filename) {
  SinglyLinkedList data = slReadFile(filename, name);

  if (!data.isEmpty()) {
    int index = data.find(value); // Используем метод find
    if (index == -1) {
      throw out_of_range("Нет такого значения в списке");
    } else {
      cout << "Индекс значения: " << index << endl;
    }
    } else {
      throw out_of_range("Ошибка: нет такого списка");
    }
}

void LPRINT(const string& name, const string& filename) {
  SinglyLinkedList data = slReadFile(filename, name);

  if (!data.isEmpty()) {
    data.print();
  } else {
      throw out_of_range("Ошибка, нет такого списка или он пуст");
  }
}

void lMenu(const string& command, const string& path) {
  string name, value;

  if (command.find("LPUSHB ") == 0) {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    LPUSH(name, value, path, "back");
  } else if (command.find("LPUSHF ") == 0) {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    LPUSH(name, value, path, "front");
  } else if (command.find("LPOPB ")) {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name;
    LPOP(name, path, "back");
  } else if (command.find("LPOPF ")) {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name;
    LPOP(name, path, "front");
  } else if (command.find("LREMOVE ")) {
    string cons = command.substr(8);
    stringstream stream(cons);
    stream >> name >> value;
    LREMOVE(name, value, path);
  } else if (command.find("LGET ")) {
    string cons = command.substr(5);
    stringstream stream(cons);
    stream >> name >> value;
    LGET(name, value, path);
  } else if (command.find("LPRINT ")) {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name;
    LPRINT(name, path);
  } else {
    throw out_of_range("Ошибка: нет такой команды");
  }
}

void qReadFile(const string& path, const string& nameStruct, Queue& data) {
    string str;
    ifstream fin(path);
    if (!fin.is_open()) {
        throw out_of_range("Не удалось открыть файл для чтения");
        return; // Завершаем выполнение функции
    }

    while (getline(fin, str)) {
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' ');
        if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
            while (getline(ss, tokens, ' ')) {
                data.push(tokens); // Добавляем элементы в очередь
            }
        }
    }
    fin.close();
}

void QPUSH(const string& name, const string& value, const string& path) {
  string textfull = Ftext(path, name);
  Queue data;
  qReadFile(path, name, data);
    
  data.push(value); // Добавляем новое значение в очередь
  string str = name + ' '; // Создаем строку для записи
  Queue temp = data; // Копируем текущую очередь для записи
  while (!temp.isempty()) {
    str += temp.peek() + ' ';
    temp.pop();
  }
  textfull += str;
  write(path, textfull); // Записываем строку в файл
}


void QPOP(const string& name, const string& path) {
  string textfull = Ftext(path, name);
  Queue data;
  qReadFile(path, name, data);

    if (data.isempty()) {
        throw out_of_range("Ошибка: нет такой очереди или она пуста");
    }

    data.pop(); // Удаляем элемент из очереди

    // Создаем строку для записи
    string str = name + ' ';
    Queue temp = data; // Копируем текущую очередь для записи
    while (!temp.isempty()) {
        str += temp.peek() + ' ';
        temp.pop();
    }
    textfull += str;
    write(path, textfull); // Записываем строку в файл
}

void QPRINT(const string& name, const string& path) {
    Queue data;
    qReadFile(path, name, data);
    
    if (data.isempty()) {
        throw out_of_range("Нет такой очереди или она пуста");
    }

    while (!data.isempty()) {
        cout << data.peek() << " ";
        data.pop();
    }
    cout << endl;
}

void qMenu(const string& command, const string& path) {
    string name, value;

    if (command.find("QPUSH ") == 0) {
      string cons = command.substr(6);
      stringstream stream(cons);
      stream >> name >> value;
      QPUSH(name, value, path);
    } else if (command.find("QPOP ") == 0) {
        string cons = command.substr(5);
      stringstream stream(cons);
      stream >> name;
      QPOP(name, path);
    } else if (command.find("QPRINT ") == 0) {
      string cons = command.substr(7);
      stringstream stream(cons);
      stream >> name;
      QPRINT(name, path);
    } else {
      throw out_of_range("Ошибка, нет такой команды");
    }
}

void sReadFile(const string& path, const string& nameStruct, Stack& data) {
  Stack doubly(30);
  string str;
  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл для чтения" << endl;
  }

  while (getline(fin, str)) {
    stringstream ss(str);
    string tokens;
    getline(ss, tokens, ' ');
    if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
    while (getline(ss, tokens, ' ')) {
      doubly.push(tokens);
      }
    while (getline(ss, tokens, ' ')) {
      data.push(data.peek());
      doubly.pop(); // Добавляем элементы в список 
      }
    }
  }
  fin.close();
}

void SPUSH(string& name, string& value, string& path) {
  string textfull = Ftext(path, name);
  Stack data; // Создаем стек
  sReadFile(path, name, data); // Передаем стек в функцию

  data.push(value);
  string str = name + ' ';
  while (!data.isEmpty()) {
    str += data.peek() + ' ';
    data.pop();
  }
  textfull += str;
  write(path, textfull);
}

void SPOP(string& name, string& path) {
    string textfull = Ftext(path, name);
    Stack data;
    sReadFile(path, name, data); // Исправлено имя функции

    if (!data.isEmpty()) {
        data.pop();
        string str = name + ' ';
        while (!data.isEmpty()) {
            str += data.peek() + ' ';
            data.pop();
        }
        textfull += str;
        write(path, textfull);
    } else {
        throw out_of_range("Ошибка, нет такого стека или он пуст!");
    }
}

void SPRINT(string& name, string& path) {
    Stack data;
    sReadFile(path, name, data); // Исправлено имя функции

    if (!data.isEmpty()) {
        while (!data.isEmpty()) {
            cout << data.peek() << " ";
            data.pop();
        }
        cout << endl;
    } else {
        throw out_of_range("Нет такого стека или он пуст!");
    } 
}

void sMenu(string& command, string& path) { // Функция обработки команд стека
    string name, value;

    if (command.find("SPUSH ") == 0) {
      string cons = command.substr(6);
      stringstream stream(cons);
      stream >> name >> value;
      SPUSH(name, value, path);
    } else if (command.find("SPOP ") == 0) {
        string cons = command.substr(5);
      stringstream stream(cons);
        stream >> name;
        SPOP(name, path);
    } else if (command.find("SPRINT ") == 0) {
        string cons = command.substr(7);
      stringstream stream(cons);
        stream >> name;
        SPRINT(name, path);
    } else {
        throw out_of_range("Ошибка, нет такой команды!");
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
