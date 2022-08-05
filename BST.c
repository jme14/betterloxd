#include "BST.h"
#include "../helpers.h"
#include "diaryReader.h"
#include "listReader.h"
#include "dirReader.h"
#include "userInput.h"
#include "filmNodeInsertion.h"
#include "menus.h"

#define SIZE 320

int main ( void  )
{
    mNode* menuNode = initMenu();
    menu(menuNode);
}

/* DB INITIALIZING  */

filmDB initFilmDB() // DB manipulation
    // CHECKED FOR FREEING!
{
    filmDB filmDB;

    TreeNode* yearSortHead = malloc(sizeof(TreeNode));

    yearSortHead->object = NULL;
    yearSortHead->left = NULL;
    yearSortHead->right = NULL;

    TreeNode* ratingSortHead = malloc(sizeof(TreeNode));

    ratingSortHead->object = NULL;
    ratingSortHead->left = NULL;
    ratingSortHead->right = NULL;

    TreeNode* titleSortHead = malloc(sizeof(TreeNode));

    titleSortHead->object = NULL;
    titleSortHead->left = NULL;
    titleSortHead->right = NULL;

    filmDB.yearSort = yearSortHead;
    filmDB.ratingSort = ratingSortHead;
    filmDB.titleSort = titleSortHead;


    if ( filmDB.titleSort == NULL )
    {
        puts("Improper initialization of titleSort");
    }
    filmDB.size = 0;
    filmDB.error = 0;

    return filmDB;
}


int insertNewFilm(filmData* newFilm, filmDB filmDB) // DB initialization
    /* this function inserts new film into the BSTs of a database */
    // CHECKED FOR FREEING
{
    TreeNode* newTitleNode = malloc(sizeof(TreeNode));
    TreeNode* newYearNode = malloc(sizeof(TreeNode));
    TreeNode* newRatingNode = malloc(sizeof(TreeNode));


    newTitleNode->left = NULL;
    newTitleNode->right = NULL;
    newTitleNode->next = NULL;
    newTitleNode->object = newFilm;

    newYearNode->left = NULL;
    newYearNode->right = NULL;
    newYearNode->next = NULL;
    newYearNode->object = newFilm;

    newRatingNode->left = NULL;
    newRatingNode->right = NULL;
    newRatingNode->next = NULL;
    newRatingNode->object = newFilm;

    if ( newTitleNode != NULL && newYearNode != NULL && newFilm != NULL)
    {
        //puts("Entering hell");
        filmDB.titleSort = insertNodeByTitle(filmDB.titleSort, newTitleNode, newFilm->title);
        //puts("Leaving hell");

        //puts("Entering heaven");
        filmDB.yearSort = insertNodeByYear(filmDB.yearSort, newYearNode, newFilm->year);
        //puts("Leaving heaven");

        filmDB.ratingSort = insertNodeByRating(filmDB.ratingSort, newRatingNode, newFilm->rating);

        //traverseTree(filmDB.ratingSort, "ratingSort");
        /* puts("\n------\n"); */
        /* traverseTree(filmDB.titleSort, "titleSort"); */
        /* puts("\n------\n"); */
        /* traverseTree(filmDB.yearSort, "yearSort"); */
        /* puts("\n------\n"); */
    }
    else
    {
        puts("Malloc failure or sum");
    }

    return filmDB.error;
}

LLNode* insertTrueLL( LLNode* head, void* newObject) // DB insertion
/* This function inserts a new database into a linked list of all DBs uploaded  */
    // CHECKED FOR FREEING
{

    if ( head == NULL )
    {
        // this means this list is empty and we need a new node

        LLNode* newNode = malloc(sizeof(LLNode));
        newNode->next = NULL;
        newNode->object = newObject;

        head = newNode;

        //printf("Head is pointing to %p\n", head);

        //puts("Inserted object");
    }

    else if ( head != NULL && head->object == NULL )
    {
        //puts("At the beginning of the list");
        //
        LLNode* newNode = malloc(sizeof(LLNode));
        head->next = newNode;
        head->object = newObject;
        newNode->next = NULL;
    }
    else
    {
        head->next = insertTrueLL(head->next, newObject);
    }
    return head;
}

TreeNode* traverseTree(TreeNode* head, char* location) // DB traversal
    // CHECKED FOR FREEING
{
    if ( head != NULL  )

    {
        puts("Going left");
        traverseTree(head->left, location);
        puts("Going Up");
        puts("Going Right");
        traverseTree(head->right, location);
        puts("Going Up");
    }

    printf("head for %s at %p\n", location, head);

    return head;
}

void insertLL(TreeNode* head, TreeNode* tail) // DB initialization
/* This is for dealing with duplicates at BSTs, NOT for insertion of finished DBs  */
// CHECKED FOR FREEING
{
    if ( head->next == NULL )
    {
        head->next = tail;
    }
    else
    {
        insertLL(head->next, tail);
    }
}

/* UPLOADING OR REMOVING DB FROM DB COLLECTION */

filmDB uploadDiary() // DB work
    // CHECKED FOR FREEING
{
    filmDB diaryDB = initFilmDB();
    strcpy(diaryDB.identifier, "Diary");

    //printf("diaryDB.identifier is %s\n", diaryDB.identifier);

    filmData** myFilms = fileReader("./lbData/diary.csv");
    int filmCount = getArraySize(myFilms);

    for ( int i = 0 ; i < filmCount ; i++ )
    {
        if ( myFilms[i] == NULL )
        {
            puts("FATAL ERROR: film node empty");
            exit (0);
        }
        else
        {
            if ( myFilms[i]->year != 0 )
            {

                insertNewFilm(myFilms[i], diaryDB);
                //printFilmData(myFilms[i]);
            }
        }
    }

    return diaryDB;
}

filmDB uploadList(char* listTitle) // Creating DB work
    // CHECKED FOR FREEING
 {
    filmDB listDB = initFilmDB();
    strcpy(listDB.identifier, listTitle);

    //filmData** myFilms = fileReader
    filmData** myFilms = listFileReader(listTitle);

    int filmCount = getArraySize(myFilms);

    for ( int i = 0  ; i < filmCount ; i++ )
    {
        if ( myFilms[i] == NULL )
        {
            puts("FATAL ERROR: film node empty");
            exit ( 0 );
        }
        else
        {
            if ( myFilms[i]->year != 0 )
            {
                insertNewFilm(myFilms[i], listDB);
            }
        }
    }
    return listDB;
}

void removeDB(mNode* menuNode, char* identifier)  //DB Work
    // CHECKED FOR FREEING
{
    LLNode* head = *menuNode->head;

    if ( head == NULL )
    {
        puts("FATAL ERROR: No DB in list");
        exit ( 0 );
    }

    filmDB* DB = NULL; // will start at first object
    int ifFound = 0;


    while ( ifFound == 0 && head != NULL )
    {
        if ( head->next != NULL )
        {
            DB = head->next->object;

            if ( DB != NULL && !strcmp(DB->identifier, identifier) ) //then the node AFTER the one DB is on is Diary
            {
                filmDB* finder = head->next->object;

                head->next = head->next->next;
                freeFilmDB(*finder);
                ifFound = 1;
            }
        }
        head = head->next;
    }

    menuNode->size--;
}
/* EDITING DB */

TreeNode* gDI(TreeNode* head, filmDB* diary) // Editing DB work
    // CHECKED FOR MEM LEAKS
{
    if ( head != NULL )
    {
        head->left = gDI(head->left, diary);

        filmData** answers = NULL;
        filmData* filmData = head->object;

        answers = findByTitle(filmData->title, *diary);

        if ( answers != NULL ) //as long as a diary entry is found, do the following
        {

            puts ("answers is NOT null actually");
            printf("found entry with title %s\n", filmData->title);

            int lastEntry = getArraySize(answers)-1;

            filmData->rating = answers[lastEntry]->rating;
            filmData->rewatch = answers[lastEntry]->rewatch;

            filmData->yearWatched = answers[lastEntry]->yearWatched;
            filmData->monthWatched = answers[lastEntry]->monthWatched;
            filmData->dateWatched = answers[lastEntry]->dateWatched;

        }

        head->right = gDI(head->right, diary) ;
    }
    return head;
}
void getDiaryInfo(mNode* menuNode, char* listIdentifier) // Editing DB work
    // CHECKED FOR MEM LEAKS
{
    filmDB* diary = getDiary(menuNode);

    if ( diary == NULL )
    {
        puts("No diary to compare to. This list will be missing information");
    }
    else
    {
        filmDB* list = getDB(menuNode, listIdentifier);
        puts("Entering gDI");
        gDI(list->titleSort, diary);
        puts("Exiting gDI");
    }
}

/* PRINTING DB  */
void printDBlist(mNode* menuNode) // Printing DB
    // CHECKED FOR MEM LEAKS
{
    LLNode* head = *menuNode->head;
    filmDB* film = NULL;
    for ( int i = 0; head->next != NULL ; i++)
    {
        film = head->object;

        printf("#%2d | %s\n",i, film->identifier);
        head = head->next;
    }
}

void pDB( TreeNode* head, int* printCount) // printing DB tool
    // CHECKED FOR MEM LEAKS
{
    if ( head != NULL )
    {
        pDB(head->left, printCount);
        int count = findLLCount(head);

        int* sizer = malloc(sizeof(int) + sizeof(filmData*)*(count+1));
        sizer[0] = count+1;

        filmData** printer = (filmData**) sizer;
        TreeNode* finder = head;


        for ( int i = 0 ; i < count+1 ; i++ )
        {
            printer[i] = finder->object;

            finder = finder->next;

            printf("#%3d | ", *printCount);
            printFilmData(printer[i]);
            (*printCount)++;
        }

        free(sizer--);

        pDB(head->right, printCount);
    }
}

/* FINDING DB AND RETURNING THEM  */
filmDB* getDB(mNode* menuNode, char* listTitle) // Collect DB
    // CHECKED FOR MEM LEAKS
{
    //puts("WE ARE HERE");

    LLNode* head = *menuNode->head;

    if ( head == NULL )
    {
        puts("FATAL ERROR: No DB in list");
        exit ( 0 );
    }

    if ( head->object == NULL )
    {
        head = head->next; //gets out of the dummy
    }

    filmDB* DB = NULL;
    int success = 0;

    //puts("About to enter getDB while");

    while ( success == 0 && head != NULL )
    {
        //puts("Looping...");

        DB = head->object;

        if ( DB!=NULL && !strcmp(DB->identifier , listTitle))
        {
            success = 1;
        }
        else
        {
            head = head->next;
        }
    }

    //puts("returning......");
    return DB;
}

filmDB* getDBbyIndex(mNode* menuNode, int index) // Collect DB by index
    // checked for mem leaks
{
    LLNode* finder = *menuNode->head;
    if ( finder != NULL )
    {
        for ( int i = 0 ; i < index ; i++ )
        {
            finder = finder->next;
        }
    }
    return finder->object;
}
filmDB* getDiary(mNode* menuNode) //Get DB Work (maybe obsolete function)
    //CHECKED FOR MEM LEAKS
{
    LLNode* head = *menuNode->head;

    if ( head == NULL )
    {
        puts("FATAL ERROR: No DB in list");
        exit ( 0 );
    }

    if ( head->object == NULL )
    {
        head = head->next; //gets out of the dummy
    }

    filmDB* DB = NULL;
    int success = 0;

    while ( success == 0 && head != NULL )
    {
        DB = head->object;

        if ( DB != NULL && !strcmp(DB->identifier , "Diary"))
        {
            success = 1;
        }
        else
        {
            head = head->next;
        }
    }

    return DB;
}

/* DATA STRUCTURE MANIPULATION  */
// this might include LL, Trees, or other stuff which isn't specific to the film structures

int findLLCount(TreeNode* head) // LL function
    // CHECKED FOR MEM LEAKS
{
    TreeNode* finder = head;
    int count = 0;

    while ( finder->next != NULL )
    {
       finder = finder->next;
       count++;
    }
    return count;
}




int removeByTitle(char* title, filmDB filmDB);

