#include "BST.h"
#include "../csHelpers/helpers.h"
#include "diaryReader.h"
#include "listReader.h"
#include "dirReader.h"
#include "userInput.h"
#include "filmNodeInsertion.h"
#include "menus.h"
#include "free.h"
#define SIZE 320

int main ( void  )
{
    printf("sizeof filmData is %ld", sizeof(filmData));
    mNode* menuNode = initMenu();
    menu(menuNode);
    puts("Out of menu!");
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
    yearSortHead->next = NULL;

    TreeNode* ratingSortHead = malloc(sizeof(TreeNode));

    ratingSortHead->object = NULL;
    ratingSortHead->left = NULL;
    ratingSortHead->right = NULL;
    ratingSortHead->next = NULL;

    TreeNode* titleSortHead = malloc(sizeof(TreeNode));

    titleSortHead->object = NULL;
    titleSortHead->left = NULL;
    titleSortHead->right = NULL;
    titleSortHead->next = NULL;

    filmDB.yearSort = yearSortHead;
    filmDB.ratingSort = ratingSortHead;
    filmDB.titleSort = titleSortHead;

    if ( filmDB.titleSort == NULL )
    {
        puts("Improper initialization of titleSort");
    }
    filmDB.size = malloc(sizeof(int));
    filmDB.error = 0;

    return filmDB;
}


int insertNewFilm(filmData* newFilm, filmDB filmDB) // DB initialization
    /* this function inserts new film into the BSTs of a database */
    // CHECKED FOR FREEING
{
    TreeNode* newTitleNode = malloc(sizeof(TreeNode));
    //printf("newTitleNode is %p\n", newTitleNode);
    TreeNode* newYearNode = malloc(sizeof(TreeNode));
    //printf("newYearNode is %p\n", newYearNode);
    TreeNode* newRatingNode = malloc(sizeof(TreeNode));
    //printf("newRatingNode is %p\n", newRatingNode);


    /* all different tree nodes point to the same object  */

    newTitleNode->left = NULL;
    newTitleNode->right = NULL;
    newTitleNode->next = NULL;
    newTitleNode->object = newFilm;
    //printf("newTitleNode->object is pointing to %p\n", newTitleNode->object);
    //filmData* headData = newTitleNode->object;
    //printf("the head contains the film with title %s\n", headData->title);

    newYearNode->left = NULL;
    newYearNode->right = NULL;
    newYearNode->next = NULL;
    newYearNode->object = newFilm;

    newRatingNode->left = NULL;
    newRatingNode->right = NULL;
    newRatingNode->next = NULL;
    newRatingNode->object = newFilm;

    if ( newTitleNode != NULL && /*newYearNode != NULL &&*/ newFilm != NULL) //malloc checking
    {
        filmDB.titleSort = insertNodeByTitle(filmDB.titleSort, newTitleNode, newFilm->title);

        filmDB.yearSort = insertNodeByYear(filmDB.yearSort, newYearNode, newFilm->year);

        filmDB.ratingSort = insertNodeByRating(filmDB.ratingSort, newRatingNode, newFilm->rating);


        (*filmDB.size)++; //once the new tree nodes are inserted in the corresponding trees, increment the database size
    }
    else
    {
        puts("Malloc failure or sum");
    }

    return filmDB.error;
}

LLNode* addToDatabaseList( LLNode* head, void* newObject) // DB insertion
/* This function inserts a new database into a linked list of all DBs uploaded  */
{
    if ( head == NULL )
    {
        // there is nothing at this point in the list, so make something
        LLNode* newDatabaseNode = malloc(sizeof(LLNode));
        newDatabaseNode->object = newObject;
        newDatabaseNode->next = NULL;

        head = newDatabaseNode;
    }
    else if ( head != NULL && head->object == NULL )
    {
        // this is the first case
        head->object = newObject;
        head->next = NULL;
    }
    else if ( head != NULL && head->object != NULL )
    {
        // this is the case where we need to go deeper
        head->next = addToDatabaseList(head->next, newObject);
    }
    else
    {
        puts("FATAL ERROR IN ADD TO DATABSE LIST ");
        exit(0);
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
    //puts("MEM LEAK POSSIBLE HERE");
    //filmData* currentNode = tail->object;
    //printf("head is at %p and tail is at %p with the data on the tail at %p as well as the title at %p\n", head, tail, tail->object, currentNode->title);
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
    // DEPENDENCIES
    // -- initFilmDB
    // -- fileReader
    // -- insertNewFilm
{
    filmDB diaryDB = initFilmDB(); //inits database
    strcpy(diaryDB.identifier, "Diary");

    filmData** myFilms = fileReader("./lbData/diary.csv"); //reads the diary file

    int filmCount = getArraySize(myFilms);
    printf("filmCount is %d\n", filmCount);
    for ( int i = 0 ; i < filmCount ; i++ ) //for as many films as there are, insert a new film node into the database
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
                insertNewFilm(myFilms[i], diaryDB); //new film insertion
//                printf("myFilms[%d] is stored at %p\n",i, myFilms[i]);
            }
            else
            {
                free(myFilms[i]);
            }
        }
    }
    freeArray(myFilms); // just frees the ARRAY, not the objects in the array
    return diaryDB;
}

filmDB uploadList(char* listTitle) // Creating DB work
    // CHECKED FOR FREEING
 {
    filmDB listDB = initFilmDB();
    strcpy(listDB.identifier, listTitle); //gives new list the title of the list on lb

    //printf("list title is stored at %p\n", listTitle);

    filmData** myFilms = listFileReader(listTitle);//NEEDS TO BE FREED ; reads list from data with this title
    //printf("listFileReader is %p\n", myFilms);

    int filmCount = getArraySize(myFilms);

    for ( int i = 0  ; i < filmCount ; i++ )
        // for all list entries do the following
    {
        if ( myFilms[i] == NULL )
        {
            puts("FATAL ERROR: film node empty");
            exit ( 0 );
        }
        else
        {
            if ( myFilms[i]->year != 0 ) //as long as films are valid, insert them into the list
            {
                insertNewFilm(myFilms[i], listDB);
            }
        }
    }
    freeArray(myFilms);
    return listDB;
}

int removeDB(mNode* menuNode, char* identifier)  //DB Work
    // this function returns 1 if a DB got successfully removed and 0 if no DB was removed
    // CHECKED FOR FREEING
{
    LLNode* head = menuNode->head;

    if ( head == NULL )
    {
        puts("FATAL ERROR: No DB in list");
        exit ( 0 );
    }

    filmDB* DB = NULL; // will start at first object
    int ifFound = 0;

    while ( ifFound == 0 && head != NULL )
    {
        DB = head->object;

        if ( !strcmp(DB->identifier, identifier) )
        {
            freeFilmDB(*DB);

            if ( menuNode->head == head ) // if the duplicate is in the beginning...
            {
                LLNode* headFreer = head;
                menuNode->head = head->next;
                printf("menuNode points to %p and new head points to %p\n", menuNode->head, head);
                free(headFreer);
            }
            else
            {
                LLNode* headFreer = head;
                head = head->next;
                free(headFreer);
            }

            ifFound = 1;
        }

        head = head->next;
    }

    menuNode->size--;

    return ifFound;
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

        answers = findByTitle(filmData->title, *diary);//FREED

        if ( answers != NULL ) //as long as a diary entry is found, do the following
        {
            int lastEntry = getArraySize(answers)-1;

            filmData->rating = answers[lastEntry]->rating;
            filmData->rewatch = answers[lastEntry]->rewatch;

            filmData->yearWatched = answers[lastEntry]->yearWatched;
            filmData->monthWatched = answers[lastEntry]->monthWatched;
            filmData->dateWatched = answers[lastEntry]->dateWatched;

            freeArray(answers);
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
        gDI(list->titleSort, diary);
    }
}

/* PRINTING DB  */
void printDBlist(mNode* menuNode) // Printing DB
    // CHECKED FOR MEM LEAKS
{
    LLNode* head = menuNode->head;
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

    LLNode* head = menuNode->head;

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
    LLNode* finder = menuNode->head;
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
    LLNode* head = menuNode->head;

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

