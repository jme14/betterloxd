#include "free.h"


/* this is the hub for freeing all allocated memory across the project */

void freeAll(mNode* menuNode)
{
    LLNode* DBLL = *menuNode->head;
    while ( DBLL != NULL )
    {
        filmDB* DBgetter = (filmDB*) DBLL->object;
        freeFilmDB(*DBgetter);
        DBLL = DBLL->next;
    }
    freeLL(*menuNode->head);
}

// menus.c

// BST.c

void freeTree(TreeNode* head) // FREES DATA STRUCTURE TREENODE
{
    if ( head != NULL )
    {
        freeTree(head->left);
        freeTree(head->right);
        free(head);
    }
}

void freeLL(LLNode* head) // FREES A LINKED LIST DATA STRUCTURE (ALL OF THE LLNode* TYPE)
{
    if ( head!=NULL )
    {
        freeLL(head->next);
        free(head);
    }
}
void freeFilmDB(filmDB DB)
{
    freeTree(DB.yearSort);
    freeTree(DB.ratingSort);
    freeTree(DB.titleSort);
}

// I AM AT THE EDITING DB SECTION //

// menus.c
// userInput.c
// LBreader.c
// diaryReader.c
// dirReader.c
// listReader.c
// filmSearching.c
// filmNodeInsertion.c
