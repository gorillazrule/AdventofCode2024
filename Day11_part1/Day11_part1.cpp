// Day11_part1.cpp :

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>


int main()
{
    const int blinks = 25;
    std::list<unsigned long long> rocks;
    //read in the input
    std::ifstream infile("Input.txt");
    std::string line;
    std::getline(infile, line);

    //Split the input by whitespace and add to list
    std::stringstream ss;
    ss.str(line);
    while (ss >> line)
    {
        rocks.push_back(stoi(line));
    }

    for (int i = blinks; i > 0; --i)
    {
        for (auto it = rocks.begin(); it != rocks.end(); ++it)
        {
            std::string num = std::to_string(*it);
            if (*it == 0)
            {
                *it = 1;
            }
            else if (num.length() % 2 == 0)
            {
                unsigned long long left = stoi(num.substr(0, num.length() / 2));
                unsigned long long right = stoi(num.substr(num.length() / 2));
                *it = right;
                rocks.insert(it, left);
            }
            else
            {
                *it = *it * 2024;
            }
        }
    }

    std::cout << "Number of stones after " << blinks << " blinks: " << rocks.size() << std::endl;
}
