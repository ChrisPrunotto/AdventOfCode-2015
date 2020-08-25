#include <iostream>
#include <fstream>


int main()
{
    std::ifstream file("input.txt");
    char currentChar;
    int floorCount = 0, instructionCount=0;
    bool bHasHitBasement = false;

    while (file >> currentChar)
    {
        instructionCount++;
        if (currentChar == '(')
        {
            //std::cout << "Movin' up...!\n";
            floorCount++;
        }
        if (currentChar == ')')
        {
            //std::cout << "Goin' down!\n";
            floorCount--;
            if (floorCount < 0 && bHasHitBasement == false)
            {
                bHasHitBasement = true;
                std::cout << "Basement found at Instruction #: " << instructionCount << "\n";
            }
        }
    }

    std::cout << "Floor Count: " << floorCount;
}

/*
    What I Learned in this challenge:
    -- This is quite a simple exercise, especially after coming from the much harder 2019 puzzles. 
    -- I learned that I'm starting to understand the pattern of opening a file and extracting it's contents into a particular type of variable using a while loop.
    -- Initially, I tried iterating instruction count at the top of the while loop, right above the if statement for currentChar == '(', but it wound up incredibly unpredictable. Turns out I wasn't initializing that variable to zero, and the number was very off, to say the least.

    The puzzle solution is Instruction #1783

 */