#include "../include/menu.h"
#include "../include/file_manager.h"

int main(int argc, char **argv) {
    // Проверка аргументов командной строки
    if (argc != 5 || string(argv[1]) != "--file" || string(argv[3]) != "--query") {
        cerr << "Usage: " << argv[0] << " --file <filename> --query <query>" << endl;
        return 1;
    }

    Data data;
    SinglyLinkedList SList;
    Array arr; // Создаем экземпляр класса Array
    Node *tokens = parse(argv[4]);
    
    if (!tokens || !tokens->next) {
        cerr << "Error: Invalid query." << endl;
        return 1;
    }

    data.name = tokens->next->data;
    HNode ht(data.name, ""); // Создаем HNode с именем и пустым значением
    readValuesFromFile(argv[2], data);

    // Обработка команды в зависимости от первого символа
    switch (tokens->data[0]) {
        case 'M':
            aMenu(tokens, arr);
            break;
        case 'Q':
            qMenu(tokens, data);
            break;
        case 'S':
            if (tokens->data[1] == 'L') {
                lsMenu(tokens, data); 
            } else {
                sMenu(tokens, data);
            }
            break;
        case 'D':
            ldMenu(tokens, data);
            break;
        case 'H':
            hMenu(tokens, data);
            break;
        case 'T':
            tMenu(tokens, data);
            break;
        case 'P':
            if (tokens->data == "PRINT") {
                cout << data.str << endl;
            }
            break;
        default:
            cout << "Wrong query" << endl;
            break;
    }

    replaceLineInFile(argv[2], data.numLine, data.str);

    SList.clearSList(); // Освобождение памяти для списка
    delete tokens; // Освобождение памяти для токенов
    return 0;
}
