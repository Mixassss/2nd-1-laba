#ifndef file_manager_h
#define file_manager_h

#include "utility.h"

void readValuesFromFile(const string &path, Data &data);
bool replaceLineInFile(const string &filePath, int lineNumber, const string &newLine);


#endif // FILE_MANAGER_H
