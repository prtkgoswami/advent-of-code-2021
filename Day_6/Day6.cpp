#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

// ONLY FOR PART 1

void simulate(vector<int> &school, int days)
{
    for (int day = 1; day <= days; day++)
    {
        for (int i = 0; i < school.size(); i++)
        {
            if (school[i] > 0)
            {
                school[i]--;
            }
            else if (school[i] == 0)
            {
                school.push_back(9);
                school[i] = 6;
            }
        }

        // Print School -- DEBUG
        // cout << "Day " << day << ": ";
        // for (int i = 0; i < school.size(); i++)
        // {
        //     cout << school[i] << ",";
        // }
        // cout << endl;
    }
}

int recursiveSimulate(int population, int day, int remaining)
{
    if (day == 0)
        return population;

    if (remaining == 0)
    {
        int current = recursiveSimulate(population, day - 1, 6);
        int newChild = recursiveSimulate(population, day - 1, 8);
        return current + newChild;
    }

    return recursiveSimulate(population, day - 1, remaining - 1);
}

int main()
{
    string inp;
    vector<int> school;

    ifstream inputFile("./Day6_Input.txt");
    inputFile >> inp;

    int pos = inp.find(",");
    while (pos != string::npos)
    {
        school.push_back(stoi(inp.substr(0, pos)));
        inp.erase(0, pos + 1);
        pos = inp.find(",");
    }
    if (inp != "")
        school.push_back(stoi(inp));

    // 18 Days
    // simulate(school, 18);
    // cout << "# of fishes after 18 Days: " << school.size() << endl;

    // 80 Days
    simulate(school, 80);
    cout << "# of fishes after 80 Days: " << school.size() << endl;

    return 0;
}