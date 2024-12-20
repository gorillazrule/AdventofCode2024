// Day15_part1.cpp : 

#include <iostream>
#include "Matrix.h"
#include <string>


void move(Matrix& map, char c, std::pair<int,int>& botPos);
bool inBounds(Matrix& map, std::pair<int, int>& position);
void tryPush(Matrix& map, char dir, std::pair<int, int>& position, std::pair<int,int>& botPos);
void print(Matrix& map);

int main()
{
    const bool debug = false;
    std::ifstream infile("Input.txt");
    std::ofstream outfile("Map.txt");
    std::string line;
    int sum = 0;

    while (std::getline(infile, line))
    {
        if (line == "")
        {
            outfile.close();
            break;
        }
        outfile << line << std::endl;
    }

    std::ifstream mapFile("Map.txt");
    Matrix map(mapFile);
    std::pair<int, int> botPos = map.getStart();

    while (std::getline(infile, line))
    {
        for (char c : line)
        {
            move(map, c, botPos);
            if (debug)
            {
                print(map);
            }
        }
    }

    for (int i = 0; i < map.numRows; ++i)
    {
        for (int j = 0; j < map.numCols; ++j)
        {
            if (map.at(std::pair<int, int>{i, j}) == 'O')
            {
                sum += 100 * i + j;
            }
        }
    }

    std::cout << "The sum of all boxes' Gps Coordinates is: " << sum << std::endl;
}

void move(Matrix& map, char c, std::pair<int,int>& botPos)
{
    std::pair<int, int> nextPos = botPos;
    if (c == '^')
    {
        --nextPos.first;
    }
    else if (c == '>')
    {
        ++nextPos.second;
    }
    else if (c == 'v')
    {
        ++nextPos.first;
    }
    else if (c == '<')
    {
        --nextPos.second;
    }

    if (inBounds(map,nextPos) && map.at(nextPos) != '#')
    {
        if (map.at(nextPos) == 'O')
        {
            tryPush(map, c, nextPos, botPos);
        }
        else
        {
            map.set(botPos, '.');
            botPos = nextPos;
            map.set(botPos, '@');
        }
    }
}

bool inBounds(Matrix& map, std::pair<int, int>& position)
{
    if (position.first >= 0 && position.first < map.numRows && position.second >= 0 && position.second < map.numCols)
    {
        return true;
    }
    return false;
}

void tryPush(Matrix& map, char dir, std::pair<int, int>& position, std::pair<int, int>& botPos)
{
    std::pair<int, int> nextPos = position;
    if (dir == '^')
    {
        while (inBounds(map, nextPos) && map.at(nextPos) != '.' && map.at(nextPos) != '#')
        {
            --nextPos.first;
        }
        if (inBounds(map,nextPos) && map.at(nextPos) == '.')
        {
            while (nextPos != position)
            {
                map.set(nextPos, 'O');
                ++nextPos.first;
            }
            map.set(position, '@');
            map.set(botPos, '.');
            botPos = position;
        }
    }
    else if (dir == '>')
    {
        while (inBounds(map, nextPos) && map.at(nextPos) != '.' && map.at(nextPos) != '#')
        {
            ++nextPos.second;
        }
        if (inBounds(map, nextPos) && map.at(nextPos) == '.')
        {
            while (nextPos != position)
            {
                map.set(nextPos, 'O');
                --nextPos.second;
            }
            map.set(position, '@');
            map.set(botPos, '.');
            botPos = position;
        }
    }
    else if (dir == 'v')
    {
        while (inBounds(map, nextPos) && map.at(nextPos) != '.' && map.at(nextPos) != '#')
        {
            ++nextPos.first;
        }
        if (inBounds(map, nextPos) && map.at(nextPos) == '.')
        {
            while (nextPos != position)
            {
                map.set(nextPos, 'O');
                --nextPos.first;
            }
            map.set(position, '@');
            map.set(botPos, '.');
            botPos = position;
        }
    }
    else if (dir == '<')
    {
        while (inBounds(map, nextPos) && map.at(nextPos) != '.' && map.at(nextPos) != '#')
        {
            --nextPos.second;
        }
        if (inBounds(map, nextPos) && map.at(nextPos) == '.')
        {
            while (nextPos != position)
            {
                map.set(nextPos, 'O');
                ++nextPos.second;
            }
            map.set(position, '@');
            map.set(botPos, '.');
            botPos = position;
        }
    }
}

void print(Matrix& map)
{
    for (int i = 0; i < map.numRows; ++i)
    {
        for (int j = 0; j < map.numCols; ++j)
        {
            std::cout << map.at(std::pair<int, int>{i, j});
        }
        std::cout << std::endl;
    }
}
