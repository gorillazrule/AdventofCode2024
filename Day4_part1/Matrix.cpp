#include "Matrix.h"
#include <string>

Matrix::Matrix(std::ifstream &infile)
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

char Matrix::at(int i, int j)
{
	return data.at(i * numRows + j);
}
