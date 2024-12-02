// Day2_part1.cpp :

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>


std::vector<int> getDifferences(std::vector<int>& report);
bool isSafe(std::vector<int>& differences);

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

        //Create a second vector with the differences between each level in the report.
        std::vector<int> differences;

        differences = getDifferences(report);

        //determine whether the vector is safe or unsafe, and count the occurrences
        safety = isSafe(differences);
        if (safety)
        {
            ++numSafe;
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

bool isSafe(std::vector<int>& differences)
{
    bool decrease = true;
    bool increase = true;
    bool delta = true;

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
    
    assert(!(decrease && increase));

    if ((decrease && delta) || (increase && delta))
    {
        return true;
    }
    return false;
}
