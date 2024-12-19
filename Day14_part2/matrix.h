#pragma once

#include <fstream>
#include <vector>

class Matrix
{
private:
	std::vector<char> data;
	std::pair<int, int> startPos;
	char at(int i, int j);
public:
	int numCols;
	int numRows;
	Matrix(std::ifstream& infile);
	Matrix(int rows, int cols, char c);
	char at(std::pair<int, int> coord);
	void set(std::pair<int, int> coord, char val);
	int count(char c);
	void fill(char c);

};