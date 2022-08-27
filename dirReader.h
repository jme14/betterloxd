#ifndef DIRREADER_H_
#define DIRREADER_H_

#include "../csHelpers/helpers.h"
#include "BST.h"

#endif // DIRREADER_H_

listDirectoryData getListDirectoryData(char* directory);

char* getListFileByIndex(listDirectoryData lDD, int index);
void printListDirectoryData(listDirectoryData lDD);
