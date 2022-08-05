#include "listReader.h"
#include "BST.h"

#define MAXLENGTH 300
void initListNode(filmData* node, char* fileLine)
{

    char* translator;
    //int interpreter = 0;
    // CAN OF WORMS
    translator = strtok(fileLine, ","); //collects position
    //interpreter = strtol(translator, NULL, 10);
    //

    translator = strtok(NULL, ","); // collects name
    strcpy(node->title, translator);

    translator = strtok(NULL, ","); // collects year
    node->year = strtol(translator, NULL, 10);
}

filmData** listFileReader( char* fileLocation )
{
    filmData** nodeArray = NULL;

    FILE* fp = fopen(fileLocation, "r");

    while ( fp == NULL )
    {
        puts ("FATAL ERROR: no file found of that name");
        fileLocation = getPrompt();
        fp = fopen(fileLocation, "r");
    }
    if ( fp!=NULL )
    {
        int* counts = getListFileLineCount(fp);

        int* sizer = malloc((sizeof(filmData*)*counts[0]) + sizeof(int));
        sizer[0] = counts[0];
        sizer++;
        nodeArray = (filmData**) sizer;

        char fileLine[MAXLENGTH];

        //printf("get through %d lines\n", counts[1]);
        for ( int i = 0 ; i < counts[1] ; i++ )
        {
            fgets(fileLine, MAXLENGTH, fp);
        }
        for ( int i = 0 ; i < counts[0] ; i++ )
        {
            nodeArray[i] = malloc(sizeof(filmData));
            fgets(fileLine, MAXLENGTH, fp);

            initListNode(nodeArray[i], fileLine);
        }
    }
    return nodeArray;

}

int* getListFileLineCount(FILE* fp)
{
    char dummy[MAXLENGTH];
    int count = 0;
    int deleteCount = 1;

    int* twoCounts = malloc(sizeof(int)*2);

    fgets( dummy, MAXLENGTH, fp );

    while ( strcmp(dummy, "Position,Name,Year,URL,Description") != 0 && !feof(fp))
    {

        fgets(dummy, MAXLENGTH, fp);

        deleteCount++;

        dummy[34] = '\0';

    }

    while ( !feof(fp) )
    {
        fgets(dummy, MAXLENGTH, fp);
        count++;
    }
    count--;
    rewind(fp);

    twoCounts[0] = count;
    twoCounts[1] = deleteCount;

    return twoCounts;
}
