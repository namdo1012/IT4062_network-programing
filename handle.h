#ifndef __HANDLE_H__
#define __HANDLE_H__

#include "linkedlist.h"

// Return signin successfully user
Node *userAuth(linkedList *list);
Node *getUser(linkedList *list, char username[20]);
void updateUser(linkedList *list, nodeValType user, char option[10]);

void handleRegister(linkedList *list);
void handleActivate(linkedList *list);
void handleSignIn(linkedList *list);
void handleSearch(linkedList *list);
void handleChangePassword(linkedList *list);
void handleLogOut(linkedList *list);

#endif