#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

int main()
{
    int R = 1000, C = 1000;
    vector<vector<int>> arr(R, vector<int>(C, 0));
    string inp;

    ifstream inputFile("./Day5_Input.txt");
    int startX = -1, startY = -1, endX = -1, endY = -1;
    while (inputFile >> inp)
    {
        if (inp != "->")
        {
            int pos = inp.find(",");
            int x = stoi(inp.substr(0, pos)), y = stoi(inp.substr(pos + 1));

            if (startX == -1 || startY == -1)
                startX = x, startY = y;
            else if (endX == -1 || endY == -1)
                endX = x, endY = y;

            if (startX != -1 && startY != -1 && endX != -1 && endY != -1)
            {
                // Vertical Line - Part 1
                if (startX == endX && startY != endY)
                {
                    int lower = min(startY, endY), higher = max(startY, endY);
                    for (int y = lower; y <= higher; y++)
                        arr[startX][y]++;
                }

                // Horizontal Line - Part 1
                else if (startY == endY && startX != endX)
                {
                    int lower = min(startX, endX), higher = max(startX, endX);
                    for (int x = lower; x <= higher; x++)
                        arr[x][startY]++;
                }

                // Diagonal Line - Part 2
                else if (abs(startX - endX) == abs(startY - endY))
                {
                    int currX = startX, currY = startY;
                    while (currX != endX && currY != endY)
                    {
                        arr[currX][currY]++;

                        if (currX < endX)
                            currX++;
                        else if (currX > endX)
                            currX--;

                        if (currY < endY)
                            currY++;
                        else if (currY > endY)
                            currY--;
                    }
                    arr[currX][currY]++;
                }
                startX = -1, startY = -1;
                endX = -1, endY = -1;
            }
        }
    }

    int count = 0;
    for (int x = 0; x < R; x++)
        for (int y = 0; y < C; y++)
            if (arr[x][y] >= 2)
                count++;

    cout << "Num of Intersections: " << count << endl;

    return 0;
}