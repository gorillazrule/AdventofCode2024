// Day8_part2.cpp : 

#include <iostream>
#include "Matrix.h"
#include <map>

template <typename T>
std::pair<T, T> operator+(const std::pair<T, T>& l, const std::pair<T, T>& r)
{
    return { l.first + r.first, l.second + r.second };
}

template <typename T>
std::pair<T, T> operator-(const std::pair<T, T>& l, const std::pair<T, T>& r)
{
    return { l.first - r.first, l.second - r.second };
}

template <typename T>
std::pair<T, T> operator+=(std::pair<T, T>& l, const std::pair<T, T>& r)
{
    l.first = l.first + r.first;
    l.second = l.second + r.second;
    return l;
}

template <typename T>
std::pair<T, T> operator-=(std::pair<T, T>& l, const std::pair<T, T>& r)
{
    l.first = l.first - r.first;
    l.second = l.second - r.second;
    return r;
}

std::pair<int, int> getDistance(std::pair<int, int>& a, std::pair<int, int>& b);
bool inBounds(Matrix& map, std::pair<int, int>& coord);

int main()
{
    //populate the map with data
    std::ifstream infile("Input.txt");
    Matrix map(infile);
    Matrix antinodes = map;
    antinodes.fill('.');
    std::multimap<char, std::pair<int, int>> antennas;

    //Scan through the map, and populate antennas with the frequency and location of all antennas
    for (int i = 0; i < map.numRows; ++i)
    {
        for (int j = 0; j < map.numCols; ++j)
        {
            std::pair<int, int> coord{ i,j };
            char c = map.at(coord);
            if (c != '.')
            {
                antennas.emplace(c, coord);
            }
        }
    }

    //Loop through antennas, finding where all the antinodes are, and placing a marker on the antinode matrix
    decltype(antennas.equal_range(' ')) range;
    for (auto i = antennas.begin(); i != antennas.end(); i = range.second)
    {
        range = antennas.equal_range(i->first);

        for (auto j = range.first; j != range.second; ++j)
        {
            for (auto k = std::next(j); k != range.second; ++k)
            {
                //calculate the distance between the 2 antennas
                std::pair<int, int> distance = getDistance(j->second, k->second);
                antinodes.set(j->second, '#');
                antinodes.set(k->second, '#');

                //check all possible antinodes;
                std::pair<int, int> antinode1 = j->second + distance;
                std::pair<int, int> antinode2 = k->second - distance;
                while (inBounds(antinodes, antinode1))
                {
                    antinodes.set(antinode1, '#');
                    antinode1 += distance;
                }
                while (inBounds(antinodes, antinode2))
                {
                    antinodes.set(antinode2, '#');
                    antinode2 -= distance;
                }
            }
        }
    }


    std::cout << "There are: " << antinodes.count('#') << " unique antinodes" << std::endl;
}

std::pair<int, int> getDistance(std::pair<int, int>& a, std::pair<int, int>& b)
{
    int i = a.first - b.first;
    int j = a.second - b.second;


    return std::pair<int, int> {i, j};
}

bool inBounds(Matrix& map, std::pair<int, int>& coord)
{
    if (coord.first >= 0 && coord.second >= 0 && coord.first < map.numRows && coord.second < map.numCols)
    {
        return true;
    }
    return false;
}
