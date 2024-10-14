#include "../include/file_manager.h"

void readValuesFromFile(const string &path, Data &data) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << path << endl;
        return;
    }

    string line;
    int currentLine = 0;

    while (getline(file, line)) {
        currentLine++;
        istringstream iss(line);
        string name;

        if (iss >> name && name == data.name) {
            data.numLine = currentLine; 

            string value;
            data.str.clear(); // Очистка предыдущих значений
            while (iss >> value) {
                data.str += value + " ";
            }
            data.str.pop_back(); // Удаление последнего пробела
            break; // Выход из цикла после нахождения нужной строки
        }
    }
}

bool replaceLineInFile(const string &filePath, int lineNumber, const string &newLine) {
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return false;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cerr << "Error: Unable to create temporary file." << endl;
        return false;
    }

    string line;
    int currentLine = 1;
    bool lineReplaced = false;

    while (getline(inputFile, line)) {
        if (currentLine == lineNumber) {
            tempFile << newLine << endl;
            lineReplaced = true;
        } else {
            tempFile << line << endl;
        }
        currentLine++;
    }

    if (!lineReplaced && lineNumber == 0) { // Если lineNumber равен 0, добавляем новую строку в начало
        tempFile << newLine << endl; 
    }

    inputFile.close();
    tempFile.close();

    if (remove(filePath.c_str()) != 0) { // Удаление оригинального файла
        cerr << "Error: Unable to delete original file." << endl;
        return false;
    }

    if (rename("temp.txt", filePath.c_str()) != 0) { // Переименование временного файла
        cerr << "Error: Unable to rename temporary file." << endl;
        return false;
    }

    return true;
}
