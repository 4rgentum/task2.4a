#ifndef DIALOG_H
#define DIALOG_H

#include "get.h"
#include "root.h"

int D_Insert(Node** root);
int D_Erase(Node** root);
int D_Inorder(Node** root);
int D_Search(Node **root);
int D_TaskSearch(Node **root);
int D_Print(Node** root);
int D_load(Node** root);
int D_Timing();
int dialog(const char* msgs[], int flag);

#endif
