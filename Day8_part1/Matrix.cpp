#include "Matrix.h"
#include <string>
#include <cmath>

Matrix::Matrix(std::ifstream& infile)
{
	numRows = 0;
	numCols = 0;
	int numLines = 0;
	std::string line;
	while (std::getline(infile, line))
	{
		if (numCols == 0)
		{
			numCols = line.size();
		}

		++numLines;

		for (char c : line)
		{
			data.push_back(c);
		}
	}

	numRows = numLines;
}

char Matrix::at(std::pair<int, int> coord)
{
	return this->at(coord.first, coord.second);
}

void Matrix::set(std::pair<int, int> coord, char val)
{
	data.at(coord.first * numRows + coord.second) = val;
}

int Matrix::count(char c)
{
	int count = 0;
	for (char ch : data)
	{
		if (ch == c)
		{
			++count;
		}
	}
	return count;
}

void Matrix::fill(char c)
{
	for (int i = 0; i < data.size(); ++i)
	{
		data.at(i) = c;
	}
}

char Matrix::at(int i, int j)
{
	return data.at(i * numRows + j);
}