// Day1_part1.cpp :

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <cmath>

template<typename T>
void getLists(std::ifstream &infile, T& list1,T& list2);

template<typename T>
void getDifferences(T& list1, T& list2, std::vector<int>& differences);

int main()
{
    std::ifstream infile("Input.txt");
    std::priority_queue<int, std::vector<int>, std::greater<int>> list1;
    std::priority_queue<int, std::vector<int>, std::greater<int>> list2;

    getLists(infile, list1, list2);

    std::vector<int> differences;

    getDifferences(list1, list2, differences);

    int total = 0;
    for (int i : differences)
    {
        total += i;
    }

    std::cout << "total:" << total;
}

template<typename T>
void getLists(std::ifstream& infile, T& list1, T& list2)
{
    int data;
    while (infile >> data)
    {
        list1.push(data);
        infile >> data;
        list2.push(data);
    }
}

template<typename T>
void getDifferences(T& list1, T& list2, std::vector<int>& differences)
{
    int coord1;
    int coord2;
    while (!list1.empty())
    {
        coord1 = list1.top();
        coord2 = list2.top();
        list1.pop();
        list2.pop();
        differences.push_back(std::abs(coord1 - coord2));
    }
}
