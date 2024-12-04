// Day3_part1.cpp : 
//

#include <iostream>
#include <regex>
#include <fstream>
#include <string>


int main()
{
    std::ifstream infile("Input.txt");
    std::string line;
    int sum = 0;

    while (std::getline(infile, line))
    {
        int l;
        int r;
        std::regex rgx("(mul\\()(\\d{1,3})(,)(\\d{1,3})(\\))");

        auto start = std::sregex_iterator(line.begin(), line.end(), rgx);
        auto end = std::sregex_iterator();

        for (std::sregex_iterator i = start; i != end; ++i)
        {
            std::smatch match = *i;
            l = std::stoi(match[2]);
            r = std::stoi(match[4]);
            sum += l * r;
        }
    }
    
    std::cout << "Sum: " << sum << std::endl;
}