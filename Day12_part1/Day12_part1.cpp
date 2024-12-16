// Day12_part1.cpp : 

#include <iostream>
//from Day8_part1
#include "Matrix.h"
#include <queue>

struct Fencing
{
    int size;
    int perimeter;
    int price;
    char plant;
};

Fencing search(Matrix& map, Matrix& key, std::pair<int,int> start);
bool inBounds(Matrix& map, std::pair<int, int>& coord);
void process(Matrix& map, Matrix& key, std::pair<int, int>& next, std::queue<std::pair<int, int>>& plots, int& perimeter, char& c);

int main()
{
    //Read file into a Matrix
    std::ifstream infile("Input.txt");
    Matrix garden(infile);
    //Create separate matrix for tiles that have been accounted for
    Matrix counted = garden;
    counted.fill('.');
    
    std::vector<Fencing> fences;
    bool debug = true;
    int total = 0;

    //Loop through matrix, search adjacent edges for matching plants, mark off each tile that has been accounted
    // calculate Area
    // calculate Perimeter
    //create vector of Fencing.
    for (int i = 0; i < garden.numRows; ++i)
    {
        for (int j = 0; j < garden.numCols; ++j)
        {
            if (counted.at(std::pair<int, int> {i, j}) == '.')
            {
                fences.push_back(search(garden, counted, std::pair<int, int> {i, j}));
            }
        }
    }

    for (Fencing fence : fences)
    {
        if (debug)
        {
            std::cout << "A region of " << fence.plant << " plants with price " << fence.size << " * " << fence.perimeter << " = " << fence.price << std::endl;
        }
        total += fence.price;
    }
    
    std::cout << "Total price of fences: " << total << std::endl;
}

Fencing search(Matrix& map, Matrix& key, std::pair<int, int> start)
{
    int area = 0;
    int perimeter = 0;
    Fencing region;
    std::queue<std::pair<int, int>> plots;
    char c = map.at(start);

    plots.push(start);

    while (!plots.empty())
    {
        std::pair<int, int> cur = plots.front();
        plots.pop();
        key.set(cur, '*');
        ++area;

        if (map.at(cur) == c)
        {
            std::pair<int, int> next;
            next = cur;

            //Search adjecent sides for matching plots.
            //Up
            --next.first;
            process(map, key, next, plots, perimeter, c);
            next = cur;

            //Right
            ++next.second;
            process(map, key, next, plots, perimeter, c);
            next = cur;
           
            //Down
            ++next.first;
            process(map, key, next, plots, perimeter, c);
            next = cur;
            
            //Left
            --next.second;
            process(map, key, next, plots, perimeter, c);
            
        }

    }

    region.perimeter = perimeter;
    region.size = area;
    region.plant = c;
    region.price = perimeter * area;

    return region;
}

bool inBounds(Matrix& map, std::pair<int, int>& coord)
{
    if (coord.first >= 0 && coord.first < map.numRows && coord.second >= 0 && coord.second < map.numCols)
    {
        return true;
    }
    return false;
}

void process(Matrix& map, Matrix& key, std::pair<int, int>& next, std::queue<std::pair<int, int>>& plots, int& perimeter, char &c)
{
    //If you find a matching plot that hasnt been counted, add to plots
    //If different plot type, or on edge of map, increase perimeter
    if (inBounds(map, next))
    {
        if (map.at(next) == c && key.at(next) == '.')
        {
            plots.push(next);
            key.set(next, '*');
        }
        else if (map.at(next) != c)
        {
            ++perimeter;
        }
    }
    else
    {
        ++perimeter;
    }
}
