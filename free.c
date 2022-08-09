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
    //free(menuNode->head); //might cause a seg or something
    free(menuNode);

    menuNode = NULL;

    puts("All should be freed!");
}

// BST.c

void freeTree(TreeNode* head) // FREES DATA STRUCTURE TREENODE
{
    if ( head != NULL )
    {
        puts("Going left...");
        freeTree(head->left);
        puts("Going right...");
        freeTree(head->right);
        puts("About to start freeing!");
        if ( head != NULL )
        {
            if ( head->next != NULL )
            {
                freeTreeLL(head->next);
                free(head->object);
                free(head);
            }

        }
    }
    puts("exiting!");
}
void freeTreeLL(TreeNode* head)
{
    puts("inside freeTreeLL");
    if ( head->next != NULL )
    {
        freeTreeLL(head->next);
    }
    free(head);
}
void freeLL(LLNode* head) // FREES A LINKED LIST DATA STRUCTURE (ALL OF THE LLNode* TYPE)
{
    if ( head != NULL )
    {
        puts("In freeLL if");
        freeLL(head->next);
        free(head);
    }
}
void freeFilmDB(filmDB DB)
{
    printf("freeing filmDB titled %s\n", DB.identifier);
    freeTree(DB.yearSort);
    freeTree(DB.ratingSort);
    freeTree(DB.titleSort);
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
