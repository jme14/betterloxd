#ifndef LISTREADER_H_
#define LISTREADER_H_

#include "../csHelpers/helpers.h"
#include "BST.h"
#include "LBreader.h"

int* getListFileLineCount(FILE* fp);
void initListNode(filmData* node, char* fileLine);

filmData** listFileReader( char* fileLocation );
#endif // LISTREADER_H_
