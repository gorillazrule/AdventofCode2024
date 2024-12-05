// Day4_part1.cpp : 


#include <iostream>
#include "Matrix.h"

int search(Matrix& grid, int i, int j);


int main()
{
    std::ifstream infile("Input.txt");
    Matrix grid(infile);
    int wordCount = 0;

    for (int i = 0; i < grid.numRows; ++i)
    {
        for (int j = 0; j < grid.numCols; ++j)
        {
            if (grid.at(i, j) == 'X')
            {
                wordCount += search(grid, i, j);
            }
        }
    }

    std::cout << "There are " << wordCount << " instances of \"XMAS\"" << std::endl;
}

int search(Matrix& grid, int i, int j)
{
    int hits = 0;
    std::string target = "XMAS";
    std::string start = "X";
    std::string word = start;
    //Look up
    if (i - 3 >= 0)
    {
        word += grid.at(i - 1, j);
        word += grid.at(i - 2, j);
        word += grid.at(i - 3, j);
        if (word == target)
        {
            ++hits;
        }
        word = start;
    }

    //look up-right
    if (i - 3 >= 0 && j + 3 < grid.numCols)
    {
        word += grid.at(i - 1, j + 1);
        word += grid.at(i - 2, j + 2);
        word += grid.at(i - 3, j + 3);
        if (word == target)
        {
            ++hits;
        }
        word = start;
    }

    //look right
    if (j + 3 < grid.numCols)
    {
        word += grid.at(i, j + 1);
        word += grid.at(i, j + 2);
        word += grid.at(i, j + 3);
        if (word == target)
        {
            ++hits;
        }
        word = start;
    }

    //look down-right
    if (i + 3 < grid.numRows && j + 3 < grid.numCols)
    {
        word += grid.at(i + 1, j + 1);
        word += grid.at(i + 2, j + 2);
        word += grid.at(i + 3, j + 3);
        if (word == target)
        {
            ++hits;
        }
        word = start;

    }

    //look down
    if (i + 3 < grid.numRows)
    {
        word += grid.at(i + 1, j);
        word += grid.at(i + 2, j);
        word += grid.at(i + 3, j);
        if (word == target)
        {
            ++hits;
        }
        word = start;

    }

    //look down-left
    if (i + 3 < grid.numRows && j - 3 >= 0)
    {
        word += grid.at(i + 1, j - 1);
        word += grid.at(i + 2, j - 2);
        word += grid.at(i + 3, j - 3);
        if (word == target)
        {
            ++hits;
        }
        word = start;
    }

    //look left
    if (j - 3 >= 0)
    {
        word += grid.at(i, j - 1);
        word += grid.at(i, j - 2);
        word += grid.at(i, j - 3);
        if (word == target)
        {
            ++hits;
        }
        word = start;
    }

    //look up-left
    if (i - 3 >= 0 && j - 3 >= 0)
    {
        word += grid.at(i - 1, j - 1);
        word += grid.at(i - 2, j - 2);
        word += grid.at(i - 3, j - 3);
        if (word == target)
        {
            ++hits;
        }
        word = start;
    }

    return hits;
}
