// Day6_part2.cpp : 

#include <iostream>
#include "Matrix.h"
#include <map>

enum Facing { up, right, down, left };

bool onMap(Matrix& map, std::pair<int, int> curPos);
int simulate(Matrix& map, std::pair<int, int> startPos);

int main()
{
    std::ifstream infile("Input.txt");
    Matrix map(infile);
    std::pair<int, int> start = map.getStart();
    int loopCount = 0;
    int simCount = 0;

    //populate the Map
    simulate(map, start);

    //Run simulations for every position that has been visited
    for (int i = 0; i < map.numRows; ++i)
    {
        for (int j = 0; j < map.numCols; ++j)
        {
            if (map.at(std::pair<int, int> {i, j}) == 'X')
            {
                Matrix cpy = map;
                cpy.set(std::pair<int, int>{i, j}, '#');
                loopCount += simulate(cpy, start);

                //Keep track of simulations just to make sure we're not caught in a loop
                std::cout << "Simulation: " << simCount << std::endl;
                simCount++;
            }
        }
    }

    std::cout << "There are " << loopCount << " possible positions to place an obstruction." << std::endl;
}

bool onMap(Matrix& map, std::pair<int, int> curPos)
{
    int i = curPos.first;
    int j = curPos.second;
    if (i >= 0 && i < map.numRows && j >= 0 && j < map.numCols)
    {
        return true;
    }
    return false;
}

int simulate(Matrix& map, std::pair<int, int> startPos)
{
    bool inBounds = true;
    bool loop = false;
    std::pair<int, int> curPos = startPos;

    std::multimap<int, Facing> path;

    Facing direction = up;

    //Determine which direction the start is facing. and set the Facing.
    char start = map.at(curPos);
    if (start == '^')
    {
        direction = up;
    }
    else if (start == '>')
    {
        direction = right;
    }
    else if (start == 'v')
    {
        direction = down;
    }
    else if (start == '<')
    {
        direction = left;
    }

    //Loop through until either out of bounds or loop detected;
    while (inBounds && !loop)
    {
        //Mark unique spaces travelled
        map.set(curPos, 'X');

        //generate an id based upon the position
        int id = curPos.first * map.numRows + curPos.second;

        //check if this position has been traveled to before
        if (path.contains(id))
        {
            //check if this position has been reached facing this direction before
            auto range = path.equal_range(id);
            for (auto i = range.first; i != range.second; ++i)
            {
                if (i->second == direction)
                {
                    loop = true;
                }
            }
        }
        //enter the position and facing to the path log
        else
        {
            path.emplace(id, direction);
        }

        std::pair<int, int> nextPos = curPos;

        switch (direction)
        {
        case up:
            nextPos.first--;
            if (!onMap(map, nextPos))
            {
                break;
            }
            if (map.at(nextPos) == '#')
            {
                direction = right;
                nextPos.first++;
            }
            break;
        case right:
            nextPos.second++;
            if (!onMap(map, nextPos))
            {
                break;
            }
            if (map.at(nextPos) == '#')
            {
                direction = down;
                nextPos.second--;
            }
            break;
        case down:
            nextPos.first++;
            if (!onMap(map, nextPos))
            {
                break;
            }
            if (map.at(nextPos) == '#')
            {
                direction = left;
                nextPos.first--;
            }
            break;
        case left:
            nextPos.second--;
            if (!onMap(map, nextPos))
            {
                break;
            }
            if (map.at(nextPos) == '#')
            {
                direction = up;
                nextPos.second++;
            }
            break;
        }

        curPos = nextPos;
        inBounds = onMap(map, curPos);
    }

    //return 1 if loop detected
    if (loop)
    {
        return 1;
    }
    
    return 0;
}
