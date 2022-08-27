#ifndef STRUCTURES_H_
#define STRUCTURES_H_

/* Generic Data Structures  */

typedef struct node
{
    void* object;
    struct node* left;
    struct node* right;
    struct node* next;
} TreeNode;

typedef struct llnode
{
    void* object;
    struct llnode* next;
} LLNode;

/* Menu Structure  */

typedef struct mnode
{
    LLNode* head;
    char screen[50];
    int size;
} mNode;

typedef struct mchoice
{
    int index;
    int code;
    char title[50];
} menuChoice;

/* File Reading Structures */

typedef struct listDir
{
    struct dirent* listData; //this includes the list name (return type of readdir)
    char title[300];
    int index; //this is how user will access a list
} listItems;

typedef struct listDirMask
{
    listItems* listlist; //an array of all items in the list file
    int listlistCount; //holds the amount of lists in the file to be accessed
    char directoryTitle[300];
} listDirectoryData;

/* Film Data Structures */

typedef struct film
{
    int year;
    float rating;
    char title[300]; //might not be how it works lol
    int rewatch;

    int yearWatched;
    int monthWatched;
    int dateWatched;

} filmData; // this is the specific film data

typedef struct filmDB
{
    char identifier[1000];
    TreeNode* yearSort;
    TreeNode* ratingSort;
    TreeNode* titleSort;
    int* size;
    int error;
} filmDB; // this is storing a collection of films and including numerous ways of sorting them



#endif // STRUCTURES_H_
