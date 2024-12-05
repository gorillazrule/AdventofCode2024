#pragma once

#include <fstream>
#include <vector>

class Matrix
{
private:
	std::vector<char> data;
public:
	int numCols;
	int numRows;
	Matrix(std::ifstream &infile);
	char at(int i, int j);

};

