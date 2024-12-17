// Day13_part1.cpp : 

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

struct Button
{
    int x;
    int y;
    int cost;
};

struct Prize
{
    int x;
    int y;
};

int calcMin(Button& a, Button& b, Prize& p);

int main()
{
    std::ifstream infile("Input.txt");
    std::string line;
    Button a;
    Button b;
    Prize p;
    a.cost = 3;
    b.cost = 1;
    unsigned long long total = 0;

    while (std::getline(infile, line))
    {
        std::regex rgx("X\\+(\\d+).*Y\\+(\\d+)");
        std::smatch match;
        if (line.find("Button A:") != line.npos)
        {
            std::regex_search(line, match, rgx);
            a.x = stoi(match[1]);
            a.y = stoi(match[2]);
        }
        else if (line.find("Button B:") != line.npos)
        {
            std::regex_search(line, match, rgx);
            b.x = stoi(match[1]);
            b.y = stoi(match[2]);
        }
        else if (line.find("Prize:") != line.npos)
        {
            rgx.assign("X=(\\d+).*Y=(\\d+)");
            std::regex_search(line, match, rgx);
            p.x = stoi(match[1]);
            p.y = stoi(match[2]);

            total += calcMin(a, b, p);
        }

    }
    std::cout << "The fewest tokens to will all possible prizes is: " << total << std::endl;
}

int calcMin(Button& a, Button& b, Prize& p)
{
    int det = a.x * b.y - b.x * a.y;

    int x = ((b.y * p.x) - (b.x* p.y));
    int y = ((a.x * p.y) - (a.y * p.x));

    if (x % det == 0 && y % det == 0)
    {
        x /= det;
        y /= det;
    }
    else
    {
        return 0;
    }

    if (x <= 100 && y <= 100)
    {
        return x * a.cost + y * b.cost;
    }
    return 0;
}
