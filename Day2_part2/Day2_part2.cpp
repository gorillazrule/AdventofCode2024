// Day2_part2.cpp : 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>


std::vector<int> getDifferences(std::vector<int>& report);
bool isSafe(std::vector<int>& differences);
bool dampenerCheck(std::vector<int>& report);

int main()
{
    std::ifstream infile("Input.txt");
    std::string line;
    int numSafe = 0;

    //Read input one line at a time and break up into vector.
    while (std::getline(infile, line))
    {
        std::vector<int> report;
        std::stringstream ss(line);
        int level;
        bool safety = false;

        while (ss >> level)
        {
            report.push_back(level);
        }

        //determine whether the vector is safe or unsafe, and count the occurrences
        safety = isSafe(report);
        if (safety)
        {
            ++numSafe;
        }
        else
        {
            //Check if it would be safe with one of the numbers removed. 
            if (dampenerCheck(report))
            {
                ++numSafe;
            }
        }

    }


    std::cout << "safe reports:" << numSafe;
}

std::vector<int> getDifferences(std::vector<int>& report)
{
    std::vector<int> differences;
    for (int i = 0; i < report.size() - 1; ++i)
    {
        differences.push_back(report.at(i) - report.at(i + 1));
    }
    return differences;
}

bool isSafe(std::vector<int>& report)
{
    bool decrease = true;
    bool increase = true;
    bool delta = true;

    std::vector<int> differences = getDifferences(report);

    for (int i : differences)
    {
        if (i < 0)
        {
            increase = false;
        }
        if (i > 0)
        {
            decrease = false;
        }
        if (i == 0 || std::abs(i) > 3)
        {
            delta = false;
        }
    }

    assert(!(decrease && increase) || !delta);

    if ((decrease && delta) || (increase && delta))
    {
        return true;
    }
    return false;
}

bool dampenerCheck(std::vector<int>& report)
{
    bool safety = false;
    //Iterate through and remove elements one by one testing each time if it qualifies as a safe report.
    for (int i = 0; i < report.size(); ++i)
    {
        std::vector<int> dampened = report;
        dampened.erase(dampened.begin() + i);
        safety = isSafe(dampened);
        if (safety)
        {
            return true;
        }
    }
    return false;
}
