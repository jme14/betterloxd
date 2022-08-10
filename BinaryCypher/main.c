#include "main.h"
#include "../userInput.h"
#include "../../helpers.h"
#include "../structures.h"

#define TESTINGVAL 1002

/* int main ( void  ) */
/* { */
/*     long value = getMenuChoices(); */
/*     printf("The long val you need is %ld\n", value); */
/* } */

void readMenuText()
    // this function simply reads the list of menus in the menus.txt file
{
    FILE* fp = fopen("menus.txt", "r");

    char line[300];

    if ( fp != NULL )
    {
        while ( NULL != fgets(line, 300,fp) )
        {
            printf("%s\n", line);
        }
    }

    rewind(fp);
    fclose(fp);
}

long getMenuChoices()
    // this function collects the menus wanted by the user then returns the long value to be inserted in the menu parsing function
{
    int choice = 0;
    int storedOptions[64];
    int choiceCount = 0;

    for ( int i = 0 ; choice != -2 && i != 64 ; i++ )
    {
        readMenuText();
        puts("Enter menu to be listed");
        choice = storedOptions[i] = getChoice()-1;
        choiceCount = i;

    }

    int* choices = malloc(sizeof(int)*choiceCount+sizeof(int));//FREED
    choices[0] = choiceCount;
    choices++;

    for ( int i = 0 ; i < choiceCount ; i++ )
    {
        choices[i] = storedOptions[i];
    }

    char* binaryString = createBinaryString(choices);
    long item = returnIntegerFromBinaryString(binaryString);

    free(binaryString);
    freeArray(choices);
    return item;
}

char* createBinaryString(int* choices)//NEEDS TO BE FREED
{
    // this function collects an array of integers corresponding to the menu.txt file and creates a binary string from the answers
    int size = getArraySize(choices);

    char* binaryString = malloc(sizeof(char)*64);

    for ( int i = 0 ; i < 64 ; i++ )
    {
        binaryString[i] = (char)48;
    }

    for ( int i = 0 ; i < size ; i++ )
    {
        binaryString[choices[i]] = (char)49;
    }

    binaryString[64] = '\0';

    //printf("created binary string is %s\n", binaryString);

    return binaryString;


}

long returnIntegerFromBinaryString(char* binaryString)
    // this function takes a string and creates an integer corresponding to that string
{
    long returner = 0;
    for ( int i = 0 ; i  < 64 ; i++ )
    {
        if ( binaryString[i] == '1')
        {
            returner = returner + pow(2,i);
        }
    }
    return returner;
}



char* dTOb(long dec)//NEEDS TO BE FREED //returns a BACKWARD binary sequence based on the provided number
// THIS IS THE FUNCTION USED BY OTHER FUNCTIONS TO INTERPRET INTEGER GIVEN BY USER
{
    int tempBin[64];
    int bin[64];
    int num = 0;

    for ( int i = 0 ; i < 64 ; i++ )
    {
        num = dec%2;
        dec = dec/2;
        tempBin[i] = num;

        if ( dec == 0 )
        {
            for ( int j = 63 ; j >= 63 - i /* if i=9, this should be 63,62,61,60,59,58,57,56,55 */; j-- )
            {
                bin[j] = tempBin[63-j];
            }
            for ( int k = 0 ; k < 63 - i ; k++ )
            {
                bin[k] = 0;
            }
            i = 64;
        }
    }

    char* binInChar = malloc(sizeof(char)*65);

    for ( int i = 63 ; i != -1 ; i-- )
    {
        binInChar[i] = (48+bin[63-i]);
    }

    binInChar[64] = '\0';

    return binInChar;
}
