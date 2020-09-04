#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main(){

    ifstream file("input.txt");
    std::string fileLine;
    bool grid[1000][1000];
    int coord1, coord2, coord3, coord4;
    enum Operation { turnOn, turnOff, toggle };
    Operation OpStatus;
    smatch matches;

    //set up the grid
    for(int i=0;i<1000;i++)
    {
        for (int j=0;j<1000;j++)
        {
            grid[i][j]=false;
        }
    }

    while (getline(file, fileLine))
    { 
        //Parse the line of text. Use matched groups sort the instruction and gather the four coordinates.
        if (regex_search(fileLine, matches, std::regex(R"(^(turn on|turn off|toggle) (\d+)(?:,)(\d+)(?: through )(\d+)(?:,)(\d+))")))
        {
            if (matches[1] == "turn on")
            {
                OpStatus = turnOn;
            }
            else if (matches[1] == "turn off")
            {
                OpStatus = turnOff;
            }
            else if (matches[1] == "toggle")
            {
                OpStatus = toggle;
            }
            coord1 = stoi(matches[2]);
            coord2 = stoi(matches[3]);
            coord3 = stoi(matches[4]);
            coord4 = stoi(matches[5]);
        }

        //follow the instructions
        switch (OpStatus)
        {
            case turnOn:
                for (int x = min(coord1,coord3); x <= max(coord1, coord3); x++)
                {
                    for (int y = min(coord2, coord4); y <= max(coord2, coord4); y++)
                    {
                        grid[x][y] = true;
                    }
                }
                break;
            case turnOff:
                for (int x = min(coord1,coord3); x <= max(coord1, coord3); x++)
                    {
                        for (int y = min(coord2, coord4); y <= max(coord2, coord4); y++)
                        {
                            grid[x][y] = false;
                        }
                    }
                break;
            case toggle:
                for (int x = min(coord1,coord3); x <= max(coord1, coord3); x++)
                    {
                        for (int y = min(coord2, coord4); y <= max(coord2, coord4); y++)
                        {
                            grid[x][y] = !grid[x][y];
                        }
                    }
                break;
            default:
                break;
        }

    }
    //count the lights
    int lightcount = 0;
    for (int z=0;z<1000;z++)
    {
        for (int c=-0;c<1000;c++)
        {
            if (grid[z][c] == true)
            {
                lightcount++;
            }
        }
    }
    cout << "Lights Left On: " << lightcount;
}

/* 
--- Day 6: Probably a Fire Hazard ---

-- Immediately, I tried using a Map object the way I did in Day 3, but trying to initialize a map of 1 million values to zero was...not good.

-- I discovered you can create an array by just naming the int with 2 dimensions. With some testing, I was mistaken beliving I needed a third dimension to hold the bool/value of the light's state, but I don't. The array is the coordinate system, and the value of the int can hold it fine.
    -- I wonder if it'd be possible to instatiate other variables like this? Like an array of bools in the form of bool grid[100][100]??
    -- Turns out you can use an array of bools, and they're 1/4 the size! (bools are one byte, ints are 4 bytes.)

-- The reason the int [1000][1000] was crashing was because the stack is capped at 1mb. I need to do research on what it means to "dynamically allocate" memory, instead of using "Static memory." The windows "Stack" size is usually limited to 1MB, and the error I was getting ("unable to open chkstk.asm") is usually related to running out of stack space. Allegedly, C++ CAN handle arrays as large as [1000][1000], but not on the stack, they should be allocated on the heap.

-- Figuring out a method for parsing the string out was taking a long time and I realized regex might be up to the task here, especially because I want to practice it after giving up on Day 5.
    -- It turns out regex MATCH is very, very different than regex SEARCH!
    -- Using the "smatch" template (the string implementation of the regex_match template (hence "smatch" for string match), I can collect "capture groups" and access them!

-- int grid[999][999] appears to be breaking the program (?? Memory??) so for now I've reduced it to [99][99]
    --When initializing the value of int grid[99][99], there's a LOT of values that aren't set to zero. I wonder what happens then...

-- DOH. I needed to create the grid at bool grid[1000][1000], not [999][999].

The puzzle solution was: 569999.

 */