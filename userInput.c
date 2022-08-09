#include "userInput.h"



int getChoice ()
    // does NOT need to be freed
{
    char response[100];

    fgets(response, 100, stdin);

    char exitChecker[5];
    for (int i = 0 ; i < 4 ; i++)
    {
       exitChecker[i] = response[i];
    }
    exitChecker[4] = '\0';

    if ( strcmp(exitChecker, "exit")  == 0)
    {
        puts("Goodbye!");
        return -1;
    }
    else
    {
        return strtol(response, NULL, 10);
    }
}

char* getPrompt() //REQUIRES FREEING RETURNED ITEM
{
    char* finder = malloc(sizeof(char)*300);
    fgets(finder, 300, stdin);

    for ( int i = 0 ; i < 300 ; i++ )
    {
        if ( (!isalnum(finder[i]) && finder[i] != ' ') && (!isalnum(finder[i+1]) && finder[i+1] != ' ' ) )
        {
            finder[i] = '\0';
            i = 300;
        }
    }
    return finder;
}
