// Day6_part1.cpp : 

#include <iostream>
#include "Matrix.h"

enum Facing { up, right, down, left};

bool onMap(Matrix& map, std::pair<int, int>& curPos);

int main()
{
    std::ifstream infile("Input.txt");
    Matrix map(infile);
    std::pair<int, int> curPos = map.getStart();
    Facing direction = up;
    bool inBounds = true;

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

    while (inBounds)
    {
        map.set(curPos, 'X');
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

    std::cout << "Traveled " << map.count('X') << " unique spaces" << std::endl;
}

bool onMap(Matrix& map, std::pair<int, int>& curPos)
{
    int i = curPos.first;
    int j = curPos.second;
    if (i >= 0 && i < map.numRows && j >= 0 && j < map.numCols)
    {
        return true;
    }
    return false;
}
