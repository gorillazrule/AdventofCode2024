// Day11_part2.cpp : 

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

void increment(std::map<unsigned long long, unsigned long long>& count, unsigned long long &num, unsigned long long &occurrences);

int main()
{
    const int blinks = 75;
    unsigned long long total = 0;
    std::map<unsigned long long, unsigned long long> rocks;
    //read in the input
    std::ifstream infile("Input.txt");
    std::string line;
    std::getline(infile, line);

    //Split the input by whitespace and add to list
    std::stringstream ss;
    ss.str(line);
    while (ss >> line)
    {
        rocks.emplace(stoi(line),1);
    }

    for (int i = blinks; i > 0; --i)
    {
        //create a temporary map to contain the changes after current blink
        std::map<unsigned long long, unsigned long long> next_map;
        for (auto it = rocks.begin(); it != rocks.end(); ++it)
        {
            unsigned long long num = it->first;
            unsigned long long occurrences = it->second;
            std::string str = std::to_string(num);
            if (num == 0)
            {
                unsigned long long one = 1;
                increment(next_map,one,occurrences);
            }
            else if (str.length() % 2 == 0)
            {
                unsigned long long left = stoull(str.substr(0, str.length() / 2));
                unsigned long long right = stoull(str.substr(str.length() / 2));
                increment(next_map, left, occurrences);
                increment(next_map, right, occurrences);
                
            }
            else
            {
                unsigned long long temp = num * 2024;
                increment(next_map, temp, occurrences);
            }
        }
        rocks = next_map;
    }

    for (auto rock : rocks)
    {
        total += rock.second;
    }

    std::cout << "Number of stones after " << blinks << " blinks: " << total << std::endl;
}

void increment(std::map<unsigned long long, unsigned long long>& count, unsigned long long& num, unsigned long long& occurrences)
{
    auto it = count.find(num);
    if (it == count.end())
    {
        count.insert_or_assign(num, occurrences);
    }
    else
    {
        count.insert_or_assign(num, (occurrences + it->second));
    }
}
