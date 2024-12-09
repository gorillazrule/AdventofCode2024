// Day9_part1.cpp : 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


struct memBlock
{
    int id;
    int size;
};

unsigned long long checkSum(std::vector<memBlock>& memory);
void print(std::vector<memBlock>& memory);

int main()
{
    std::ifstream infile("Input.txt");
    char c;
    bool isFile = true;
    std::vector<memBlock> memory;
    int id = 0;

    //create a vector of memoryBlocks where an id of -1 indicates the space is empty
    while (infile >> c)
    {
        int size = c - '0';
        memBlock block;
        block.size = size;
        if (isFile)
        {
            block.id = id;
            ++id;
        }
        else
        {
            block.id = -1;
        }
        isFile = !isFile;
        memory.push_back(block);
    }

    auto left = memory.begin();
    auto right = memory.rbegin();

    //loop through until the iterators meet
    while (std::distance(left,right.base() - 1) > 0)
    {
        //If the right iterator is not on a file
        if (right->id == -1)
        {
            ++right;
            continue;
        }

        //if the left iterator is on empty space, fill it with files from the right iterator.
        if (left->id == -1)
        {
            //Space is larger than file
            if (left->size > right->size)
            {
                int lDist = std::distance(memory.begin(), left);
                int rDist = std::distance(memory.rbegin(), right);
                int fileSize = right->size;
                left->size -= fileSize;
                memory.insert(left, *right);

                //fix iterators
                left = std::next(memory.begin(), lDist);
                right = std::next(memory.rbegin(), rDist);
                right->id = -1;

            }

            //Space and file are same size
            else if (left->size == right->size)
            {
                left->id = right->id;
                right->id = -1;
                ++left;
            }
 
            //File is large than space
            else if (left->size < right->size)
            {
                right->size -= left->size;
                left->id = right->id;
                ++left;
            }
        }
        else
        {
            ++left;
        }
    }

    std::cout << "The new filesystem checksum is: " << checkSum(memory) << std::endl;
}

unsigned long long checkSum(std::vector<memBlock>& memory)
{
    unsigned long long check = 0;
    int position = 0;
    for (memBlock block : memory)
    {
        if (block.id >= 0)
        {
            for (int i = block.size; i > 0; --i)
            {
                check += position * block.id;
                ++position;
            }
        }
    }
    
    return check;
}

//This is for debuging/logging purposes
void print(std::vector<memBlock>& memory)
{
    for (memBlock block : memory)
    {
        for (int i = block.size; i > 0; --i)
        {
            std::cout << block.id;
        }
    }
    std::cout << std::endl;
}
