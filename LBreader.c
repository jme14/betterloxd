#include "LBreader.h"



int getFileLineCount(FILE* fp)
{
    //puts("Entered getFileLineCount!");
    char dummy[MAXLENGTH];
    int count;
    for ( count = 0 ; !feof(fp) ; count++ )
    {
        fgets(dummy, MAXLENGTH, fp );
    }
    count--;
    rewind(fp);

    fgets(dummy, MAXLENGTH, fp); //this skips the top line again

    //puts("Returning!");
    //
    return count;
}

int countCommaTokens(char* fileLine)
{
    int count = 0;
    for ( int i = 0 ; fileLine[i] != '\0' ; i++ )
    {
        if ( fileLine[i] == ',' )
        {
            count++;
        }
    }
    return count;
}
