// Day7_part1.cpp : 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


bool checkValid(unsigned long long &target, std::vector<int>::reverse_iterator start, std::vector<int>::reverse_iterator end);

int main()
{
    std::ifstream infile("Input.txt");
    std::string line;
    unsigned long long sum = 0;

    while (std::getline(infile, line))
    {
        //read in the first value and drop the ':' from the end. Then populate a vector with the operands
        std::stringstream ss(line);
        std::string word;
        unsigned long long result;
        ss >> word;
        word.pop_back();
        result = stoull(word);
        std::vector<int> nums;
        while (ss >> word)
        {
            nums.push_back(stoi(word));
        }

        //Check wether the value can be achieved through the given operands
        if (checkValid(result, nums.rend(), nums.rbegin()))
        {
            sum += result;
        }
    }

    std::cout << "total calibration result: " << sum << std::endl;
}

bool checkValid(unsigned long long &target, std::vector<int>::reverse_iterator start, std::vector<int>::reverse_iterator end)
{
    if (end == start)
    {
        if (target == 1)
        {
            return true;
        }
        return false;
    }
    
    
    if (target % *end == 0)
    {
        unsigned long long div = target / *end;
        if (checkValid(div, start, std::next(end, 1)))
        {
            return true;
        }
    }

    unsigned long long dif = target - *end;
    if (checkValid(dif, start, std::next(end, 1)))
    {
        return true;
    }

    return false;
}
