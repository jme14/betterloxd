#include "dirReader.h"


int getDirectorySize(char* directory)
{

    DIR* dP = opendir(directory);
    struct dirent* currentFile = readdir(dP);

    int directorySize = 0;

    while ( currentFile != NULL )
    {
        if ( currentFile->d_name[0] != '.' )
        {
            directorySize++;
        }
        currentFile = readdir(dP);
    }

    closedir(dP);

    return directorySize;
}

listDirectoryData getListDirectoryData(char* directory)
{

    listDirectoryData lDD;
    lDD.listlistCount = getDirectorySize("/Users/treywilliams/Local Files/My Stuff/Summer2022/CSpractice/BinaryTrees/lbData/lists/");

    lDD.listlist = malloc(sizeof(listItems)*lDD.listlistCount);//FREED; NOT HERE

    DIR* dP = opendir(directory);
    struct dirent* currentFile = readdir(dP);

    int indexer = 1;
    lDD.listlistCount = 0;
    if ( currentFile != NULL )
    {
        strcpy(lDD.directoryTitle, directory);
        for (int i = 0;  currentFile != NULL ; i++)
        {
            if ( currentFile->d_name[0] != '.' )
            {
                strcpy(lDD.listlist[i].title, currentFile->d_name);
                lDD.listlist[i].index = indexer;
                indexer++;
                lDD.listlistCount++;
            }
            currentFile = readdir(dP);
        }

    }
    else
    {
        puts("Invalid directory name");
    }

    closedir(dP);
    return lDD;
}


char* getListFileByIndex(listDirectoryData lDD, int index)
{
    char listTitle[1000];

    strcpy(listTitle, "/Users/treywilliams/Local Files/My Stuff/Summer2022/CSpractice/BinaryTrees/lbData/lists/");

    int foundIndex = 0;
    for ( int i = 0 ; i < lDD.listlistCount ; i++ )
    {
        if ( lDD.listlist[i].index == index )
        {

            strcat(listTitle, lDD.listlist[i].title);
            foundIndex = i;
            i = lDD.listlistCount;
        }
    }

    int mallochelper = sizeof("/Users/treywilliams/Local Files/My Stuff/Summer2022/CSpractice/BinaryTrees/lbData/lists/");

    for ( int i = 0 ; lDD.listlist[foundIndex].title[i] != '\0' ; i++ )
    {
        mallochelper++;
    }


    char* listTitle1 = malloc(sizeof(char)*(mallochelper));//FREED

    listTitle1[mallochelper-1] = '\0';

    for ( int i = 0 ; i < mallochelper-1; i++ )
    {
        listTitle1[i] = listTitle[i];
        //printf("listTitle is %s\n", listTitle1);
    }


    return listTitle1;
}

void printListDirectoryData(listDirectoryData lDD)
{
    for ( int i = 0 ; i < lDD.listlistCount ; i++ )
    {
        if ( lDD.listlist[i].index != 0 )
        {

            printf("%d | %s\n", lDD.listlist[i].index, lDD.listlist[i].title);
        }
    }
}
