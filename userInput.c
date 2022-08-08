#include "userInput.h"



int getChoice ()
    // does NOT need to be freed
{
    char response[100];

    fgets(response, 100, stdin);

    if ( strcmp(response, "exit")  == 0)
    {
        puts("Goodbye!");
        exit(0);
    }

    return strtol(response, NULL, 10);
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
