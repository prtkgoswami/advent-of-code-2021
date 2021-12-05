#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int binaryToDecimal(int len, string bin)
{
    int decimalNum = 0;
    for (int i = 0; i < len; i++)
        decimalNum += (bin[i] - '0') * pow(2, ((len - 1) - i));
    return decimalNum;
}

int getPowerConsumption(int reportLen, vector<string> &reports)
{
    string str_gammaRate = "", str_epsilonRate = "";
    int gammaRate = 0, epsilonRate = 0;
    vector<vector<int>> frequencies(reportLen, vector<int>(2, 0));

    for (string report : reports)
        for (int i = 0; i < reportLen; i++)
            frequencies[i][report[i] - '0']++;

    for (int i = 0; i < reportLen; i++)
    {
        if (frequencies[i][0] > frequencies[i][1])
        {
            str_gammaRate += '0';
            str_epsilonRate += '1';
        }
        else
        {
            str_gammaRate += '1';
            str_epsilonRate += '0';
        }
    }

    gammaRate = binaryToDecimal(reportLen, str_gammaRate);
    epsilonRate = binaryToDecimal(reportLen, str_epsilonRate);
    return gammaRate * epsilonRate;
}

int getLifeSupportRating(int reportLen, vector<string> &reports)
{
    string str_O2GenRating = "", str_CO2ScrubRating = "";
    int O2GenRating = 0, CO2ScrubRating = 0;
    vector<bool> reportValidO2(reports.size(), true), reportValidCO2(reports.size(), true);
    int O2Count = reports.size(), CO2Count = reports.size();

    for (int i = 0; i < reportLen; i++)
    {
        if (O2Count == 1 && CO2Count == 1)
            break;

        vector<int> O2freq(2, 0), CO2freq(2, 0);
        for (int j = 0; j < reports.size(); j++)
        {
            string report = reports[j];

            if (reportValidO2[j] && O2Count > 1)
                O2freq[report[i] - '0']++;

            if (reportValidCO2[j] && CO2Count > 1)
                CO2freq[report[i] - '0']++;
        }

        char max, min;
        if (O2Count > 1)
        {
            if (O2freq[0] == 0)
                max = '1';
            else if (O2freq[1] == 0)
                max = '0';
            else
                max = (O2freq[1] >= O2freq[0]) ? '1' : '0';
        }
        if (CO2Count > 1)
        {
            if (CO2freq[0] == 0)
                min = '1';
            else if (CO2freq[1] == 0)
                min = '0';
            else
                min = (CO2freq[0] <= CO2freq[1]) ? '0' : '1';
        }
        O2freq.clear();
        CO2freq.clear();

        for (int j = 0; j < reports.size(); j++)
        {
            string report = reports[j];
            if (O2Count > 1 && reportValidO2[j] && report[i] != max)
            {
                reportValidO2[j] = false;
                O2Count--;
            }
        }
        for (int j = 0; j < reports.size(); j++)
        {
            string report = reports[j];
            if (CO2Count > 1 && reportValidCO2[j] && report[i] != min)
            {
                reportValidCO2[j] = false;
                CO2Count--;
            }
        }
    }

    for (int i = 0; i < reports.size(); i++)
    {
        if (reportValidCO2[i])
            str_CO2ScrubRating = reports[i];

        if (reportValidO2[i])
            str_O2GenRating = reports[i];
    }

    CO2ScrubRating = binaryToDecimal(reportLen, str_CO2ScrubRating);
    O2GenRating = binaryToDecimal(reportLen, str_O2GenRating);
    return O2GenRating * CO2ScrubRating;
}

int main()
{
    ifstream inputFile("./Day3_Input.txt");
    string report;
    vector<string> reports;

    while (inputFile >> report)
        reports.push_back(report);

    int inputLen = reports[0].length();

    // Part 1
    // int powerConsumption = getPowerConsumption(inputLen, reports);
    // cout << "Power Consumption: " << powerConsumption << endl;

    // Part 2
    int lifeSupportRating = getLifeSupportRating(inputLen, reports);
    cout << "Life Support Rating: " << lifeSupportRating << endl;

    return 0;
}