#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int getDisplacementBasic(vector<pair<string, int>> arr)
{
    int hor = 0, vert = 0;

    for (auto p : arr)
    {
        if (p.first == "forward")
            hor += p.second;
        else if (p.first == "up")
            vert -= p.second;
        else if (p.first == "down")
            vert += p.second;
    }

    return hor * vert;
}

int getDisplacementAdvanced(vector<pair<string, int>> arr)
{
    int hor = 0, vert = 0, aim = 0;

    for (auto p : arr)
    {
        if (p.first == "forward")
        {
            hor += p.second;
            vert += (p.second * aim);
        }
        else if (p.first == "up")
            aim -= p.second;
        else if (p.first == "down")
            aim += p.second;
    }

    return hor * vert;
}

int main()
{
    ifstream inputFile("./Day2_Input.txt");
    string dir;
    int num;
    vector<pair<string, int>> arr;

    while (inputFile >> dir >> num)
    {
        arr.push_back(make_pair(dir, num));
    }

    // Part 1
    // int disp = getDisplacementBasic(arr);

    // Part 2
    int disp = getDisplacementAdvanced(arr);

    cout << "Displacement: " << disp << endl;

    return 0;
}