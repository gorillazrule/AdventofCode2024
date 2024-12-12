// Day10_part1.cpp : 

#include <iostream>
#include <queue>
#include "Matrix.h"
#include <unordered_set>

struct Step{
    std::pair<int,int> position;
    int height;
};

struct hash
{
    size_t operator()(const std::pair<int, int>& x) const
    {
        if (x.second > x.first)
        {
            return x.second * x.second + x.first;
        }
        else
        {
            return x.first * x.first + x.first + x.second;
        }
    }
};

bool operator >(const Step& lhs, const Step& rhs)
{
    return lhs.height > rhs.height;
}

int path(Matrix& map, std::pair<int, int>& position);
void addStep(Matrix& map, int curHeight, std::priority_queue< Step, std::vector<Step>, std::greater<Step>>& steps, std::pair<int, int>& nextPos);
bool inBounds(Matrix& map, std::pair<int, int> position);

int main()
{
    //Read input into matrix
    std::ifstream infile("Input.txt");
    Matrix map(infile);
    int total = 0;
    
    //loop through matrix and search for 0s.
    for (int i = 0; i < map.numRows; ++i)
    {
        for (int j = 0; j < map.numCols; ++j)
        {
            std::pair<int, int> pos = { i,j };
            if (map.at(pos) == '0')
            {
                total += path(map, pos);
            }
        }
    }

    std::cout << "Sum of trailheads:" << total << std::endl;;
}


int path(Matrix& map, std::pair<int, int>& position)
{
    std::priority_queue<Step, std::vector<Step>, std::greater<Step>> steps;
    Step temp;
    temp.position = position;
    temp.height = 0;
    steps.push(temp);
    std::unordered_set<std::pair<int, int>, hash> peaks;

    while (!steps.empty())
    {
        Step curStep = steps.top();
        Step temp;
        steps.pop();
        std::pair<int, int> curPos = curStep.position;
        std::pair<int, int> nextPos = curPos;
        
        //check if current height is the max
        if (curStep.height == 9)
        {
            peaks.insert(curStep.position);
            continue;
        }

        //check up
        --nextPos.first;
        addStep(map, curStep.height, steps, nextPos);
        nextPos = curPos;

        //check right
        ++nextPos.second;
        addStep(map, curStep.height, steps, nextPos);
        nextPos = curPos;

        //check down
        ++nextPos.first;
        addStep(map, curStep.height, steps, nextPos);
        nextPos = curPos;
        
        //check left
        --nextPos.second;
        addStep(map, curStep.height, steps, nextPos);
    }

    //return the number of unique peaks reachable from trailhead
    return peaks.size();
}

void addStep(Matrix& map, int curHeight, std::priority_queue<Step, std::vector<Step>, std::greater<Step>>& steps, std::pair<int, int>& nextPos)
{
    if (inBounds(map, nextPos))
    {
        if (map.at(nextPos) - '0' == curHeight + 1)
        {
            Step temp;
            temp.height = curHeight + 1;
            temp.position = nextPos;
            steps.push(temp);
        }
    }
    return;
}

bool inBounds(Matrix& map, std::pair<int, int> position)
{
    if (position.first >= 0 && position.first < map.numRows && position.second >= 0 && position.second < map.numCols)
    {
        return true;
    }
    return false;
}