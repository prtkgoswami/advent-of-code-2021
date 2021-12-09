#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

int calculateRiskScore(vector<vector<int>> &heights)
{
    int ROW_LIM = heights.size(), COL_LIM = heights[0].size();
    int riskScore = 0; // 1 + lowPt

    for (int r = 0; r < ROW_LIM; r++)
    {
        for (int c = 0; c < COL_LIM; c++)
        {
            bool isLowPt = true;
            if ((r > 0 && heights[r - 1][c] <= heights[r][c]) ||
                (c > 0 && heights[r][c - 1] <= heights[r][c]) ||
                (r < ROW_LIM - 1 && heights[r + 1][c] <= heights[r][c]) ||
                (c < COL_LIM - 1 && heights[r][c + 1] <= heights[r][c]))
                isLowPt = false;

            if (isLowPt)
                riskScore += 1 + heights[r][c];
        }
    }

    return riskScore;
}

void getBasin(vector<vector<int>> &heights, vector<vector<bool>> &visited, int &size, int row, int col)
{
    int ROW_LIM = heights.size(), COL_LIM = heights[0].size();

    if (row < 0 || row >= ROW_LIM || col < 0 || col >= COL_LIM || heights[row][col] == 9 || visited[row][col])
        return;

    size += 1;
    visited[row][col] = true;
    getBasin(heights, visited, size, row - 1, col);
    getBasin(heights, visited, size, row + 1, col);
    getBasin(heights, visited, size, row, col - 1);
    getBasin(heights, visited, size, row, col + 1);
}

int calculateBasinSizeProduct(vector<vector<int>> &heights)
{
    int ROW_LIM = heights.size(), COL_LIM = heights[0].size();
    int product = 1;
    vector<vector<bool>> visited(ROW_LIM, vector<bool>(COL_LIM, false));
    priority_queue<int, vector<int>, greater<int>> sizes;

    for (int r = 0; r < ROW_LIM; r++)
    {
        for (int c = 0; c < COL_LIM; c++)
        {
            int size = 0;
            getBasin(heights, visited, size, r, c);
            if (size > 0)
            {
                if (sizes.size() < 3)
                    sizes.push(size);
                else if (size > sizes.top() && sizes.size() == 3)
                {
                    sizes.pop();
                    sizes.push(size);
                }
            }
        }
    }

    while (!sizes.empty())
    {
        product *= sizes.top();
        sizes.pop();
    }

    return product;
}

int main()
{
    ifstream inputFile("./Day9_Input.txt");
    string line;
    vector<vector<int>> heights;

    while (getline(inputFile, line))
    {
        vector<char> temp(line.begin(), line.end());
        vector<int> tempInts;

        for (char ch : temp)
        {
            if (ch >= '0' && ch <= '9')
                tempInts.push_back(ch - '0');
        }
        heights.push_back(tempInts);
    }

    // Part 1
    cout << "Risk Score: " << calculateRiskScore(heights) << endl;

    // Part 2
    cout << "Basin Size Product: " << calculateBasinSizeProduct(heights) << endl;

    return 0;
}