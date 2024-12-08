// Day7_part2.cpp : 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>


bool checkValid(unsigned long long target, std::vector<int> nums);

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
        if (checkValid(result, nums))
        {
            sum += result;
        }
    }

    std::cout << "total calibration result: " << sum << std::endl;
}

bool checkValid(unsigned long long target, std::vector<int> nums)
{
    auto end = nums.rbegin();
    auto start = nums.rend();
    //base case
    if (nums.size() == 1)
    {
        if (target == nums.at(0))
        {
            return true;
        }
        return false;
    }

    std::vector<int> next = nums;
    next.pop_back();

    //multiplication
    if (target % *end == 0)
    {
        unsigned long long div = target / *end;
        
        if (checkValid(div, next))
        {
            return true;
        }
    }

    //addition
    unsigned long long dif = target - *end;
    if (checkValid(dif, next))
    {
        return true;
    }

    //concatination
    //If last x digits are equal to the number at the end of the vector, drop them from target and check again
    std::string disjoint = std::to_string(*end);
    std::string targ = std::to_string(target);
    if (targ.size() > disjoint.size() && targ.substr(targ.size() - disjoint.size()) == disjoint)
    {
        std::string dis = targ.substr(0, targ.size() - disjoint.size());
        if (checkValid(std::stoull(dis), next))
        {
            return true;
        }
    }

    return false;
}
