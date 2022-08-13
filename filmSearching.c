#include "filmSearching.h"
#include "userInput.h"

void searchAll(char* listTitle, int searchType, mNode* menuNode)
{
    filmDB* DBP = getDB(menuNode, listTitle);

    if ( DBP != NULL )
    {
        filmDB DB = *DBP;

        if ( searchType == 0 ) // this is year
        {
            puts("Enter sought after year");
            int year = getChoice();

            filmData** foundFilm = findByYear(year, DB);

            if ( foundFilm != NULL )
            {
                printf("%d diary entries found...\n", getArraySize(foundFilm));

                for ( int i = 0 ; i < getArraySize(foundFilm) ; i++ )
                {
                    printFilmData(foundFilm[i]);
                }
                freeArray(foundFilm);
            }
            else
            {
                puts("Failed to find films of this year");
            }
        }

        if ( searchType == 1 ) // this is title
        {
            puts("Enter sought after film");
            char* finder = getPrompt();

            printf("Looking for film of title %s\n", finder);
            filmData** foundFilm2 = findByTitle(finder, DB);//FREED

            if ( foundFilm2 != NULL )
            {
                printf("%d entries found of that title\n", getArraySize(foundFilm2));

                /* if ( getArraySize(foundFilm2) == 0) */
                /* { */
                /*     puts("Here's a guess for what you meant..."); */
                /*     foundFilm2 = findByTitle(foundFilm2[0]->title, DB); */
                /* } */

                for ( int i = 0 ; i < getArraySize(foundFilm2) ; i++)
                {
                    printFilmData(foundFilm2[i]);
                }
                freeArray(foundFilm2);

            }
        }
        if ( searchType == 2 ) // this is rating
        {

            puts("Enter sought after film rating");
            float finder = strtof(getPrompt(), NULL);

            printf("Looking for films of rating %g\n", finder);
            filmData** foundFilm2 = findByRating(finder, DB);

            if ( foundFilm2 != NULL )
            {
                printf("%d entries found of that title\n", getArraySize(foundFilm2));

                if ( getArraySize(foundFilm2) == 0)
                {
                    puts("No films of that rating...");
                }

                for ( int i = 0 ; i < getArraySize(foundFilm2) ; i++)
                {
                    printFilmData(foundFilm2[i]);
                }
                freeArray(foundFilm2);
            }
        }
    }
    else
    {
        puts("Can't find the listed DB");
    }
}

filmData** findByTitle(char* title, filmDB filmDB) // Searching Function
    // searches the title binary tree, serves as a wrapper function
{
   filmData** finder = fBTitle(title, filmDB.titleSort);

   return finder;
}

filmData** fBTitle(char* title, TreeNode* node) // Searching Function
    // title is title, TreeNode* node is the head of the binary tree being traversed
{
    filmData** returner = NULL;

    if ( node != NULL )
    {

        filmData* finder = node->object;

        if (!strcmp(((finder->title)), title ))
        {
            int count = findLLCount(node);
            TreeNode* searcher = node;

            int * sizer = malloc(sizeof(filmData*)*(count+1)+sizeof(int));
            //printf("sizer is located at %p\n", sizer);
            sizer[0] = count+1;
            sizer++;

            returner = (filmData**)sizer;
            //puts("About to loop...");

            for ( int i = 0 ; i < count+1 ; i++ )
            {
                returner[i] = searcher->object;
                searcher = searcher->next;
            }
        }

        else
        {
            if ( strcmp(((finder->title)), title) > 0 )
            {
                returner = fBTitle(title, node->left);
            }
            else
            {
                returner = fBTitle(title, node->right);
            }
        }

        if ( returner == NULL )
        {
            /* filmData* newFind =  node->object; */
            /* int* fakeFinder = malloc(sizeof(int) + sizeof(filmData*)); */
            /* fakeFinder[0] = 0; */
            /* fakeFinder++; */

            /* returner = (filmData**) fakeFinder; */
            /* returner[0] = malloc(sizeof(filmData)); */

            /* returner[0] = newFind; */
        }

    }

    return returner;
}

filmData** findByRating(float rating, filmDB filmDB) // Searching Function
{
    TreeNode* finder = filmDB.ratingSort;

    return fBRating(rating, finder);
}

filmData** fBRating(float rating, TreeNode* node) // Searching Function
{
   filmData** returner = NULL;

   if ( node != NULL && node->object != NULL)
   {
       filmData* filmFinder = node->object;
       puts("WE HERE?");
       if ( filmFinder->rating == rating )
       {
           // FOUND
           int count = findLLCount(node);
           TreeNode* finder = node;

           int* sizer = malloc(sizeof(int) + sizeof(filmData*)*(count+1));
           sizer[0] = count+1;
           sizer++;

           returner = (filmData**) sizer;

           for ( int i = 0 ; i < count+1 ; i++ )
           {
               returner[i] = finder->object;
               finder = finder->next;
           }
       }
       else
       {
           if ( filmFinder->rating > rating  )
           {
               fBRating(rating, node->left);
           }
           else if ( filmFinder->rating < rating )
           {
               fBRating(rating, node->right);
           }
       }
   }

   return returner;
}

void printFilmData( filmData* fD ) // Printing DB tool
{
    printf("title: %-60s | year: %4d | rating: %3g | dateWatched: %2d/%2d/%4d | rewatch?: %1d\n", fD->title, fD->year, fD->rating, fD->monthWatched, fD->dateWatched, fD->yearWatched, fD->rewatch);
}

void printDatabase( filmDB DB, char* sortType ) // DB printing tool
{
    int printCount = 1;
    int* printCounter = &printCount;
    if ( !strcmp(sortType, "Title") )
    {
        pDB( DB.titleSort, printCounter );
    }
    else if ( !strcmp(sortType, "Rating") )
    {
        pDB( DB.ratingSort, printCounter );
    }
    else if ( !strcmp(sortType, "Year") )
    {
        pDB( DB.yearSort, printCounter );
    }
}

filmData** findByYear(int year, filmDB filmDB) // Searching Function
{
    TreeNode* finder = filmDB.yearSort;

    return fBYear(year, finder);
}

filmData** fBYear(int year, TreeNode* node) // Searching Function
{

    filmData** returner = NULL;

    if ( node == NULL )
    {
    }
    else
    {
        filmData* filmFinder = node->object;

        if ( filmFinder->year == year )
        {
            int count = findLLCount(node);
            TreeNode* finder = node;
            int* sizer = malloc(sizeof(int) + sizeof(filmData*)*(count+1));
            sizer[0] = count+1;
            sizer++;

            returner = (filmData**) sizer;

            for ( int i = 0 ; i < count+1 ; i++ )
            {
                returner[i] = finder->object;
                finder = finder->next;
            }
        }
        else
        {
            if ( filmFinder->year > year )
            {
                //puts("Going left!");
                returner = fBYear(year, node->left);
            }
            else
            {
                //puts("Going right!");
                returner = fBYear(year, node->right);
            }

        }
    }
    return returner;
}
