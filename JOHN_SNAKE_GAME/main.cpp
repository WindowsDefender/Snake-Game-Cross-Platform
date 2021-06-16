

#include "cdT.h"
#include "Snake.h"

int gamecount = 0;

void clrScreen(int stuff)
{
    printf("Press q to quit\n");
    for (int i = 0; i < stuff; i++)
    {
        printf("\n");
    }
    printf("\r");
}

void printgamename()
{
    printf("           OOOOOOOO0  O       O  OOOOOOOOO\n\r");
    printf("               O      O       O  O        \n\r");
    printf("               O      OOOOOOOOO  OOOOOOOOO\n\r");
    printf("               O      O       O  O        \n\r");
    printf("               O      O       O  OOOOOOOOO\n\r");
    printf("\n\r");
    printf("     OOOOOOOO  OO    O      O      O   O  OOOOOOO\n\r");
    printf("     O         O O   O     O O     O  O   O      \n\r");
    printf("     OOOOOOOO  O  O  O    O   O    O O    OOOOOOO\n\r");
    printf("            O  O   O O   O     O   O  O   O      \n\r");
    printf("     OOOOOOOO  O    OO  O       O  O   O  OOOOOOO\n\r");
    printf("\n\r\n\r");
    printf("********************* By John Jung *********************\n\r");
    printf("\n\r\n\r\n\r\n\r");
}

stateT controlsMenu()
{
    printf("************** Controls **************\n\r");
    printf("             UP:     w\n\r");
    printf("             DOWN:   s\n\r");
    printf("             LEFT:   a\n\r");
    printf("             RIGHT:  d\n\r");
    printf("             PAUSE:  p\n\r");
    printf("\n\r\n\r");
    printf("       Press 1 to return to menu\n\r");
    char input;
    input = _getch();
    while (true)
    {
        switch (input)
        {
        case '1':
            return start;
        default:
            input = _getch();
            break;
        }
    }
}

stateT initGame()
{
    system("cls");
    printgamename();
    printf("********************** Main Menu ***********************\n\r");
    printf("       START GAME        QUIT           CONTROLS\n\r");
    printf("         Press 1        Press 2          Press 3\n\r");
    char input;
    input = _getch();
    while (true)
    {
        switch (input)
        {
        case '1':
            return pregame;
        case '2':
            return end;
        case '3':
            return controls;
        default:
            input = _getch();
            break;
        }
    }
}

stateT initPauseScreen()
{
    printf("********************* Pause Menu *********************\n\r");
    printf("    CONTINUE           QUIT         RETURN TO MENU\n\r");
    printf("     Press 1          Press 2           Press 3\n\r");

    char input;
    input = _getch();
    while (true)
    {
        switch (input)
        {
        case '1':
            return ingame;
        case '2':
            return end;
        case '3':
            return start;
        default:
            input = _getch();
            break;
        }
    }
}

int main(void)
{
    stateT gamestate = start;
    long int x = 500;
    Snake* snek = new Snake(8);
    std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed;
    std::chrono::duration<double> comp = (std::chrono::duration<double>) 0.2;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);

    while (true)
    {
        switch (gamestate)
        {
            case start:
            {
                if (gamecount > 0) snek = new Snake(8);
                comp = (std::chrono::duration<double>) 0.2;
                gamestate = initGame();
                system("cls");
                gamecount = 1;
                break;
            }

            case controls:
            {
                gamestate = controlsMenu();
                break;
            }

            case pregame:
            {
                snek->testprint();
                snek->createApple();
                snek->print();
                gamestate = ingame;
                break;
            }
            case ingame:
            {
                while (!snek->CollidedIntoWall())
                {
                    nowTime = std::chrono::steady_clock::now();
                    elapsed = nowTime - previousTime;
                    char input;

                    if (_kbhit())
                    {
                        directionT dir = right;
                        input = _getch();

                        switch (input)
                        {
                        case 'w':
                            dir = up;
                            break;
                        case 'a':
                            dir = left;
                            break;
                        case 's':
                            dir = down;
                            break;
                        case 'd':
                            dir = right;
                            break;
                        case 'p':
                        {
                            gamestate = stopped;
                            break;
                        }
                        }
                        //if the user chooses to end the game, then exit the while loop
                        if (gamestate == end || gamestate == stopped) break;
                        snek->changeDirection(dir);
                    }
                    if (elapsed >= comp)
                    {
                        snek->move();
                        snek->print();
                        if (snek->AteApple())
                        {
                            snek->grow();
                            snek->createApple();
                            if (comp > (std::chrono::duration<double>)0.1)
                                comp = (std::chrono::duration<double>) (comp * 0.9);
                        }
                        snek->gotoxy(0, 30);
                        printf("\n\r");
                        printf("head   %d    %d\n\r", snek->head.x, snek->head.y);
                        printf("apple  %d    %d\n\r", snek->apple.x, snek->apple.y);
                        printf("length %d\n\r", (int)snek->snake_body_vector->size());
                        previousTime = nowTime;
                    }
                }
                if (gamestate != end && gamestate != stopped)
                {
                    clrScreen(120);
                    printf("Snake died\n\r");
                    printf("Score: %d\n\r", snek->getScore());
                    gamestate = start;
                }
                break;
            }

            case stopped:
            {
                snek->gotoxy(0, 34);
                gamestate = initPauseScreen();
                snek->gotoxy(0, 34);
                printf("                                                      \n\r");
                printf("                                                  \n\r");
                printf("                                               \n\r");
                break;
            }
            case end:
            {
                printf("Ended\n\r");
                printf("Score: %d\n\r", snek->getScore());
                return 0;
            }
        }
    }
    printf("Game Error: Halt\n\r");
    return 1;
}