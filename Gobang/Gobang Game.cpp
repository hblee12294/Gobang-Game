#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

//------VARIABLE & CONSTANT------

#define ROW 15
#define COL 15

char chessBoard[ROW + 1][COL + 1];
int whoseTurn;        // used in 'whoseTurn % 2', odd is Player1, even is Player2
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

    cout << "\n  Game over.\n";
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
                cout << setw(3) << posY;
            else if (posY == 0)
                cout << setw(3) << posX;
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

    //place chess on the chessboard
    if (whoseTurn % 2 == Player1)
    {
        cout << "\n Player1, enter the position of chess (X Y): ";

        while(cin >> cPosX >> cPosY)
        {
            if (chessBoard[cPosX][cPosY] == 0)
            {
                chessBoard[cPosX][cPosY] = Player1;
                break;
            }
            else
                cout << " The position has been taken, enter again: ";
        }
    }
    else
    {
        cout << "\n Player2, enter the position of chess (X Y): ";

        while(cin >> cPosX >> cPosY)
        {
            if (chessBoard[cPosX][cPosY] == 0)
            {
                chessBoard[cPosX][cPosY] = Player2;
                break;
            }
            else
                cout << " The position has been taken, enter again: ";
        }
    }

    //fresh screen
    system("cls");
    PrintChessBoard();

    if (Judge(cPosX, cPosY))
    {
        if (whoseTurn % 2 == Player1)
            cout << "\n  Player1 wins!\n";
        else
            cout << "\n  Player2 wins!\n";

        //winner appears, jump out of the game
        gameStatus = false;
    }

}

bool Judge(int cPosX, int cPosY)
{

    int tPosX, tPosY;                  //temp chess to check if 5 chesses are contiguous
    int sign = 2 - whoseTurn %2;       //mark player's chess, 1 -- Player1, 2--Player2


    //check vertical direction
    for (tPosX = cPosX - 4, tPosY = cPosY; tPosX < cPosX; ++tPosX)
    {
        if (tPosX >=1 &&  tPosX<= ROW - 4 &&
            chessBoard[tPosX][tPosY] == sign &&
            chessBoard[tPosX+1][tPosY] == sign &&
            chessBoard[tPosX+2][tPosY] == sign &&
            chessBoard[tPosX+3][tPosY] == sign &&
            chessBoard[tPosX+4][tPosY] == sign
            )
                return true;
    }


    //check horizontal direction
    for (tPosX = cPosX, tPosY = cPosY - 4; tPosY <= cPosY; ++tPosY)
    {
        if (tPosY >=1 && tPosY <= COL - 4 &&
            chessBoard[tPosX][tPosY] == sign &&
            chessBoard[tPosX][tPosY+1] == sign &&
            chessBoard[tPosX][tPosY+2] == sign &&
            chessBoard[tPosX][tPosY+3] == sign &&
            chessBoard[tPosX][tPosY+4] == sign
            )
                return true;
    }


    //check diagonal direction from lower left to upper right
    for (tPosX = cPosX - 4, tPosY = cPosY - 4; tPosX <= cPosX, tPosY <= cPosY; ++tPosX, ++tPosY)
    {
        if (tPosX >= 1 && tPosX <= ROW - 4 &&
            tPosY >= 1 && tPosY <= COL - 4 &&
            chessBoard[tPosX][tPosY] == sign &&
            chessBoard[tPosX+1][tPosY+1] == sign &&
            chessBoard[tPosX+2][tPosY+2] == sign &&
            chessBoard[tPosX+3][tPosY+3] == sign &&
            chessBoard[tPosX+4][tPosY+4] == sign
            )
                return true;
    }


    //check diagonal direction from lower right to upper left
    for (tPosX = cPosX + 4, tPosY = cPosY - 4; tPosX >= cPosX, tPosY <= cPosY; --tPosX, ++tPosY)
    {
        if (tPosX >= 1 && tPosX <= ROW - 4 &&
            tPosY >= 1 && tPosY <= COL - 4 &&
            chessBoard[tPosX][tPosY] == sign &&
            chessBoard[tPosX-1][tPosY+1] == sign &&
            chessBoard[tPosX-2][tPosY+2] == sign &&
            chessBoard[tPosX-3][tPosY+3] == sign &&
            chessBoard[tPosX-4][tPosY+4] == sign
            )
                return true;
    }


    //no match situations
    return false;
}
