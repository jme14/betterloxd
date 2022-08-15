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
    // note that title is a pointer to an array of characters, which gets mallocly created
    // also note that newFilm is the newFilm NODE
    //

    //puts("FALLING");

    if ( title == NULL )
    {
        puts("FATAL ERROR: no title given");
        exit(0);
    }

    if ( head == NULL ) //this happens when the previously passed head->right or left is NULL, meaning we have reached the end of a tree!
    {
        //printf("Changing... ");
        head = newFilm;
        // newFilm should have ALLL the below attributes
        //head->object = newFilm->object;
        head->right = NULL;
        head->left = NULL;
        head->next = NULL;
        //puts("Ah, found the spot!");
        //
        //printf("head->object is stored at %p\n", head->object);

    }

    else
    {
        if ( head->object == NULL ) //this should only happen on the first run through
        {
            //printf("HEAD ESTABLISHING...");

            head->object = newFilm->object;
            head->right = NULL;
            head->left = NULL;
            head->next = NULL;
            //printf("DONE! Head is at %p\n", newFilm);
            free ( newFilm );
        }

        else //this should always happen if we have not found a node's proper place
        {
            filmData* fD = head->object; // this should only be entered when neither head->object nor head is NULL

            if ( head->object == NULL )
            {
                puts("FATAL ERROR: no film attached");
                exit(0);
            }

            //printf("Comparing with head %s\n", fD->title);
            //printf("head->left is %p\n", head->left);
            //printf("head->right is %p\n", head->right);

            if (strcmp( (fD->title), title) > 0)
            {
                //printf("-");
                //printf("Going LEFT %d\n", strcmp( (fD->title), title ));

                head->left = insertNodeByTitle(head->left, newFilm, title);

                //printf("After going in on the left with head %s\n", fD->title);
                //printf("head->left is %p\n", head->left);
                //printf("head->right is %p\n", head->right);

            }
            else if (strcmp( (fD->title), title) < 0 )
            {
                //printf("-");
                //printf("Going RIGHT %d\n", strcmp( (fD->title), title ));
                head->right = insertNodeByTitle(head->right, newFilm, title);

                //printf("After going in on the right with head %s\n", fD->title);
                //printf("head->left is %p\n", head->left);
                //printf("head->right is %p\n", head->right);

            }
            else if ( strcmp( (fD->title), title ) == 0 )
            {
                filmData* theFilm = newFilm->object;
                printf("the film is stored at %p\n", theFilm);
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
