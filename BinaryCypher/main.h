#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>

char* dTOb(long dec);


char* createBinaryString(int* choices);
long returnIntegerFromBinaryString(char* binaryString);
void readMenuText();
long getMenuChoices();


void printLimitedMenuChoice(long code);
#endif // MAIN_H_
