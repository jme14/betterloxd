#include "diaryReader.h"

void initNode(int tokens, filmData* node, char* fileLine)
{
    char* translator;
    char* helper;
    char storer1[MAXLENGTH];
    char storer2[MAXLENGTH];
    int interpreter;
    //printf("fileLine is %s\n", fileLine);

    if ( tokens == 7 ) //for when the title has no comma in it and the diary entry has no tags
    {
       strtok(fileLine, ","); // collects date logged

       translator = strtok(NULL, ","); // collects title
       strcpy(node->title, translator);

       translator = strtok(NULL, ","); // collects year
       interpreter = strtol(translator, NULL, 10);
       node->year = interpreter;

       strtok(NULL, ","); // collects Letterboxd URI

       translator = strtok(NULL, ","); // collects rating
       node->rating = strtod(translator, NULL);


       if ( node->rating > 5 ) //if film is UNRATED...
       {
           node->rating = 0;
           //printf("Translator HERE is %s\n", translator);
       }
       else //if film is RATED, move on to collecting rewatch info
       {
           translator = strtok(NULL, ",");
           //printf("Translator THERE is %s\n", translator);
       }

       if ( !strcmp(translator, "Yes") ) // if rewatch is listed as YES...
       {
           node->rewatch = 1;
           translator = strtok(NULL, ",");
       }
       else // designate no rewatch
       {
           node->rewatch = 0;
       }

       //strtok(NULL, ","); // collects tags ( THIS IS A GIANT CAN OF WORMS )

       helper = strtok(translator, "-");
       interpreter = strtol(helper, NULL, 10);
       node->yearWatched = interpreter;

       helper = strtok(NULL, "-");
       interpreter = strtol(helper, NULL, 10);
       node->monthWatched = interpreter;

       helper = strtok(NULL, "\n");
       interpreter = strtol(helper, NULL, 10);
       node->dateWatched = interpreter;


    }
    else if ( tokens == 8 )
    {

       strtok(fileLine, ","); // collects date logged

       helper = strtok(NULL, ","); // collects title
       translator = strtok(NULL, ","); //collects second part of title

       strcpy(storer1, helper);
       strcpy(storer2, translator);
       strcat(storer1, storer2);

       strcpy(node->title,storer1);

       helper = NULL;

       translator = strtok(NULL, ","); // collects year
       interpreter = strtol(translator, NULL, 10);
       node->year = interpreter;

       strtok(NULL, ","); // collects Letterboxd URI

       translator = strtok(NULL, ","); // collects rating
       node->rating = strtod(translator, NULL);


       if ( node->rating > 5 ) //if film is UNRATED...
       {
           node->rating = 0;
           //printf("Translator HERE is %s\n", translator);
       }
       else //if film is RATED, move on to collecting rewatch info
       {
           translator = strtok(NULL, ",");
           //printf("Translator THERE is %s\n", translator);
       }

       if ( !strcmp(translator, "Yes") ) // if rewatch is listed as YES...
       {
           node->rewatch = 1;
           translator = strtok(NULL, ",");
       }
       else // designate no rewatch
       {
           node->rewatch = 0;
       }

       //strtok(NULL, ","); // collects tags ( THIS IS A GIANT CAN OF WORMS )

       helper = strtok(translator, "-");
       interpreter = strtol(helper, NULL, 10);
       node->yearWatched = interpreter;

       helper = strtok(NULL, "-");
       interpreter = strtol(helper, NULL, 10);
       node->monthWatched = interpreter;

       helper = strtok(NULL, "\n");
       interpreter = strtol(helper, NULL, 10);
       node->dateWatched = interpreter;
    }
    //printf("node->title is %s | node->year is %d | node->rating is %f\n", node->title, node->year, node->rating);
}

filmData** fileReader(char* fileLocation)
{
    filmData** nodeArray = NULL;
    FILE* fp = fopen(fileLocation, "r");

    if ( fp == NULL )
    {
        puts("FATAL ERROR: no file found");
        exit (0);
    }
    else
    {
       // puts("fp not null!");

        int count = getFileLineCount(fp);

        /* creating filmData array to be returned */
        int* sizer = malloc((sizeof(filmData*)*count)+ sizeof(int));
        sizer[0] = count;
        sizer++;
        nodeArray = (filmData**)sizer;

        char fileLine[MAXLENGTH];

        int tokens = 0;

        for ( int i = 0 ; i < count ; i++ )
        {
            //printf("%d ", i);
            nodeArray[i] = malloc(sizeof(filmData));
            fgets(fileLine, MAXLENGTH, fp);

            //printf("fileLine is %s\n", fileLine);

            //puts("Entering commaCountTokens...");
            tokens = countCommaTokens(fileLine);

            //printf("tokens is %d\n", tokens);

            //puts("Entering initNode...");
            initNode(tokens, nodeArray[i], fileLine);
        }

    }
    return nodeArray;
}
