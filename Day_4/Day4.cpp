#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

bool CheckWin(vector<vector<bool>> checkBoard)
{
    int R = checkBoard.size(), C = checkBoard[0].size();
    // Check Full Row
    for (int i = 0; i < R; i++)
    {
        bool valid = true;
        for (int j = 0; j < C; j++)
            valid = valid && checkBoard[i][j];
        if (valid)
            return true;
    }

    // Check Full Col
    for (int i = 0; i < C; i++)
    {
        bool valid = true;
        for (int j = 0; j < R; j++)
            valid = valid && checkBoard[j][i];
        if (valid)
            return true;
    }
    return false;
}

int GetUncheckedSum(vector<vector<int>> board, vector<vector<bool>> checkBoard)
{
    int R = board.size(), C = board[0].size();
    int sumUnchecked = 0;

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (!checkBoard[r][c])
                sumUnchecked += board[r][c];

    return sumUnchecked;
}

pair<int, int> PlayBingo(vector<vector<int>> board, vector<int> sequence)
{
    int R = board.size(), C = board[0].size();
    vector<vector<bool>> check(R, vector<bool>(C, false));
    int turn = 0;

    for (int num : sequence)
    {
        turn++;
        for (int r = 0; r < R; r++)
        {
            bool found = false;
            for (int c = 0; c < C; c++)
            {
                if (board[r][c] == num)
                {
                    check[r][c] = true;
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if (CheckWin(check))
        {
            int score = GetUncheckedSum(board, check) * num;
            return make_pair(turn, score);
        }
    }
    return make_pair(0, 0);
}

int main()
{
    vector<vector<int>> arr;
    vector<int> subarr;
    vector<int> seq;
    string seqInput, inp;
    int lineCount = 1, elemCount = 0, boardCount = 0;
    int minTurns = INT_MAX, minTurnScore = 0, winningBoard = 0;
    int maxTurns = 0, maxTurnScore = 0, losingBoard = 0;

    ifstream inputFile("./Day4_Input.txt");
    while (inputFile >> inp)
    {
        if (lineCount == 1)
        {
            seqInput = inp;
            int pos = seqInput.find(",");
            while (pos != string::npos)
            {
                seq.push_back(stoi(seqInput.substr(0, pos)));
                seqInput.erase(0, pos + 1);
                pos = seqInput.find(",");
            }
            if (seqInput != "")
                seq.push_back(stoi(seqInput));
        }
        else
        {
            subarr.push_back(stoi(inp));
            elemCount++;

            if (elemCount % 5 == 0)
            {
                arr.push_back(subarr);
                subarr.clear();
            }

            if (elemCount % 25 == 0)
            {
                boardCount++;
                pair<int, int> results = PlayBingo(arr, seq);
                int turns = results.first, score = results.second;
                // Part 1
                if (turns < minTurns)
                {
                    minTurns = turns;
                    minTurnScore = score;
                    winningBoard = boardCount;
                }

                // Part 2
                if (turns > maxTurns)
                {
                    maxTurns = turns;
                    maxTurnScore = score;
                    losingBoard = boardCount;
                }

                elemCount = 0;
                arr.clear();
            }
        }
        lineCount++;
    }

    // Part 1
    cout << "Board " << winningBoard << " Won in " << minTurns << " Turns with a Score of " << minTurnScore << endl;

    // Part 2
    cout << "Board " << losingBoard << " Lost in " << maxTurns << " Turns with a Score of " << maxTurnScore << endl;

    return 0;
}