#pragma once

#include <fstream>
#include <vector>

class Matrix
{
private:
	std::vector<char> data;
	std::pair<int, int> startPos;
	void setStart(int pos);
	char at(int i, int j);
public:
	int numCols;
	int numRows;
	Matrix(std::ifstream& infile);
	char at(std::pair<int, int> coord);
	void set(std::pair<int, int> coord, char val);
	int count(char c);

	std::pair<int, int> getStart();

};

