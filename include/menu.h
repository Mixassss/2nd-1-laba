#ifndef menu_h
#define menu_h

#include "arr.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "ht.h"
#include "tree.h"

#include "utility.h"

void aMenu(Node *tokens, Array &data);
void lsMenu(Node* tokens, Data &data);
void ldMenu(Node* tokens, Data &data);
void qMenu(Node *tokens, Data &data);
void sMenu(Node* tokens, Data& data);
void hMenu(Node *tokens, Data &data);
void tMenu(Node *tokens, Data &data);
Node* parse(const string &input);
void addToData(Data &data, NodeT *node);
size_t stringToSize(const string &str);

#endif // MENU_H
