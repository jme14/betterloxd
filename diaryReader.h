#ifndef DIARYREADER_H_
#define DIARYREADER_H_

#include "../helpers.h"
#include "BST.h"
#include "LBreader.h"


void initNode(int tokens, filmData* node, char* fileLine);

filmData** fileReader(char* fileLocation);

#endif // DIARYREADER_H_
