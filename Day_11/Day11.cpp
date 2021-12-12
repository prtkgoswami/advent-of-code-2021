#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void flash(vector<vector<int>> &board, int row, int col, vector<vector<bool>> &flashboard, long &flashCount)
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10 || flashboard[row][col])
        return;

    board[row][col] += 1;
    if (board[row][col] > 9)
    {
        flashboard[row][col] = true;
        board[row][col] = 0;
        flashCount += 1;
        // Bottom
        flash(board, row + 1, col, flashboard, flashCount);
        // Top
        flash(board, row - 1, col, flashboard, flashCount);
        // Right
        flash(board, row, col + 1, flashboard, flashCount);
        // Left
        flash(board, row, col - 1, flashboard, flashCount);
        // Bottom - Right
        flash(board, row + 1, col + 1, flashboard, flashCount);
        // Bottom - Left
        flash(board, row + 1, col - 1, flashboard, flashCount);
        // Top - Left
        flash(board, row - 1, col + 1, flashboard, flashCount);
        // Top - Left
        flash(board, row - 1, col - 1, flashboard, flashCount);
    }
}

long simulateFlashing(vector<vector<int>> board)
{
    long flashCount = 0;
    for (int step = 1; step <= 100; step++)
    {
        long currFlashCount = 0;
        vector<vector<bool>> flashboard(10, vector<bool>(10, false));
        for (int row = 0; row < 10; row++)
            for (int col = 0; col < 10; col++)
                flash(board, row, col, flashboard, currFlashCount);

        flashCount += currFlashCount;
    }
    return flashCount;
}

int simultaneousFlashStep(vector<vector<int>> board)
{
    int step = 0;
    while (true)
    {
        step++;
        long currFlashCount = 0;
        vector<vector<bool>> flashboard(10, vector<bool>(10, false));
        for (int row = 0; row < 10; row++)
            for (int col = 0; col < 10; col++)
                flash(board, row, col, flashboard, currFlashCount);

        if (currFlashCount == 100)
            return step;
    }
    return 0;
}

vector<vector<int>> getInput()
{
    ifstream inputFile("./Day11_Input.txt");
    string line;
    vector<vector<int>> board;
    while (getline(inputFile, line))
    {
        vector<int> row;
        for (char ch : line)
            row.push_back(ch - '0');

        board.push_back(row);
    }
    return board;
}

int main()
{
    vector<vector<int>> board = getInput();

    // Part 1
    cout << "Number of Flashes in 100 Steps: " << simulateFlashing(board) << endl;

    // Part 2
    cout << "First Synchronous Flash occurs at: " << simultaneousFlashStep(board) << endl;

    return 0;
}