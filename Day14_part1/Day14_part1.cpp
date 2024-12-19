// Day14_part1.cpp : 

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

struct Robot
{
    int xStart;
    int yStart;
    int xPos;
    int yPos;
    int xVel;
    int yVel;
};

const int rows = 103;
const int cols = 101;
const bool debug = false;

void simulate(std::vector<Robot>& bots, int cycles);
unsigned long long calcSafety(std::vector<Robot>& bots);

int main()
{
    
    std::ifstream infile("Input.txt");
    std::string line;
    std::regex rgx("p=(\\d+),(\\d+).*v=(-?\\d+),(-?\\d+)");
    std::smatch match;
    std::vector<Robot> bots;

    const int cycles = 100;

    while (std::getline(infile, line))
    {
        std::regex_search(line, match, rgx);
        Robot tempBot;
        tempBot.xPos = std::stoi(match[1]);
        tempBot.yPos = std::stoi(match[2]);
        tempBot.xVel = std::stoi(match[3]);
        tempBot.yVel = std::stoi(match[4]);
        tempBot.xStart = tempBot.xPos;
        tempBot.yStart = tempBot.yPos;

        bots.push_back(tempBot);
    }

    simulate(bots, cycles);

    unsigned long long safety = calcSafety(bots);



    std::cout << "The safety factor after " << cycles << " cycles is: " << safety << std::endl;
}

void simulate(std::vector<Robot>& bots, int cycles)
{
    for (Robot& bot : bots)
    {
        bot.xPos = (((bot.xStart + bot.xVel * cycles) % cols) + cols) % cols;
        bot.yPos = (((bot.yStart + bot.yVel * cycles) % rows) + rows) % rows;

        if (debug)
        {
            std::cout << bot.xPos << "," << bot.yPos << std::endl;
        }
    }

}

unsigned long long calcSafety(std::vector<Robot>& bots)
{
    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;

    int vertMid = std::floor(cols / 2);
    int horMid = std::floor(rows / 2);

    for (const Robot& bot : bots)
    {
        if (bot.xPos < vertMid)
        {
            if (bot.yPos < horMid)
            {
                ++q1;
            }
            else if (bot.yPos > horMid)
            {
                ++q3;
            }
        }
        else if (bot.xPos > vertMid)
        {
            if (bot.yPos < horMid)
            {
                ++q2;
            }
            else if (bot.yPos > horMid)
            {
                ++q4;
            }
        }
    }

    return q1 * q2 * q3 * q4;
}
