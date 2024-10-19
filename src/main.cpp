#include "../include/arr.h"
#include "../include/list.h"
#include "../include/queue.h"
#include "../include/stack.h"
#include "../include/ht.h"
#include "../include/tree.h"

void printUsage( char* programName) {
    cerr << "Использование: " << programName << " --file <filename> --query '<command>'" << endl;
}

string Ftext(string& path, string& nameStruct) { // Функция сохранения фулл текста файла без нужной структуры
  string str, text;
  ifstream fin;
  fin.open(path);

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

void write(string& path, string& text) { // Функция записи данных в файл
  ofstream fout(path);
  if (!fout.is_open()) {
    cout << "Не удалось открыть файл для записи" << endl;
    return;
  }
  fout << text;
  fout.close();
}

Array aReadFile(string& path, string& nameStruct) {
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

void MPUSH (string& data, string& path, string& value) {
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

void MPUSHIND(string& name, string& value, size_t index, string& path) {
  string ftext = Ftext(path, name);
  Array arr = aReadFile(path, name);

  string str;
    if (arr.getSize() != 0 && index < arr.getSize()) {
        arr.addAtIndex(index, value);
        str = name + ' ';
        for (int i = 0; i < arr.getSize(); ++i) {
            str += arr.getIndex(i) + ' ';
        }
        ftext += str;
        write(path, ftext);
    } else if (arr.getSize() == 0 && index == 0){ // создание массива, если его нет
        str = name + ' ' + value;
        ftext += str;
        write(path, ftext);
  } else {
        cout << "Ошибка, индекс выходит за размеры массива!" << endl;
        exit(1);
    }
}

void MREMOVE(string& name, size_t index, string& path) {
  string textfull = Ftext(path, name);
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
  textfull += str;
  write(path, textfull);
}

void MREPLACE(string& name, string& value, size_t index, string& path) {
  string textfull = Ftext(path, name);
  Array arr = aReadFile(path, name);
    
  if (index >= arr.getSize()) {
    cout << "Индекс выходит за пределы массива!" << endl;
    return;
  }
  arr.replaceAtIndex(index, value);
    
  string str;
  str = name + ' ';
  if (arr.getSize() != 0 && index < arr.getSize()) {
    arr.replaceAtIndex(index, value);
  for (size_t i = 0; i < arr.getSize(); ++i) {
    str += arr.getIndex(i) + ' ';
  }
  textfull += str;
  write(path, textfull);
  }
}

void MGET(string& data, size_t& index, string& path) {
  Array arr = aReadFile(path, data);

  if (arr.getSize() != 0 && index < arr.getSize()) {
    cout << arr.getIndex(index) << endl; // Используем метод get для получения значения
  } else {
      throw out_of_range("Ошибка: Нет такого массива или индекс выходит за его размеры ");
  }
}

void MSIZE(string& name, string& path) {
  Array arr = aReadFile(path, name);

  if (arr.getSize() != 0) {
    cout << arr.getSize() << endl; // Выводим размер массива
  } else {
    throw out_of_range("Ошибка. Нет такого массива или он пуст ");
  }
}

void MPRINT(string& name, string& path) {
  Array arr = aReadFile(path, name);

  if (arr.getSize() != 0) {
    arr.ShowArray(); // Печатаем массив
  } else {
  throw out_of_range("Ошибка. Нет такого массива или он пуст ");
  }
}

void aMenu(string& command, string& path) { // Функция обработки команд массива
  string name, value;
  size_t index;

  if (command.substr(0, 6) == "MPUSH ") {
    string cons = command.substr(6); 
    stringstream stream(cons);
    stream >> name >> value;
    MPUSH(name, path, value);
  } else if (command.substr(0, 9) == "MPUSHIND ") {
    stringstream stream(command.substr(9));
    stream >> name >> value >> index;
    MPUSHIND(name, value, index, path);
  } else if (command.substr(0, 8) == "MREMOVE ") {
    string cons = command.substr(8);
    stringstream stream(cons);
    stream >> name >> index;
    MREMOVE(name, index, path);
  } else if (command.substr(0, 9) == "MREPLACE ") {
    string cons = command.substr(9);
    stringstream stream(cons);
    stream >> name >> value >> index;
    MREPLACE(name, value, index, path);
  } else if (command.substr(0, 5) == "MGET ") {
    string cons = command.substr(5);
    stringstream stream(cons);
    stream >> name >> index;
    MGET(name, index, path);
  } else if (command.substr(0, 6) == "MSIZE ") {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name;
    MSIZE(name, path);
  } else if (command.substr(0, 7) == "MPRINT ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name;
    MPRINT(name, path);
  } else {
    throw out_of_range("Ошибка. Нет такой команды ");
  }
}

SinglyLinkedList slReadFile( string& path,  string& nameStruct) {
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

void LPUSH( string& name,  string& value,  string& path,  string check) {
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

void LPOP( string& name,  string& path,  string check) {
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

void LREMOVE( string& name,  string& value,  string& path) {
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

void LGET( string& name,  string& value,  string& filename) {
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

void LPRINT( string& name,  string& filename) {
  SinglyLinkedList data = slReadFile(filename, name);

  if (!data.isEmpty()) {
    data.print();
  } else {
      throw out_of_range("Ошибка, нет такого списка или он пуст");
  }
}

void lMenu( string& command,  string& path) {
  string name, value;

  if (command.substr(0, 7) == "LPUSHB ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    LPUSH(name, value, path, "back");
  } else if (command.substr(0, 7) == "LPUSHF ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name >> value;
    LPUSH(name, value, path, "front");
  } else if (command.substr(0, 6) == "LPOPB ") {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name;
    LPOP(name, path, "back");
  } else if (command.substr(0, 6) == "LPOPF ") {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name;
    LPOP(name, path, "front");
  } else if (command.substr(0, 8) == "LREMOVE ") {
    string cons = command.substr(8);
    stringstream stream(cons);
    stream >> name >> value;
    LREMOVE(name, value, path);
  } else if (command.substr(0, 5) == "LGET ") {
    string cons = command.substr(5);
    stringstream stream(cons);
    stream >> name >> value;
    LGET(name, value, path);
  } else if (command.substr(0, 7) == "LPRINT ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name;
    LPRINT(name, path);
  } else {
    throw out_of_range("Ошибка: нет такой команды");
  }
}

void qReadFile( string& path,  string& nameStruct, Queue& data) {
    string str;
    ifstream fin;
    fin.open(path);
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

void QPUSH( string& name,  string& value,  string& path) {
  string textfull = Ftext(path, name);
  Queue data(30);
  qReadFile(path, name, data);
    
  string str;
  if (data.Size() != 0) {
    data.push(value);
    str = name + ' ';
    while(data.Size() != 0) {
      str += data.peek() + ' ';
      data.pop();
      }
      textfull += str;
      write(path, textfull);
    } else {
      str = name + ' ' + value;
      textfull += str;
      write(path, textfull);
  }
}


void QPOP( string& name,  string& path) {
  string textfull = Ftext(path, name);
  Queue data(30);
  qReadFile(path, name, data);

    string str;
    if (data.Size() != 0) {
        data.pop();
        str = name + ' ';
        while(data.Size() != 0) {
            str += data.peek() + ' ';
            data.pop();
        }
        textfull += str;
        write(path, textfull);
    } else {
        cout << "Ошибка, нет такой очереди или она пуста!" << endl;
        exit(1);
    }
}

void QPRINT( string& name,  string& path) {
    Queue data(30);
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

void qMenu( string& command,  string& path) {
    string name, value;

    if (command.substr(0, 6) == "QPUSH ") {
      string cons = command.substr(6);
      stringstream stream(cons);
      stream >> name >> value;
      QPUSH(name, value, path);
    } else if (command.substr(0, 5) == "QPOP ") {
        string cons = command.substr(5);
      stringstream stream(cons);
      stream >> name;
      QPOP(name, path);
    } else if (command.substr(0, 7) == "QPRINT ") {
      string cons = command.substr(7);
      stringstream stream(cons);
      stream >> name;
      QPRINT(name, path);
    } else {
      throw out_of_range("Ошибка, нет такой команды");
    }
}

void sReadFile( string& path,  string& nameStruct, Stack& data) {
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
    while (doubly.size() != 0) {
      data.push(doubly.peek());
      doubly.pop();
      }
    }
  }
  fin.close();
}

void SPUSH(string& name, string& value, string& path) {
  string textfull = Ftext(path, name);
  Stack data(30); // Создаем стек
  sReadFile(path, name, data); // Передаем стек в функцию

  string str;
    if (data.size() != 0) {
        data.push(value);
        str = name + ' ';
        while(data.size() != 0) {
            str += data.peek() + ' ';
            data.pop();
        }
        textfull += str;
        write(path, textfull);
    } else {
        str = name + ' ' + value;
        textfull += str;
        write(path, textfull);
    }
}

void SPOP(string& name, string& path) {
  string textfull = Ftext(path, name);
  Stack data(30);
  sReadFile(path, name, data); // Исправлено имя функции

  string str;
  if (data.size() != 0) {
    data.pop();
    str = name + ' ';
    while(data.size() != 0) {
      str += data.peek() + ' ';
      data.pop();
      }
      textfull += str;
        write(path, textfull);
    } else {
        cout << "Ошибка, нет такого стека или он пуст!" << endl;
        exit(1);
    }
}

void SPRINT(string& name, string& path) {
  Stack data(30);
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

  if (command.substr(0, 6) == "SPUSH ") {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name >> value;
    SPUSH(name, value, path);
    } else if (command.substr(0, 5) == "SPOP ") {
    stringstream stream(command.substr(5));
    stream >> name;
    SPOP(name, path);
    } else if (command.substr(0, 7) == "SPRINT ") {
      string cons = command.substr(7);
      stringstream stream(cons);
      stream >> name;
      SPRINT(name, path);
    } else {
      throw out_of_range("Ошибка, нет такой команды!");
    }
}

Hash_table hReadFile(string& path, string& name) { // ф-ия чтения Хеш-таблицы из файла
    Hash_table nums;
    string str;
    ifstream fin;
    fin.open(path);
    while (getline(fin, str)) {
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                int position = token.find_first_of(':');
                token.replace(position, 1, " ");
                stringstream iss(token);
                string key, value;
                iss >> key >> value;
                nums.insert(key, value);
            }
        }
    }
    fin.close();
    return nums;
}

string printHashTable( Hash_table& ht, string& name) { // Функция для перебора всех элементов хеш-таблицы
    string str = name + ' ';
    for (int i = 0; i < SIZE; ++i) {
        HNode* current = ht.table[i];
        while (current) {
            str += current->key + ':' + current->value + ' ';
            current = current->next;
        }
    }
    return str;
}
void HPUSH(string& name, string& key, string& value, string& path) {
    string textfull = Ftext(path, name);
    Hash_table nums = hReadFile(path, name);
    
    string str;
    if (nums.sizetable != 0) {
        nums.insert(key, value);
        str = printHashTable(nums, name);
        textfull += str;
        write(path, textfull);
    } else {
        str = name + ' ' + key + ':' + value;
        textfull += str;
        write(path, textfull);
    }
}
void HPOP(string& name, string& key, string& path) {
  string textfull = Ftext(path, name);
  Hash_table nums = hReadFile(path, name);

  string str;
  if (nums.sizetable != 0) {
    if (nums.remove(key)) {
      str = printHashTable(nums, name);
      textfull += str;
      write(path, textfull);
      } else {
        throw out_of_range("Ошибка, нет такого ключа");
      }
    } else {
      throw out_of_range("Ошибка, нет такой таблицы или она пуста");
    }
}
void HGET(string& name, string& key, string& path) {
  Hash_table data = hReadFile(path, name);

  string str;
  if (data.sizetable != 0) {
    string value;
    if (!data.get(key, value)) {
      throw out_of_range("Ошибка: нет такого ключа");
    }
    } else {
      throw out_of_range("Ошибка: нет такой таблицы или она пуста");
    }
}
void hMenu(string& command, string& path) { // ф-ия обработки команд Хеш-таблицы
  string name, key, value;

  if (command.substr(0, 6) == "HPUSH ") {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name >> key >> value;
    HPUSH(name, key, value, path);
    } else if (command.substr(0, 5) == "HPOP ") {
    string cons = command.substr(5);
    stringstream stream(cons);
    stream >> name >> key;
    HPOP(name, key, path);
    } else if (command.substr(0, 5) == "HGET ") {
    string cons = command.substr(5);
    stringstream stream(cons);
    stream >> name >> key;
    HGET(name, key, path);
    } else {
    throw out_of_range("Ошибка, нет такой команды"); 
    }
}

CompleteBinaryTree tReadFile(string& path, string& name) {
  CompleteBinaryTree data;
  string str;
  ifstream fin(path);
  if (!fin.is_open()) {
    cout << "Не удалось открыть файл для чтения" << endl;
  }

  while (getline(fin, str)) {
    stringstream ss(str);
    string token;
    getline(ss, token, ' ');
    if (token == name) {
      while (getline(ss, token, ' ')) {
        data.insert(stoi(token));
        }
      }
    }
  fin.close();
  return data;
}

void TPush(string& name, int value, string& path) {
  string textfull = Ftext(path, name);
    CompleteBinaryTree data = tReadFile(path, name);
    string str;
  
  if (data.size != 0) {
    data.insert(value);
    str = name + ' ' + data.toString(data.root); 
    textfull += str;
    write(path, textfull); 
    } else {
        str = name + ' ' + to_string(value);
        textfull += str;
        write(path, textfull);
  }
}

void TSearch(string& name, int value, string& path) {
    CompleteBinaryTree nums = tReadFile(path, name);
    if (!nums.isEmpty()) {
        cout << (nums.search(nums.root, value) ? "True" : "False") << endl;
    } else {
        throw out_of_range("Ошибка, нет такого дерева или оно пусто");
    }
}

void TCheck(string& name, string& filename) {
    CompleteBinaryTree nums = tReadFile(filename, name);
    if (!nums.isEmpty()) {
        cout << (nums.isComplete(nums.root, 0, nums.size) ? "True" : "False") << endl;
    } else {
        throw out_of_range("Ошибка, нет такого дерева или оно пусто");
    }
}

void TPrint(string& name, string& filename) {
  CompleteBinaryTree nums = tReadFile(filename, name);
  if (!nums.isEmpty()) {
    nums.printTree(nums.root);
    cout << endl; // Добавляем перевод строки для удобства
    } else {
      throw out_of_range("Ошибка, нет такого дерева или оно пусто");
    }
}

void tMenu(string& command, string& path) {
  string name;
  int value;

  if (command.find("TPUSH ") == 0) {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name >> value;
    TPush(name, value, path);
    } else if (command.find("TSEARCH ") == 0) {
      string cons = command.substr(8);
      stringstream stream(cons);
      stream >> name >> value;
      TSearch(name, value, path);
    } else if (command.find("TCHECK ") == 0) {
      string cons = command.substr(7);
      stringstream stream(cons);
      stream >> name;
      TCheck(name, path);
    } else if (command.find("TPRINT ") == 0) {
      string cons = command.substr(7);
      stringstream stream(cons);
      stream >> name;
      TPrint(name, path);
    } else {
        throw out_of_range("Ошибка: нет такой команды"); 
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printUsage(argv[0]);
        return 1;
    }

    string filename; // Разбор аргументов командной строки
    string query;

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            if (++i < argc) {
                filename = argv[i];
            } else {
                printUsage(argv[0]);
                return 1;
            }
        } else if (string(argv[i]) == "--query") {
            if (++i < argc) {
                query = argv[i];
            } else {
                printUsage(argv[0]);
                return 1;
            }
        }
    }

    // Обработка команды
    if (query.empty()) {
        cout << "Ошибка: Должна быть указана команда." << endl;
        return 1;
    }

    switch (query[0]) {
        case 'M':
            aMenu(query, filename);
            break;
        case 'L':
            lMenu(query, filename);
            break;
        case 'Q':
            qMenu(query, filename);
            break;
        case 'S':
            sMenu(query, filename);
            break;
        case 'H':
            hMenu(query, filename);
            break;
        case 'T':
            tMenu(query, filename);
            break;
        default:
            cout << "Ошибка: Неизвестная структура данных." << endl;
            return 1;
    }

    return 0;
}
