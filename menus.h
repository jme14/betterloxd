#ifndef MENUS_H_
#define MENUS_H_

#include "../helpers.h"
#include "BST.h"
#include "userInput.h"
#include "dirReader.h"
#include "./BinaryCypher/main.h"


mNode* initMenu();
mNode* menu(mNode* menuNode);


char* getmChoiceByIndex(menuChoice* mChoice, int index);
menuChoice* getMenuChoiceScreen(long code);


mNode* exitMenuSection(mNode* menuNode, menuChoice* mChoice, int choiceIndex);
#endif // MENUS_H_
