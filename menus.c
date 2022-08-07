#include "menus.h"
#include "filmSearching.h"

#define TOTALMENUS 5
mNode* initMenu()
{
    mNode* menuNode = malloc(sizeof(mNode));
    strcpy(menuNode->screen, "Main Menu");
    menuNode->head = malloc(sizeof(LLNode*));
    menuNode->size = 0;

    LLNode* permaHead = malloc(sizeof(LLNode));
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
    int choiceIndex = 0;


    printf("the difference between %s and %s is %d\n", " Upload Lists", menuNode->screen, strcmp(menuNode->screen, " Upload Lists"));
    if ( strcmp(menuNode->screen, "Exit") == 0 )
    {
        puts("Bye!");
        exit ( 0 );
    }
    else if ( strcmp(menuNode->screen, " Main Menu") == 0 ) //UPLOAD PROMPT
    {
        if( menuNode->size == 0 )
        {
            puts("\n\nWelcome to LB+!");
            puts("What would you like to do?\n");
        }

        printf("(You have %d items uploaded)\n\n", menuNode->size);

        mChoice = getMenuChoiceScreen(34);

        choiceIndex = getChoice();
        strcpy(menuNode->screen, getmChoiceByIndex(mChoice, choiceIndex));

        printf("menuNode->screen is now %s\n", menuNode->screen);
        menu(menuNode);
    }
    else if ( strcmp(menuNode->screen, " Upload and Edit Diary") == 0) //DIARY UPLOAD PROMPT
    {
        filmDB diaryDB;

        if ( getDiary(menuNode) == NULL ) //if no diary is present
        {
            diaryDB = uploadDiary();
        }
        else
        {
            removeDB(menuNode, "Diary");
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

        choiceIndex = getChoice();


        strcpy(menuNode->screen, getmChoiceByIndex(mChoice, choiceIndex));
        menu(menuNode);
    }
    else if ( strcmp(menuNode->screen, " Upload Lists") == 0)
    {
        puts("Enter the number corresponding to your desired list");

        listDirectoryData lDD = getListDirectoryData("/Users/treywilliams/Local Files/My Stuff/Summer2022/CSpractice/BinaryTrees/lbData/lists/");

        printf("0 | Upload Something Else\n\n");
        printListDirectoryData(lDD);

        int listChoice = getChoice();

        if ( listChoice == 0 )
        {
            mChoice = getMenuChoiceScreen(1);

            strcpy(menuNode->screen, getmChoiceByIndex(mChoice, 1));
            menu(menuNode);
        }
        else
        {
            char* listTitle = getListFileByIndex(lDD, listChoice);

            filmDB listDB;

            if ( getDB(menuNode, listTitle) == NULL )
            {
                puts("Inside if statement");
                listDB = uploadList(listTitle);
                puts("Uploaded new list");
                insertTrueLL(*menuNode->head, &listDB);
                puts("Inserted list into LL");
                menuNode->size++;
                puts("Increased size");
            }

            puts("About to get diary info");
            getDiaryInfo(menuNode, listTitle);

            puts("List uploaded. What now?");

            mChoice = getMenuChoiceScreen(385);

            choiceIndex = getChoice();

            strcpy(menuNode->screen, getmChoiceByIndex(mChoice, choiceIndex));
            menu(menuNode);
        }
    }
    else if ( strcmp(menuNode->screen, "Diary Search") == 0 ) // DIARY SEARCH SCREEN
    {
        puts("\n\nWhat would you like to search for?");

        puts("1: Film year");
        puts("2: Film title");
        puts("3: Film rating");
        puts("4: Main Menu");

        int searchType = getChoice();

        if ( searchType > 0 && searchType < 4 )
        {
            searchAll("Diary", searchType, menuNode);
        }
        else if ( searchType == 4 )
        {
            mChoice = getMenuChoiceScreen(1);
            strcpy(menuNode->screen, getmChoiceByIndex(mChoice, choiceIndex));
        }
        else
        {
            puts("UNDER CONSTRUCTION");
            exit(0);
        }
    }
    /* else if ( menuNode->screen == 8 ) // SEARCHING DIARY YEAR SCREEN */
    /* { */
    /*     filmDB* diaryDBPTR = getDiary(menuNode); */

    /*     if ( diaryDBPTR == NULL ) */
    /*     { */
    /*         puts("FATAL ERROR: can't find diary"); */
    /*         exit ( 0 ); */
    /*     } */

    /*     filmDB diaryDB = *diaryDBPTR; */

    /*     printf("Enter sought after year\n"); */

    /*     int year = getChoice(); */

    /*     filmData** foundFilm = findByYear(year, diaryDB); */

    /*     if ( foundFilm != NULL ) */
    /*     { */
    /*         printf("%d diary entries found...\n", getArraySize(foundFilm)); */

    /*         for ( int i = 0 ; i < getArraySize(foundFilm) ; i++ ) */
    /*         { */
    /*             printFilmData(foundFilm[i]); */
    /*         } */
    /*     } */
    /*     else */
    /*     { */
    /*         puts("Failed to find films of this year"); */
    /*     } */

    /*     menuNode->screen = 5; */
    /*     menu(menuNode); */
    /* } */

    /* else if ( menuNode->screen == 9 ) // SEARCHING DIARY TITLE SCREEN */
    /* { */
    /*     filmDB* diaryDBPTR = getDiary(menuNode); */

    /*     if ( diaryDBPTR == NULL ) */
    /*     { */
    /*         puts("FATAL ERROR: can't find diary"); */
    /*         exit ( 0 ); */
    /*     } */

    /*     filmDB diaryDB = *diaryDBPTR; */

    /*     puts("Enter sought after film"); */
    /*     char* finder = getPrompt(); */


    /*     printf("Looking for film of title %s\n", finder); */
    /*     filmData** foundFilm2 = findByTitle(finder, diaryDB); */

    /*     if ( foundFilm2 != NULL ) */
    /*     { */
    /*         printf("%d entries found of that title\n", getArraySize(foundFilm2)); */

    /*         if ( getArraySize(foundFilm2) == 0) */
    /*         { */
    /*             puts("Here's a guess for what you meant..."); */
    /*             foundFilm2 = findByTitle(foundFilm2[0]->title, diaryDB); */
    /*         } */

    /*         for ( int i = 0 ; i < getArraySize(foundFilm2) ; i++) */
    /*         { */
    /*             printFilmData(foundFilm2[i]); */
    /*         } */

    /*     } */

    /*     menuNode->screen = 5; */
    /*     menu(menuNode); */
    /* } */
    /* else if ( menuNode->screen == 11 ) // SEARCHING DIARY RATING SCREEN */
    /* { */

    /*     filmDB* diaryDBPTR = getDiary(menuNode); */

    /*     if ( diaryDBPTR == NULL ) */
    /*     { */
    /*         puts("FATAL ERROR: can't find diary"); */
    /*         exit ( 0 ); */
    /*     } */

    /*     filmDB diaryDB = *diaryDBPTR; */

    /*     puts("Enter sought after film rating"); */
    /*     float finder = strtof(getPrompt(), NULL); */


    /*     printf("Looking for films of rating %g\n", finder); */
    /*     filmData** foundFilm2 = findByRating(finder, diaryDB); */

    /*     if ( foundFilm2 != NULL ) */
    /*     { */
    /*         printf("%d entries found of that title\n", getArraySize(foundFilm2)); */

    /*         if ( getArraySize(foundFilm2) == 0) */
    /*         { */
    /*             puts("No films of that rating..."); */
    /*         } */

    /*         for ( int i = 0 ; i < getArraySize(foundFilm2) ; i++) */
    /*         { */
    /*             printFilmData(foundFilm2[i]); */
    /*         } */
    /*     } */
    /* } */
    else if ( strcmp(menuNode->screen, "Diary Printer") == 0 )
    {
        puts("How would you like your diary printed?\n");

        printDatabase(*getDiary(menuNode), getPrompt() );

        mChoice = getMenuChoiceScreen(1);

        strcpy(menuNode->screen, getmChoiceByIndex(mChoice, 1));

        menu(menuNode);
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


        puts("\nPress enter to continue\n");
        getPrompt();

        mChoice = getMenuChoiceScreen(32);

        strcpy(menuNode->screen, getmChoiceByIndex(mChoice, 1));
        menu(menuNode);
    }

    else
    {
        puts("Invalid response");
        mChoice = getMenuChoiceScreen(1);

        strcpy(menuNode->screen, getmChoiceByIndex(mChoice, 1));
        menu(menuNode);
    }

    return menuNode;
}

menuChoice* getMenuChoiceScreen(long code)
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

    }
    return mChoice;
}

char* getmChoiceByIndex(menuChoice* mChoice, int index)
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
