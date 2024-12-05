#pragma once

#include <map>
class customSort
{
	std::multimap<int, int> ordering;
public:
	customSort(std::multimap<int, int> order) : ordering(order) {}
	bool operator()(const int a, const int b);

};

