#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int countIncrease(vector<int> arr)
{
    int count = 0,
        prev = arr[0];

    for (int num : arr)
    {
        if (num > prev)
            count++;
        prev = num;
    }

    return count;
}

int countWindowSumIncrease(vector<int> arr)
{
    int count = 0,
        prevSum = arr[0] + arr[1] + arr[2];

    for (int i = 1; i <= arr.size() - 3; i++)
    {
        int sum = arr[i] + arr[i + 1] + arr[i + 2];

        if (sum > prevSum)
            count++;

        prevSum = sum;
    }

    return count;
}

int main()
{
    ifstream inputFile("./Day1_Input.txt");
    int num;
    vector<int> arr;

    while (inputFile >> num)
        arr.push_back(num);

    // Part 1
    // int count = countIncrease(arr);

    // Part 2
    int count = countWindowSumIncrease(arr);

    cout << "Num of Increases: " << count << endl;

    return 0;
}