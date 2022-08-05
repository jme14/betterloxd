#include "menus.h"

mNode* initMenu()
{
    mNode* menuNode = malloc(sizeof(mNode));
    menuNode->screen = 0;
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
    filmDB* DBarray = NULL;

    if ( menuNode->screen == -1 )
    {
        puts("Bye!");
        exit ( 0 );
    }
    else if ( menuNode->screen == 0 ) //UPLOAD PROMPT
    {
        if( menuNode->size == 0 )
        {
            puts("\n\nWelcome to LB+!");
            puts("What would you like to do?\n");
        }

        printf("(You have %d items uploaded)\n\n", menuNode->size);

        puts("1: Upload Diary");
        puts("2: Upload List");
        puts("3: Upload Watchlist");

        if ( getArraySize(DBarray) > 1 )
        {
            puts("4: Compare Uploads");
        }

        menuNode->screen = getChoice();
        menu(menuNode);
    }
    else if ( menuNode->screen == 1 ) //DIARY UPLOAD PROMPT
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

        puts("5: Search Diary"); // search for year, title, tags, etc.
        puts("6: Tag Editor"); // edit tags
        puts("0: Upload Something Else");
        puts("10: Print Diary");

        menuNode->screen = getChoice();

        menu(menuNode);
    }
    else if ( menuNode->screen == 2 )
    {
        puts("Enter the number corresponding to your desired list");

        listDirectoryData lDD = getListDirectoryData("/Users/treywilliams/Local Files/My Stuff/Summer2022/CSpractice/BinaryTrees/lbData/lists/");

        printf("0 | Upload Something Else\n\n");
        printListDirectoryData(lDD);

        int listChoice = getChoice();

        if ( listChoice == 0 )
        {
            menuNode->screen = 0;
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

            puts("12: Print List");
            puts("13: Search List");
            puts("7: Upload Something Else");

            menuNode->screen = getChoice();

        menu(menuNode);
        }
    }
    else if ( menuNode->screen == 5 ) // DIARY SEARCH SCREEN
    {
        puts("\n\nWhat would you like to search for?");

        puts("8: Film year");
        puts("9: Film title");
        puts("1: I'm done searching");

        menuNode->screen = getChoice();

        menu(menuNode);
    }
    else if ( menuNode->screen == 8 ) // SEARCHING DIARY YEAR SCREEN
    {
        filmDB* diaryDBPTR = getDiary(menuNode);

        if ( diaryDBPTR == NULL )
        {
            puts("FATAL ERROR: can't find diary");
            exit ( 0 );
        }

        filmDB diaryDB = *diaryDBPTR;

        printf("Enter sought after year\n");

        int year = getChoice();

        filmData** foundFilm = findByYear(year, diaryDB);

        if ( foundFilm != NULL )
        {
            printf("%d diary entries found...\n", getArraySize(foundFilm));

            for ( int i = 0 ; i < getArraySize(foundFilm) ; i++ )
            {
                printFilmData(foundFilm[i]);
            }
        }
        else
        {
            puts("Failed to find films of this year");
        }

        menuNode->screen = 5;
        menu(menuNode);
    }

    else if ( menuNode->screen == 9 ) // SEARCHING DIARY TITLE SCREEN
    {
        filmDB* diaryDBPTR = getDiary(menuNode);

        if ( diaryDBPTR == NULL )
        {
            puts("FATAL ERROR: can't find diary");
            exit ( 0 );
        }

        filmDB diaryDB = *diaryDBPTR;

        puts("Enter sought after film");
        char* finder = getPrompt();


        printf("Looking for film of title %s\n", finder);
        filmData** foundFilm2 = findByTitle(finder, diaryDB);

        if ( foundFilm2 != NULL )
        {
            printf("%d entries found of that title\n", getArraySize(foundFilm2));

            if ( getArraySize(foundFilm2) == 0)
            {
                puts("Here's a guess for what you meant...");
                foundFilm2 = findByTitle(foundFilm2[0]->title, diaryDB);
            }

            for ( int i = 0 ; i < getArraySize(foundFilm2) ; i++)
            {
                printFilmData(foundFilm2[i]);
            }

        }

        menuNode->screen = 5;
        menu(menuNode);
    }
    else if ( menuNode->screen == 11 ) // SEARCHING DIARY RATING SCREEN
    {

        filmDB* diaryDBPTR = getDiary(menuNode);

        if ( diaryDBPTR == NULL )
        {
            puts("FATAL ERROR: can't find diary");
            exit ( 0 );
        }

        filmDB diaryDB = *diaryDBPTR;

        puts("Enter sought after film rating");
        float finder = strtof(getPrompt(), NULL);


        printf("Looking for films of rating %g\n", finder);
        filmData** foundFilm2 = findByRating(finder, diaryDB);

        if ( foundFilm2 != NULL )
        {
            printf("%d entries found of that title\n", getArraySize(foundFilm2));

            if ( getArraySize(foundFilm2) == 0)
            {
                puts("No films of that rating...");
            }

            for ( int i = 0 ; i < getArraySize(foundFilm2) ; i++)
            {
                printFilmData(foundFilm2[i]);
            }
        }
    }
    else if ( menuNode->screen == 10 )
    {
        puts("How would you like your DB printed?\n");

        printDatabase(*getDiary(menuNode), getPrompt() );

        menuNode->screen = 1;
        menu(menuNode);
    }
    else if ( menuNode->screen == 12 )
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

        menuNode->screen = 2;
        menu(menuNode);
    }

    else
    {
        puts("Invalid response");
        menuNode->screen = 0;
        menu(menuNode);
    }

    return menuNode;
}
