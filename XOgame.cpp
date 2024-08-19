#include <iostream>
#include <vector>
#include <limits> // For numeric_limits

using namespace std;

// Function prototypes
void printBoard(const vector<char> &board);
bool checkWin(const vector<char> &board, char player);
bool checkDraw(const vector<char> &board);
bool isValidMove(const vector<char> &board, int move);
void makeMove(vector<char> &board, int move, char player);
char playGame();

int main()
{
    char playAgain;
    do
    {
        char result = playGame();
        if (result != ' ')
        {
            cout << "Congratulations! Player " << result << " wins!\n";
        }
        else
        {
            cout << "The game is a draw.\n";
        }
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        cin.ignore(); // Ignore the newline character left by cin
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}

char playGame()
{
    vector<char> board(9, ' '); // Initialize a 3x3 Tic-Tac-Toe board
    char currentPlayer = 'X';
    int move;
    bool gameOver = false;

    while (!gameOver)
    {
        printBoard(board);
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;

        if (cin.fail() || move < 1 || move > 9 || !isValidMove(board, move - 1))
        {
            cin.clear();                                         // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid move. Please try again.\n";
            continue;
        }

        makeMove(board, move - 1, currentPlayer);

        if (checkWin(board, currentPlayer))
        {
            printBoard(board);
            return currentPlayer; // Player wins
        }
        else if (checkDraw(board))
        {
            printBoard(board);
            return ' '; // Game is a draw
        }
        else
        {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return ' '; // Default to draw if loop exits unexpectedly
}

void printBoard(const vector<char> &board)
{
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n";
    cout << "\n";
}

bool checkWin(const vector<char> &board, char player)
{
    const int winPatterns[8][3] = {
        {0, 1, 2}, // Top row
        {3, 4, 5}, // Middle row
        {6, 7, 8}, // Bottom row
        {0, 3, 6}, // Left column
        {1, 4, 7}, // Middle column
        {2, 5, 8}, // Right column
        {0, 4, 8}, // Diagonal (top-left to bottom-right)
        {2, 4, 6}  // Diagonal (top-right to bottom-left)
    };

    for (const auto &pattern : winPatterns)
    {
        if (board[pattern[0]] == player && board[pattern[1]] == player && board[pattern[2]] == player)
        {
            return true;
        }
    }

    return false;
}

bool checkDraw(const vector<char> &board)
{
    for (const auto &cell : board)
    {
        if (cell == ' ')
        {
            return false;
        }
    }
    return true;
}

bool isValidMove(const vector<char> &board, int move)
{
    return move >= 0 && move < 9 && board[move] == ' ';
}

void makeMove(vector<char> &board, int move, char player)
{
    board[move] = player;
}
