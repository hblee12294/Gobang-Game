#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

//------VARIABLE & CONSTANT------

#define ROW 15
#define COL 15

char chessBoard[ROW + 1][COL + 1];
int whoseTurn;
bool gameStatus;

enum Player
{
    Player1 = 1,
    Player2 = 2
};

//-----------FUNCTIONS-----------

void InitGame();
void PrintChessBoard();
void PlayChess();
bool Judge(int, int);


//--------------MAIN-------------
int main()
{
    //initialize game
    InitGame();

    //player control
    while (gameStatus)
    {
        ++whoseTurn;
        PlayChess();
    }

    cout << "Game over.\n";
    return 0;
}

void InitGame()
{
    cout << "Enter 'Y' to start game, 'Q' to quit: ";

    char menu;
    if (cin >> menu && menu != 'y' && menu != 'Y')
    {
        cout << "See you ~\n";
        exit(EXIT_FAILURE);
    }

    //clear screen
    system("cls");

    //set initial status
    chessBoard[ROW+1][COL+1] = {};
    whoseTurn = 0;
    gameStatus = true;

    //print chessboard
    PrintChessBoard();
}

void PrintChessBoard()
{

    for (int posX = 0; posX <= ROW; ++posX)
    {
        for (int posY = 0; posY <= COL; ++posY)
        {
            if (posX == 0)
                cout << setw(3) << posX;
            else if (posY == 0)
                cout << setw(3) << posY;
            else if (chessBoard[posX][posY] == Player1)
                cout << setw(3) << "X";
            else if (chessBoard[posX][posY] == Player2)
                cout << setw(3) << "O";
            else
                cout << setw(3) << "*";
        }

        cout << endl;
    }
}

void PlayChess()
{
    int cPosX, cPosY;

    if (whoseTurn % 2 == Player1)
    {
        cout << "Player1, enter the position of chess (X Y): ";
        cin >> cPosX >> cPosY;
        chessBoard[cPosX][cPosY] = Player1;
    }
    else
    {
        cout << "Player2, enter the position of chess (X Y): ";
        cin >> cPosX >> cPosY;
        chessBoard[cPosX][cPosY] = Player2;
    }

    system("cls");
    PrintChessBoard();

    if (Judge(cPosX, cPosY))
    {
        if (whoseTurn % 2 == Player1)
            cout << "\nPlayer1 wins!\n";
        else
            cout << "\nPlayer2 wins!\n";

        gameStatus = false;
    }

}

bool Judge(int x, int y)
{
    int i, j;
    int t = 2 - whoseTurn %2;

    for (i = x - 4, j = y; i < x; ++i)
    {
        if (i >=1 && i <= ROW - 4 &&
            chessBoard[i][j] == t &&
            chessBoard[i+1][j] == t &&
            chessBoard[i+2][j] == t &&
            chessBoard[i+3][j] == t &&
            chessBoard[i+4][j] == t
            )
                return true;
    }


    for (i = x, j = y - 4; j <= y; ++j)
    {
        if (j >=1 && j <= COL - 4 &&
            chessBoard[i][j] == t &&
            chessBoard[i][j+1] == t &&
            chessBoard[i][j+2] == t &&
            chessBoard[i][j+3] == t &&
            chessBoard[i][j+4] == t
            )
                return true;
    }

    for (i = x - 4, j = y - 4; i <= x, j <= y; ++i, ++j)
    {
        if (i >= 1 && i <= ROW - 4 &&
            j >= 1 && j <= COL - 4 &&
            chessBoard[i][j] == t &&
            chessBoard[i+1][j+1] == t &&
            chessBoard[i+2][j+2] == t &&
            chessBoard[i+3][j+3] == t &&
            chessBoard[i+4][j+4] == t
            )
                return true;
    }

    for (i = x + 4, j = y - 4; i >= 1, j <= y; --i, ++j)
    {
        if (i >= 1 && i <= ROW - 4 &&
            j >= 1 && j <= COL - 4 &&
            chessBoard[i][j] == t &&
            chessBoard[i-1][j+1] == t &&
            chessBoard[i-2][j+2] == t &&
            chessBoard[i-3][j+3] == t &&
            chessBoard[i-4][j+4] == t
            )
                return true;
    }
}
