#ifndef FREE_H_
#define FREE_H_

#include "../csHelpers/helpers.h"
#include "BST.h"

typedef struct aK
{
    TreeNode** addressArray;
    filmData** FDaddressArray;
    int* size;
    int* FDsize;
} addKeep;

void freeAll(mNode* menuNode);


void addTNadd(TreeNode* head, addKeep aK);
void addFDadd(filmData* film, addKeep aK);

void freeTree(TreeNode* head, addKeep addressKeeper);
void freeAndClearTree(TreeNode* head, addKeep addressKeeper); // FREES DATA STRUCTURE TREENODE



void freeTreeLL(TreeNode* head, addKeep addressKeeper);
void freeLL(LLNode* head);
void freeFilmDB(filmDB DB);


void freeMenuChoice(menuChoice* mChoice);
#endif // FREE_H_
