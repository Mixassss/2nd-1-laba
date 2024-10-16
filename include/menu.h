#ifndef menu_h
#define menu_h

#include "arr.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "ht.h"
#include "tree.h"

#include "utility.h"

void write(const string& path, const string& text);
string Ftext(const string& path, const string& nameStruct);
void aMenu(const string& command, const string& path);
void lMenu(const string& command, const string& path);
void qMenu(const string& command, const string& path);
void sMenu(string& command, string& path);
void hMenu(string& command, string& path);
void tMenu(string& command, string& path);

#endif // MENU_H
