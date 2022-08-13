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

void freeTree(TreeNode* head)
{
    if ( head != NULL )
    {
        freeTree(head->left);
        freeTree(head->right);
        if ( head != NULL )
        {
            if ( head->next != NULL )
            {
                freeTreeLL(head->next);
                puts("outside freeTreeLL");
            }
            free(head);
        }

    }
}
void freeAndClearTree(TreeNode* head) // FREES DATA STRUCTURE TREENODE
{
    if ( head != NULL )
    {
        freeAndClearTree(head->left);
        freeAndClearTree(head->right);
        puts("Down the rabit hole");
        if ( head != NULL )
        {
            if ( head->next != NULL )
            {
                freeTreeLL(head->next);
                puts("outside freeTreeLL");
            }
            filmData* currentNode = head->object;
            printf("about to free node with title %s and location %p\n", currentNode->title, currentNode);
            if ( currentNode->title[0] != '\0' )
            {
                free(head->object);
            }
            free(head);
        }

    }
    puts("Coming up!");
}
void freeTreeLL(TreeNode* head)
{
    puts("inside freeTreeLL");
    if ( head->next != NULL )
    {
        puts("Inside freeTreeLL if statement");
        freeTreeLL(head->next);
    }
    puts("outside that statement");
    free(head);
    puts("Leaving function");
}
void freeLL(LLNode* head) // FREES A LINKED LIST DATA STRUCTURE (ALL OF THE LLNode* TYPE)
{
    if ( head != NULL && head->next != NULL )
    {
        puts("In freeLL if");
        freeLL(head->next->next);
        //free(head->object);
        free(head->next);
    }
}
void freeFilmDB(filmDB DB)
{
    printf("freeing filmDB titled %s\n", DB.identifier);

    freeAndClearTree(DB.titleSort);
    freeTree(DB.ratingSort);
    freeTree(DB.yearSort);
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
