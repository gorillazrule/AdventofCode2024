// Day3_part2.cpp : 
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
    bool enabled = true;

    while (std::getline(infile, line))
    {
        int l;
        int r;
        std::regex rgx("(mul\\()(\\d{1,3})(,)(\\d{1,3})(\\))|(do\\(\\))|(don't\\(\\))");

        auto start = std::sregex_iterator(line.begin(), line.end(), rgx);
        auto end = std::sregex_iterator();

        for (std::sregex_iterator i = start; i != end; ++i)
        {
            std::smatch match = *i;
            //Check if it is a do, dont or mul instruction
            if (match[0] == "do()")
            {
                enabled = true;
            }
            if (match[0] == "don't()")
            {
                enabled = false;
            }
            if (match[1] == "mul(" && enabled)
            {
                l = std::stoi(match[2]);
                r = std::stoi(match[4]);
                sum += l * r;
            }           
        }
    }

    std::cout << "Sum: " << sum << std::endl;
}