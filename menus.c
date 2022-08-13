#include "menus.h"
#include "filmSearching.h"
#include "free.h"

#define TOTALMENUS 5
mNode* initMenu()
{
    mNode* menuNode = malloc(sizeof(mNode));//NOT HERE FOR 1 LIST
    //printf("menuNode is stored %p\n", menuNode);
    strcpy(menuNode->screen, "Main Menu");
    //menuNode->head = malloc(sizeof(LLNode*));
    //printf("menuNode->head is stored %p\n", menuNode->head);
    menuNode->size = 0;

    LLNode* permaHead = malloc(sizeof(LLNode));//NOT HERE FOR 1 LIST
    //printf("permahead is stored at %p\n", permaHead);
    permaHead->next = NULL;
    permaHead->object = NULL;

    menuNode->head = &permaHead;

    return menuNode;
}

/* LIST OF POTENTIAL MENUS */
// Upload Menu ( MAIN MENU )
// Diary Editor (searching, printing, tag editor, etc)

// List Uploader
// List Menu (searching/printing lists)

mNode* menu(mNode* menuNode) // menu work
{
    //filmDB* DBarray = NULL;
    menuChoice* mChoice = NULL;

    if ( menuNode != NULL )
    {

    
        if ( strcmp(menuNode->screen, "exit") == 0 )
        {
            puts("Bye!");
        }
        else if ( strcmp(menuNode->screen, "Main Menu") == 0 ) //UPLOAD PROMPT
        {
            if( menuNode->size == 0 )
            {
                puts("\n\nWelcome to LB+!");
            }

            puts("What would you like to do?\n");
            printf("(You have %d items uploaded)\n\n", menuNode->size);


            if ( menuNode->size == 0 ) // if nothing is uploaded...
            {
                mChoice = getMenuChoiceScreen(34);
            }
            else // if something is uploaded, go to the list editing screen
            {
                mChoice = getMenuChoiceScreen(98);
            }

            menu(exitMenuSection(menuNode, mChoice, getChoice()));
        }
        else if ( strcmp(menuNode->screen, "Upload and Edit Diary") == 0) //DIARY UPLOAD PROMPT
        {
            filmDB diaryDB;

            if ( getDiary(menuNode) == NULL ) //if no diary is present
            {
                diaryDB = uploadDiary();
            }
            else
            {
                int didRemove = removeDB(menuNode, "Diary");
                if ( didRemove != 1 )
                {
                    puts("Failed to delete diary, check removeDB function");
                }
                diaryDB = uploadDiary();
            }

            insertTrueLL(*menuNode->head, &diaryDB);
            menuNode->size++;

            if ( menuNode->head == NULL )
            {
                puts ("FATAL ERROR: Failed to insert new DB");
                exit ( 0 );
            }

            puts("\n\nDiary uploaded. What now?\n");

            mChoice = getMenuChoiceScreen(29);

            menu(exitMenuSection(menuNode, mChoice, getChoice()));
        }
        else if ( strcmp(menuNode->screen, "Upload Lists") == 0)
        {
            puts("Enter the number corresponding to your desired list");

            listDirectoryData lDD = getListDirectoryData("/Users/treywilliams/Local Files/My Stuff/Summer2022/CSpractice/BinaryTrees/lbData/lists/");

            printf("0 | Upload Something Else\n\n");
            printListDirectoryData(lDD);

            int listChoice = getChoice();

            if ( listChoice == 0 )
            {

                free(lDD.listlist);
                mChoice = getMenuChoiceScreen(1);
                menu(exitMenuSection(menuNode, mChoice, 1));
            }
            else
            {
                char* listTitle = getListFileByIndex(lDD, listChoice);

                filmDB listDB;

                if ( getDB(menuNode, listTitle) == NULL )
                {
                    //puts("Inside if statement");
                    listDB = uploadList(listTitle);
                    //puts("Uploaded new list");
                    insertTrueLL(*menuNode->head, &listDB);
                    //puts("Inserted list into LL");
                    menuNode->size++;
                    //puts("Increased size");
                }

                //puts("About to get diary info");
                getDiaryInfo(menuNode, listTitle);

                free(lDD.listlist);
                free(listTitle);
                mChoice = getMenuChoiceScreen(64);
                menu(exitMenuSection(menuNode, mChoice, 1));
            }
        }
        else if ( strcmp(menuNode->screen, "List Editor Menu") == 0 )
        {
            puts("What do you want to do with your lists?");

            mChoice = getMenuChoiceScreen(385);

            menu(exitMenuSection(menuNode, mChoice, getChoice()));
        }
        else if ( strcmp(menuNode->screen, "List Searching Hub") == 0 )
        {
            puts("Enter the list to be searched");

            printDBlist(menuNode);

            int listIndex = getChoice();

            filmDB* list = getDBbyIndex(menuNode, listIndex);

            puts("\n\nWhat would you like to search for?");

            puts("1: Film year");
            puts("2: Film title");
            puts("3: Film rating");
            puts("4: Main Menu");

            int searchType = getChoice() - 1;

            if ( searchType > -1 && searchType < 3)
            {
                searchAll(list->identifier, searchType, menuNode);

                mChoice = getMenuChoiceScreen(64);

                menu(exitMenuSection(menuNode, mChoice, 1));
            }
            else if ( searchType == 3 )
            {
                mChoice = getMenuChoiceScreen(1);
                menu(exitMenuSection(menuNode, mChoice, 1));
            }

        }
        else if ( strcmp(menuNode->screen, "Diary Search") == 0 ) // DIARY SEARCH SCREEN
        {
            puts("\n\nWhat would you like to search for?");

            puts("1: Film year");
            puts("2: Film title");
            puts("3: Film rating");
            puts("4: Main Menu");

            int searchType = getChoice() - 1;

            if ( searchType > -1 && searchType < 3)
            {
                searchAll("Diary", searchType, menuNode);

                menu(menuNode);
            }
            else if ( searchType == 3 )
            {
                mChoice = getMenuChoiceScreen(1);
                menu(exitMenuSection(menuNode, mChoice, 1));
            }
            else
            {
                //puts("UNDER CONSTRUCTION");
                //exit(0);
            }
        }
        else if ( strcmp(menuNode->screen, "Diary Printer") == 0 )
        {
            puts("How would you like your diary printed?\n");

            char* printType = getPrompt();
            printDatabase(*getDiary(menuNode), printType);
            free(printType);

            mChoice = getMenuChoiceScreen(1);
            menu(exitMenuSection(menuNode, mChoice, 1));
        }
        else if ( strcmp(menuNode->screen, "List Printer")  == 0)
        {
            puts("What is the name of the list you want printed?");

            printDBlist(menuNode);

            int listName = getChoice();

            puts("How would you like your DB printed?");

            puts("Title?");
            puts("Rating?");
            puts("Year?");

            char* listName2= getPrompt();

            printDatabase(*getDBbyIndex(menuNode, listName), listName2);

            free(listName2);

            puts("\nPress enter to continue\n");
            free(getPrompt());

            mChoice = getMenuChoiceScreen(32);
            menu(exitMenuSection(menuNode, mChoice, 1));
        }
    }

    return menuNode;
}

menuChoice* getMenuChoiceScreen(long code)//REQUIRES FREEING
    // MUST BE FREED AFTER GETTING THE REQUIRED INFORMATION!!!
    // checked for mem leaks
{
    menuChoice* mChoice = NULL;
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

        int* mChoiceSetter = malloc(sizeof(menuChoice)*choiceSize+sizeof(int));
        printf("mChoiceSetter is here: %p\n", mChoiceSetter);
        mChoiceSetter[0] = choiceSize;
        mChoiceSetter++;
        mChoice = (menuChoice*) mChoiceSetter;

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
        fclose(fp);
    }
    free(menuChoiceFinder);
    return mChoice;
}

char* getmChoiceByIndex(menuChoice* mChoice, int index)
    // checked for memleaks
{
    char* newScreen = NULL;

    for ( int i = 0 ; i < getArraySize(mChoice) ; i++ )
    {
        if ( mChoice[i].index == index )
        {
            newScreen = mChoice[i].title;
        }
    }

    return newScreen;
}

mNode* exitMenuSection(mNode* menuNode, menuChoice* mChoice, int choiceIndex)
{
    if ( choiceIndex == -1 )
    {
        freeMenuChoice(mChoice);
        freeAll(menuNode);
    }
    else
    {
        strcpy(menuNode->screen, getmChoiceByIndex(mChoice, choiceIndex));
        freeMenuChoice(mChoice);
    }
    return menuNode;
}
