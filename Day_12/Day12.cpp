#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

string stringToLower(string s)
{
    string lowerS = "";
    for (char ch : s)
        lowerS += tolower(ch);
    return lowerS;
}

int countPaths(map<string, vector<string>> &adjList, string src, vector<string> path, set<string> visitedSmallCaves)
{
    if (src == "end")
        return 1;

    if (stringToLower(src) == src //
        && visitedSmallCaves.find(src) != visitedSmallCaves.end())
        return 0;

    if (stringToLower(src) == src)
        visitedSmallCaves.insert(src);

    int count = 0;
    for (string dst : adjList[src])
    {
        path.push_back(dst);
        count += countPaths(adjList, dst, path, visitedSmallCaves);
        path.pop_back();
    }
    return count;
}

int countPathsModified(map<string, vector<string>> &adjList, string src, vector<string> path,
                       set<string> visitedSmallCaves, bool visitedSmallCaveTwice)
{
    if (stringToLower(src) == src                                 //
        && visitedSmallCaves.find(src) != visitedSmallCaves.end() //
        && (src == "start" || visitedSmallCaveTwice))
        return 0;

    if (src == "end")
        return 1;

    if (src != "start" && stringToLower(src) == src //
        && visitedSmallCaves.find(src) != visitedSmallCaves.end())
        visitedSmallCaveTwice = true;

    if (stringToLower(src) == src)
        visitedSmallCaves.insert(src);

    int count = 0;
    for (string dst : adjList[src])
    {
        path.push_back(dst);
        count += countPathsModified(adjList, dst, path, visitedSmallCaves, visitedSmallCaveTwice);
        path.pop_back();
    }
    return count;
}

map<string, vector<string>> getInput()
{
    map<string, vector<string>> adjMap;
    ifstream inputFile("./Day12_Input.txt");
    string line;
    while (inputFile >> line)
    {
        int pos = line.find("-");
        string src = line.substr(0, pos),
               dst = line.substr(pos + 1);

        adjMap[src].push_back(dst);
        adjMap[dst].push_back(src);
    }
    return adjMap;
}

int main()
{
    map<string, vector<string>> adjMap;
    adjMap = getInput();

    // Part 1
    int count = countPaths(adjMap, "start", vector<string>{"start"}, set<string>());
    cout << "Number of Paths from start -> end = " << count << endl;

    // Part 2
    count = countPathsModified(adjMap, "start", vector<string>{"start"}, set<string>(), false);
    cout << "Number of Paths from start -> end visiting any 1 small cave twice = " << count << endl;

    return 0;
}