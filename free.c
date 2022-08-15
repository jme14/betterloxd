#include "free.h"


/* this is the hub for freeing all allocated memory across the project */

void freeAll(mNode* menuNode)
{
    puts("About to free...");
    LLNode* DBLL = *menuNode->head;

    while ( DBLL->next != NULL )
    {
        puts("In while...");
        filmDB* DBgetter = (filmDB*) DBLL->object;
        freeFilmDB(*DBgetter);
        DBLL = DBLL->next;
    }
    puts("Out of while!");

    freeLL(*menuNode->head);

    // THE LAST PART OF THIS FUNCTION (freeing the menuNode itself)
    puts("Freeing menu node now");
    if ( menuNode->head != NULL )
    {
        free(*menuNode->head);
    }
    free(menuNode);

    menuNode = NULL;

    puts("All should be freed!");
}

// BST.c
int checkAKTN(TreeNode* head, addKeep aK) // this returns 1 if mem has been freed and 0 if it has not
{
    int bool = 0;

    for ( int i = 0 ; i < *aK.size ; i++ )
    {
        //printf("HAVE %p STORED\n", aK.addressArray[i]);
        if ( aK.addressArray[i] == head )
        {
            bool = 1;
        }
    }

    if ( bool == 0 )
    {
        printf("NEED %p FREED\n", head);
        addTNadd(head, aK);
    }

    return bool;
}

int checkAKFD(filmData* film, addKeep aK) // this returns 1 if mem has been freed and 0 if it has not
{
    int bool = 0;

    for ( int i = 0 ; i < *aK.FDsize ; i++ )
    {

        //printf("HAVE %p STORED\n", aK.FDaddressArray[i]);
        if ( aK.FDaddressArray[i] == film)
        {
            printf("Matches with %p\n", film);
            bool = 1;
        }
    }

    if ( bool == 0 )
    {
        printf("NEED %p FREED\n", film);
        addFDadd(film, aK);
    }

    return bool;
}

void addTNadd(TreeNode* head, addKeep aK)
{
    aK.addressArray[*aK.size] = head;
    (*aK.size)++;
    printf("TN size is now %d\n", *aK.size);
}
void addFDadd(filmData* film, addKeep aK)
{
    aK.FDaddressArray[*aK.FDsize] = film;
    (*aK.FDsize)++;
    printf("FD size is now %d\n", *aK.FDsize);
}

void freeTree(TreeNode* head, addKeep aK)
{
    if ( head != NULL )
    {
        freeTree(head->left, aK);
        freeTree(head->right, aK);

        if ( head != NULL )
        {
            if ( head->next != NULL )
            {
                freeTreeLL(head->next, aK);
               // puts("outside freeTreeLL");
            }

            if ( !checkAKTN(head, aK) )
            {
                free(head);
                head = NULL;
            }
        }

    }
}
void freeAndClearTree(TreeNode* head, addKeep aK) // FREES DATA STRUCTURE TREENODE
{
    if ( head != NULL  )
    {
        printf("Observing %p\n", head);
        if ( head->object != NULL )
        {
            printf("Observing %p\n", head->object);
        }
    }

    if ( head != NULL )
    {
        freeAndClearTree(head->left, aK);
        freeAndClearTree(head->right, aK);
        //puts("Down the rabit hole");

        if ( head != NULL )
        {
            if ( head->next != NULL )
            {
                printf("About to attempt to free data at %p\n", head->next->object);
                freeTreeLL(head->next, aK);
                //puts("outside freeTreeLL");
            }
            filmData* currentNode = head->object;
            printf("about to free filmnode with title %s (of location %p) and location %p\n", currentNode->title, currentNode->title, currentNode);
            printf("also about to attempt to free treenode %p\n", head);

            if ( !checkAKFD(head->object, aK))
            {
                free(head->object);
                head->object = NULL;
            }
            if ( !checkAKTN(head, aK) )
            {
                printf("about to free %p\n", head);
                free(head);
                head->object = NULL;
            }
        }

    }
    //puts("Coming up!");
}
void freeTreeLL(TreeNode* head, addKeep aK)
{
    //puts("inside freeTreeLL");
    if ( head!= NULL && head->next != NULL )
    {
        freeTreeLL(head->next, aK);
    }
    if ( head->object != NULL )
    {
        filmData* currentNode = head->object;
        printf("About to attempt to free %p with title %s (which has address %p)\n", head->object, currentNode->title, currentNode->title);

        if ( !checkAKFD(head->object, aK) )
        {
            free(head->object);
            head->object = NULL;
        }

        head->object = NULL;
    }
    if ( !checkAKTN(head->object, aK) )
    {
        free(head);
        head = NULL;
    }
}

void freeLL(LLNode* head) // FREES A LINKED LIST DATA STRUCTURE (ALL OF THE LLNode* TYPE)
{
    if ( head != NULL && head->next != NULL )
    {
        printf("attempting to free what is at %p\n", head);
        freeLL(head->next->next);
        //free(head->object);
        free(head->next);
        head->next = NULL;
    }
}
void freeFilmDB(filmDB DB)
{
    printf("freeing filmDB titled %s with size %d\n", DB.identifier, *DB.size);

    addKeep addressKeeper;

    printf("size of address keeper is %ld\n", sizeof(addressKeeper));

    addressKeeper.addressArray = malloc(sizeof(TreeNode*)**DB.size*3);
    addressKeeper.FDaddressArray = malloc(sizeof(filmData*)**DB.size);
    addressKeeper.size = malloc(sizeof(int));
    addressKeeper.FDsize = malloc(sizeof(int));

    *addressKeeper.size = 0;
    *addressKeeper.FDsize = 0;
    printf("I HAVE NOT FREED %p OR %p OR %p OR %p\n", addressKeeper.addressArray, addressKeeper.FDaddressArray, addressKeeper.size, addressKeeper.FDsize);

    freeAndClearTree(DB.titleSort, addressKeeper);
    freeAndClearTree(DB.ratingSort, addressKeeper);
    freeAndClearTree(DB.yearSort, addressKeeper);

    free(DB.yearSort);
    free(DB.ratingSort);
    free(DB.titleSort);

    free(addressKeeper.addressArray);
    free(addressKeeper.FDaddressArray);
    free(addressKeeper.size);
    free(addressKeeper.FDsize);

    free(DB.size);
}

// menus.c -- CHECKED
void freeMenuChoice(menuChoice* mChoice)
{
    freeArray(mChoice);
}

// userInput.c -- CHECKED
// LBreader.c -- CHECKED
// diaryReader.c -- MAKE SURE UPLOAD DIARY ( FILE READER ) IS GETTING FREED
// dirReader.c
// listReader.c
// filmSearching.c
// filmNodeInsertion.c
