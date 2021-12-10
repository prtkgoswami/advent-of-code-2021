#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

map<char, int> _errorScoreMap{
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137}};

map<char, int> _incompleteScoreMap{
    {'(', 1},
    {'[', 2},
    {'{', 3},
    {'<', 4}};

int getErrorScore(string s)
{
    stack<char> stk;

    for (char ch : s)
    {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
            stk.push(ch);
        else if (
            ((ch == ')' || ch == ']' || ch == '}' || ch == '>') && stk.empty()) //
            || (ch == ')' && !stk.empty() && stk.top() != '(')                  //
            || (ch == ']' && !stk.empty() && stk.top() != '[')                  //
            || (ch == '}' && !stk.empty() && stk.top() != '{')                  //
            || (ch == '>' && !stk.empty() && stk.top() != '<'))
            return _errorScoreMap[ch];
        else
            stk.pop();
    }
    return 0;
}

long getCompletionScore(string s)
{
    stack<char> stk;

    for (char ch : s)
    {
        if (
            ch == '('    //
            || ch == '[' //
            || ch == '{' //
            || ch == '<')
            stk.push(ch);
        else if (
            ch == ')'    //
            || ch == ']' //
            || ch == '}' //
            || ch == '>')
            stk.pop();
    }
    long score = 0;
    while (!stk.empty())
    {
        score = score * 5 + _incompleteScoreMap[stk.top()];
        stk.pop();
    }
    return score;
}

int main()
{
    ifstream inputFile("./Day10_Input.txt");
    string input;
    vector<string> lines;
    vector<string> incompleteLines;
    while (getline(inputFile, input))
    {
        if (!input.empty() && input[input.length() - 1] == '\n')
            input.erase(input.length() - 1);
        lines.push_back(input);
    }

    // Part 1
    int errorScore = 0;
    for (string line : lines)
    {
        int score = getErrorScore(line);
        if (score == 0)
            incompleteLines.push_back(line);
        errorScore += score;
    }
    cout << "Corruption Score: " << errorScore << endl;

    // Part 2
    vector<long> completionScores;
    int middleIndex;
    for (string line : incompleteLines)
    {
        completionScores.push_back(getCompletionScore(line));
    }
    sort(completionScores.begin(), completionScores.end());
    middleIndex = completionScores.size() / 2;
    cout << "Middle Completion Score: " << completionScores[middleIndex] << endl;

    return 0;
}