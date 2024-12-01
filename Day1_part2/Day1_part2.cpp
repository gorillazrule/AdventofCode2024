// Day1_part2.cpp :
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>


void getLists(std::ifstream& infile, std::vector<int>& list1, std::map<int, int>& list2);
int getSimilarity(std::vector<int>& list1, std::map<int, int>& list2);

int main()
{
    std::ifstream infile("Input.txt");
    std::vector<int> list1;
    std::map<int, int> list2;

    getLists(infile, list1, list2);

    int similarity = getSimilarity(list1, list2);

    std::cout << "Similarity:" << similarity;
}

void getLists(std::ifstream& infile, std::vector<int>& list1, std::map<int, int>& list2)
{
    int data;
    while (infile >> data)
    {
        list1.push_back(data);
        infile >> data;
        ++list2[data];
    }
}

int getSimilarity(std::vector<int>& list1, std::map<int, int>& list2)
{
    std::map<int, int>::iterator it;
    int similarity = 0;
    for (int i : list1)
    {
        it = list2.find(i); 
        if(it != list2.end())
        {
            similarity += (it->second * i);
        }
    }
    return similarity;
}
