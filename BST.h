#ifndef BST_H_
#define BST_H_

#include "structures.h"


mNode* menu ( mNode* menuNode );
LLNode* insertTrueLL ( LLNode* head, void* newObject );

filmDB initFilmDB();

int insertNewFilm(filmData* newFilm, filmDB filmDB);

void insertLL(TreeNode* head, TreeNode* tail);
int findLLCount(TreeNode* head);

filmDB uploadDiary();
filmDB* getDiary(mNode* menuNode);
void getDiaryInfo(mNode* menuNode, char* identifier);

filmDB uploadList(char* listTitle);

filmDB* getDB(mNode* menuNode, char* listTitle);
filmDB* getDBbyIndex(mNode* menuNode, int index);

void removeDB(mNode* menuNode, char* identifier);
void printDBlist(mNode* menuNode);

filmData** findByYear(int year, filmDB filmDB);
filmData** fBYear(int year, TreeNode* node);
filmData** findByRating(float rating, filmDB filmDB);
filmData** fBRating(float rating, TreeNode* node);
filmData** findByTitle(char* title, filmDB filmDB);
filmData** fBTitle(char* title, TreeNode* node);

int stringToInteger(char* string);

int removeByTitle(char* title, filmDB filmDB);

void freeFilmDB(filmDB filmDB);

void printFilmData(filmData* fD);

void printDatabase(filmDB filmDatabase, char* sortType);
void pDB(TreeNode* head, int* printCount);



char* getPrompt(); //REQUIRES FREEING RETURNED ITEM

TreeNode* traverseTree(TreeNode* head, char* location);

#endif // BST_H_
