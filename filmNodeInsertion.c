#include "filmNodeInsertion.h"

TreeNode* insertNodeByYear(TreeNode* head, TreeNode* const newFilm, int year) // DB initialization
{
    if ( head == NULL ) // this takes place when the item is found and the head isn't being established
    {
        head = newFilm;
        head->object = newFilm->object;
        head->left = NULL;
        head->right = NULL;
        head->next = NULL;

        printf("address of newFilm->object is %p\n", newFilm->object);
        //free( newFilm );
    }
    else
    {
        if ( head->object == NULL )
        {
            //head establishing
            head->object = newFilm->object;
            head->left = NULL;
            head->right = NULL;
            head->next = NULL;

            printf("address of newFilm is %p\n", newFilm->object);
            free( newFilm );
        }
        else
        {

            filmData* fD = head->object;

            if ( head->object == NULL )
            {
                puts("FATAL ERROR: no film attatched in insertByYear");
                exit(0);
            }

            //printf("fD year is %d and we are inserting %d\n", fD->year, year);

            if ( fD->year < year ) //when new film year has a GREATER value than current film
            {
                head->right = insertNodeByYear(head->right, newFilm, year);
            }

            else if ( fD->year > year )
            {
                head->left = insertNodeByYear(head->left, newFilm, year);
            }
            else if ( fD->year == year )
            {
                insertLL(head, newFilm);
                //printf("LL size now %d\n", findLLCount(head));
            }

            else
            {
                puts("FATAL FLAW: you're boned");
                exit(0);
            }

        }
    }

    return head;

}
TreeNode* insertNodeByRating(TreeNode* head, TreeNode* const newFilm, float rating) // DB initialization
{
    if ( head == NULL )
    {
        head = newFilm;

        head->left = NULL;
        head->right = NULL;
        head->next = NULL;

    }
    else
    {
        if ( head->object == NULL ) //this is only the case when the head is being established
        {
            head->object = newFilm->object;
            head->left = NULL;
            head->right = NULL;
            head->next = NULL;

            free( newFilm );
        }
        else
        {
            filmData* fD = head->object;

            if ( rating < fD->rating )
            {
                head->left = insertNodeByRating(head->left, newFilm, rating);
            }
            else if ( rating > fD->rating )
            {
                head->right = insertNodeByRating(head->right, newFilm, rating);
            }
            else if ( rating == fD->rating )
            {
                insertLL(head, newFilm);
            }
            else
            {
                puts("FATAL ERROR: magic");
                exit ( 0 );
            }
        }
    }
    return head;
}
TreeNode* insertNodeByTitle(TreeNode* head, TreeNode* newFilm, char* const title) // DB initialization
{
    /* TreeNode* head : the top of the subtree being looked at
     * TreeNode* newFilm : the next tree node to be inserted
     * char* const title : the title of the new film node object */

    if ( title == NULL )
    {
        puts("FATAL ERROR: no title given");
        exit(0);
    }

    if ( head == NULL ) // when there is NO REMAINING SUBTREE, newFilm can be inserted
    {
        //printf("found NEW data, data now at %p\n", newFilm);
        head = newFilm; //head is changed from pointing to NULL to pointing to the new tree node!
    }
    else // when head is NOT NULL
    {
        if ( head->object == NULL ) //this should only happen on the first run through
        {
            head->object = newFilm->object; //extract item from the new node
            free ( newFilm ); //free new node; all the information has been given to head
        }

        else // when NOT the head of the full tree AND not at the end of a tree
        {
            filmData* fD = head->object; //used for comparing objects

            if ( head->object == NULL ) //error checking
            {
                puts("FATAL ERROR: no film attached");
                exit(0);
            }

            if (strcmp( (fD->title), title) > 0) //title less than
            {
                head->left = insertNodeByTitle(head->left, newFilm, title);
            }
            else if (strcmp( (fD->title), title) < 0 ) //title greater than
            {
                head->right = insertNodeByTitle(head->right, newFilm, title);
            }
            else if ( strcmp( (fD->title), title ) == 0 ) //if we find an EXACT MATCH
            {
                //filmData* theFilm = newFilm->object;
                //printf("the film node is stored at %p\n", theFilm);

                insertLL(head, newFilm);
            }
            else
            {
                puts("FATAL ERROR, WHAT THE HELL IS GOING ON");
            }

        }
    }
    //puts("RISING");
    return head;
}
