#include <iostream>
#include <fstream>


int main()
{
    std::ifstream file("input.txt");
    char currentChar;
    int floorCount = 0;

    while (file >> currentChar)
    {
        if (currentChar == '(')
        {
            //std::cout << "Movin' up...!\n";
            floorCount++;
        }
        if (currentChar == ')')
        {
            //std::cout << "Goin' down!\n";
            floorCount--;
        }
    }

    std::cout << "Floor Count: " << floorCount;
}

/*
    What I Learned in this challenge:
    -- This is quite a simple exercise, especially after coming from the much harder 2019 puzzles. 
    -- I learned that I'm starting to understand the pattern of opening a file and extracting it's contents into a particular type of variable using a while loop.

 */