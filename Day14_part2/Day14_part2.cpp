// Day14_part2.cpp : 

#include <iostream>
#include "matrix.h"
#include <regex>

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

void print(std::vector<Robot>& bots, Matrix map, std::ofstream& output);

int main()
{
    std::ifstream infile("Input.txt");
    std::ofstream outfile("Output.txt");
    std::string line;
    std::regex rgx("p=(\\d+),(\\d+).*v=(-?\\d+),(-?\\d+)");
    std::smatch match;
    std::vector<Robot> bots;
    Matrix map(rows, cols, ' ');

    const int cycles = 10403;
    const int skipCycles = 0;

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

    if (skipCycles != 0)
    {
        for (Robot& bot : bots)
        {
            bot.xPos = (((bot.xStart + bot.xVel * skipCycles) % cols) + cols) % cols;
            bot.yPos = (((bot.yStart + bot.yVel * skipCycles) % rows) + rows) % rows;
        }
    }

    for (int i = skipCycles; i < cycles; ++i)
    {
        for (Robot& bot : bots)
        {
            bot.xPos = (((bot.xPos + bot.xVel) % cols) + cols) % cols;
            bot.yPos = (((bot.yPos + bot.yVel) % rows) + rows) % rows;
        }
        outfile << "cycle: " << i << std::endl;
        print(bots, map, outfile);
    }
    std::cout << "Hello World!\n";
}

void print(std::vector<Robot>& bots, Matrix map, std::ofstream& output)
{
    for (Robot bot : bots)
    {
        map.set(std::pair<int, int> {bot.xPos, bot.yPos}, '*');
    }

    for (int i = 0; i < map.numCols; ++i)
    {
        for (int j = 0; j < map.numRows; ++j)
        {
            output << map.at(std::pair<int, int> {i, j});
        }
        output << std::endl;
    }

    output << std::endl << std::endl;
}
