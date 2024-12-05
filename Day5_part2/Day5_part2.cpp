// Day5_part2.cpp : 

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "customSort.h"
#include <cmath>

int main()
{
    std::ifstream infile("Input.txt");
    std::string line;
    std::multimap<int, int> ordering;
    std::regex rgxOrder("(\\d+)\\|(\\d+)");
    std::regex delimiter(",");
    std::smatch match;
    int num;
    int sum = 0;

    while (getline(infile, line))
    {
        std::vector<int> update;
        //If the line matches the page ordering rules, enter it into the ordering multimap
        if (std::regex_search(line, match, rgxOrder))
        {
            std::string l = match.str(1);
            std::string r = match.str(2);
            ordering.insert({ std::stoi(l), std::stoi(r) });
        }
        //If it isnt a page ordering, then it must be an update
        else
        {
            //Read through the page numbers separated by commas, and put them in a vector
            std::sregex_token_iterator it(line.begin(), line.end(), delimiter, -1);
            std::sregex_token_iterator end;
            while (it != end)
            {
                if (*it != "")
                {
                    num = std::stoi(*it);
                    update.push_back(num);
                }
                ++it;

            }
            //Copy the vector and sort it, based on the page ordering rules
            std::vector<int> copy = update;
            std::sort(copy.begin(), copy.end(), customSort(ordering));

            //Check if the sorted copy is equivalent to the update
            if (update != copy && update.size() != 0)
            {
                //find the middle page number, and add it to the sum
                sum += copy.at(std::ceil(copy.size() / 2));
            }
        }
    }
    std::cout << sum << std::endl;
}