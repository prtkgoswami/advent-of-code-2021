#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

// Part 1
pair<int, int> getAlignmentPosition(vector<int> &currentPos, int maxPos)
{
    int minCost = INT_MAX, alignPos;

    for (int pos = 0; pos <= maxPos; pos++)
    {
        int cost = 0;
        for (int currPos : currentPos)
            cost += abs(currPos - pos);

        if (cost < minCost)
        {
            minCost = cost;
            alignPos = pos;
        }
    }
    return make_pair(alignPos, minCost);
}

// Part 2
pair<int, int> getAlternateAlignmentPosition(vector<int> &currentPos, int maxPos)
{
    int minCost = INT_MAX, alignPos;

    for (int pos = 0; pos <= maxPos; pos++)
    {
        int cost = 0;
        for (int currPos : currentPos)
        {
            int diff = abs(currPos - pos);
            cost += (diff * (diff + 1)) / 2;
        }
        if (cost < minCost)
        {
            minCost = cost;
            alignPos = pos;
        }
    }
    return make_pair(alignPos, minCost);
}

int main()
{
    ifstream inputFile("./Day7_Input.txt");
    string input;
    inputFile >> input;

    vector<int> horizontalPositions;
    int maxPos = INT_MIN;
    int pos = input.find(",");
    while (pos != string::npos)
    {
        int hpos = stoi(input.substr(0, pos));
        maxPos = max(maxPos, hpos);

        horizontalPositions.push_back(hpos);
        input.erase(0, pos + 1);
        pos = input.find(",");
    }
    if (input != "")
        horizontalPositions.push_back(stoi(input));

    // Part 1
    pair<int, int> stat = getAlignmentPosition(horizontalPositions, maxPos);
    cout << "1. Align Crabs at position " << stat.first << " with total Fuel Cost " << stat.second << endl;

    // Part 2
    stat = getAlternateAlignmentPosition(horizontalPositions, maxPos);
    cout << "2. Align Crabs at position " << stat.first << " with total Fuel Cost " << stat.second << endl;

    return 0;
}