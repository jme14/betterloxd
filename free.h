#ifndef FREE_H_
#define FREE_H_

#include "../helpers.h"
#include "BST.h"

void freeAll(mNode* menuNode);

void freeTree(TreeNode* head);
void freeLL(LLNode* head);
void freeFilmDB(filmDB DB);

#endif // FREE_H_
