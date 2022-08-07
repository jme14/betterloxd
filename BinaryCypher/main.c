#include "main.h"
#include "../userInput.h"
#include "../../helpers.h"

#define TESTINGVAL 1002


typedef struct mchoice
{
    int index;
    int code;
    char title[50];
} menuChoice;

int main ( void  )
{
    printLimitedMenuChoice(getMenuChoices());
}

void readMenuText()
    // this function simply reads the list of menus in the menus.txt file
{
    FILE* fp = fopen("./BinaryCypher/menus.txt", "r");

    char line[300];

    if ( fp != NULL )
    {
        while ( NULL != fgets(line, 300,fp) )
        {
            printf("%s\n", line);
        }
    }

    rewind(fp);
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

    int* choices = malloc(sizeof(int)*choiceCount+sizeof(int));
    choices[0] = choiceCount;
    choices++;

    for ( int i = 0 ; i < choiceCount ; i++ )
    {
        choices[i] = storedOptions[i];
    }

    long item = returnIntegerFromBinaryString(createBinaryString(choices));
    return item;
}

char* createBinaryString(int* choices)
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


void printLimitedMenuChoice(long code)
{

    char* menuChoiceFinder = dTOb(code);

    FILE* fp = fopen("./BinaryCypher/menus.txt", "r");

    int choiceSize = 0;
    int fileSize = 0;
    char line[300];

    if ( fp == NULL )
    {
        puts("FATAL ERROR: can't read file");
    }
    else
    {


        //printf("menuChoiceFinder is %s\n", menuChoiceFinder);
        for ( int i = 0 ; !feof(fp) ; i++ )
        {

            fgets(line, 300, fp);

            if ( menuChoiceFinder[i] == '1' )
            {
            choiceSize++;
            }

            fileSize++;
        }

        rewind(fp);

        menuChoice* mChoice = malloc(sizeof(menuChoice)*choiceSize);
        int mChoiceIndex = 0;

        char* titleTemp;

        for ( int i = 0 ; i < fileSize ; i++ )
        {
            fgets(line, 300, fp);
            if ( menuChoiceFinder[i] == '1' )
            {
                mChoice[mChoiceIndex].code = strtol(line, NULL, 10);
                titleTemp = strtok(line, ".");
                titleTemp = strtok(NULL, "\n");

                strcpy(mChoice[mChoiceIndex].title, titleTemp);

                mChoice[mChoiceIndex].index = mChoiceIndex+1;

                mChoiceIndex++;
            }
        }

        for ( int i = 0 ; i < choiceSize ; i++ )
        {
            printf("%d. %s\n", mChoice[i].index, mChoice[i].title);
        }

    }

}

char* dTOb(long dec) //returns a BACKWARD binary sequence based on the provided number
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
