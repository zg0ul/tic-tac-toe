#include <iostream>
#include <ctime>

#ifdef _WIN32 // Check if compiling on Windows
#include <windows.h>
#else // Assuming a Linux/Unix-like environment
#include <unistd.h>
#endif

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);
void clearScreen();

int main()
{
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X';
    char computer = 'O';
    bool running = true;

    drawBoard(spaces); // a list returns a reference by default so no need to dereference it

    while (running)
    {
        playerMove(spaces, player);
        clearScreen();
        drawBoard(spaces);

        if (checkWinner(spaces, player, computer))
        {
            std::cout << "Player wins!" << std::endl;
            running = false;
            break;
        }
        else if (checkTie(spaces))
        {
            running = false;
            break;
        }

        computerMove(spaces, computer);
        clearScreen();
        drawBoard(spaces);

        if (checkWinner(spaces, player, computer))
        {
            std::cout << "Computer wins!" << std::endl;
            running = false;
            break;
        }
        else if (checkTie(spaces))
        {
            std::cout << "It's a tie!" << std::endl;
            running = false;
            break;
        }
    }
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}

void drawBoard(char *spaces)
{
    std::cout << "\n";
    std::cout << "     |     |     " << std::endl;
    std::cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << std::endl;
    std::cout << "_____|_____|_____" << std::endl;
    std::cout << "     |     |     " << std::endl;
    std::cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << std::endl;
    std::cout << "_____|_____|_____" << std::endl;
    std::cout << "     |     |     " << std::endl;
    std::cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << std::endl;
    std::cout << "     |     |     " << std::endl;
    std::cout << "\n";
}

void playerMove(char *spaces, char player)
{
    int number;
    do
    {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> number;
        number--;
        if (spaces[number] == ' ')
        {
            spaces[number] = player;
            break;
        }
    } while (!number > 0 || !number < 8);
}

void computerMove(char *spaces, char computer)
{
    int number;
    srand(time(0));

    while (true)
    {
        number = rand() % 9;
        if (spaces[number] == ' ')
        {
            spaces[number] = computer;
            break;
        }
    }
}

bool checkWinner(char *spaces, char player, char computer)
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (spaces[i] == player && spaces[i + 3] == player && spaces[i + 6] == player)
            return true;
        if (spaces[i] == computer && spaces[i + 3] == computer && spaces[i + 6] == computer)
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (spaces[i * 3] == player && spaces[i * 3 + 1] == player && spaces[i * 3 + 2] == player)
            return true;
        if (spaces[i * 3] == computer && spaces[i * 3 + 1] == computer && spaces[i * 3 + 2] == computer)
            return true;
    }

    // Check diagonals
    if (spaces[0] == player && spaces[4] == player && spaces[8] == player)
        return true;
    if (spaces[0] == computer && spaces[4] == computer && spaces[8] == computer)
        return true;
    if (spaces[2] == player && spaces[4] == player && spaces[6] == player)
        return true;
    if (spaces[2] == computer && spaces[4] == computer && spaces[6] == computer)
        return true;

    return false;
}

bool checkTie(char *spaces)
{
    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] == ' ')
        {
            return false;
        }
    }
    std::cout << "It's a tie!" << std::endl;
    return true;
}

void clearScreen()
{
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0}; // Top left corner
    DWORD count;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);

    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
#else
    system("clear"); // or use system("cls") if on a less common environment
#endif
}
