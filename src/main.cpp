#include "../include/menu.h"

void printUsage(const char* programName) {
    cerr << "Использование: " << programName << " --file <filename> --query '<command>'" << endl;
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
