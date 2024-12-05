// Day4_part2.cpp : 


#include <iostream>
#include "matrix.h"
#include <cassert>

int search(Matrix& grid, int i, int j);


int main()
{
    std::ifstream infile("Input.txt");
    Matrix grid(infile);
    int xCount = 0;

    for (int i = 0; i < grid.numRows; ++i)
    {
        for (int j = 0; j < grid.numCols; ++j)
        {
            if (grid.at(i, j) == 'A')
            {
                xCount += search(grid, i, j);
            }
        }
    }

    std::cout << "There are " << xCount << " instances of \"X-MAS\"" << std::endl;
}

int search(Matrix& grid, int i, int j)
{
    int hits = 0;
    std::string diag1 = "";
    std::string diag2 = "";
    
    if (i - 1 >= 0 && j - 1 >= 0 && i + 1 < grid.numRows && j + 1 < grid.numCols)
    {
        diag1 += grid.at(i - 1, j - 1);
        diag1 += grid.at(i + 1, j + 1);

        diag2 += grid.at(i - 1, j + 1);
        diag2 += grid.at(i + 1, j - 1);

        if (diag1.find("X") == std::string::npos && diag1.find("A") == std::string::npos && diag1.at(0) != diag1.at(1))
        {
            if (diag2.find("X") == std::string::npos && diag2.find("A") == std::string::npos && diag2.at(0) != diag2.at(1))
            {
                ++hits;
            }
        }
    }

    return hits;
}
