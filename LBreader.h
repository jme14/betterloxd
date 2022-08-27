#ifndef LBREADER_H_
#define LBREADER_H_

#define MAXLENGTH 300

#include "../csHelpers/helpers.h"
#include "BST.h"

int getFileLineCount(FILE* fp);
int countCommaTokens(char* fileLine);

#endif // LBREADER_H_
