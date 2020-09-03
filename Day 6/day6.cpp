#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main(){

    ifstream file("input.txt");
    std::string fileLine;
    int grid[999][999], coord1, coord2, coord3, coord4;
    enum Operation { turnOn, turnOff, toggle };
    Operation OpStatus;
    smatch matches;

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
                for (int x = min(coord1,coord3); x < max(coord1, coord3); x++)
                {
                    for (int y = min(coord2, coord4); y < max(coord2, coord4); y++)
                    {
                        grid[x][y] = 1;
                    }
                }
                break;
            case turnOff:
                break;
            case toggle:
                break;
            default:
                break;
        }

    }
}

/* 
--- Day 6: Probably a Fire Hazard ---

-- Immediately, I tried using a Map object the way I did in Day 3, but trying to initialize a map of 1 million values to zero was...not good.

-- I discovered you can create an array by just naming the int with 2 dimensions. With some testing, I was mistaken beliving I needed a third dimension to hold the bool/value of the light's state, but I don't. The array is the coordinate system, and the value of the int can hold it fine.
    -- I wonder if it'd be possible to instatiate other variables like this? Like an array of bools in the form of bool grid[100][100]??

-- Figuring out a method for parsing the string out was taking a long time and I realized regex might be up to the task here, especially because I want to practice it after giving up on Day 5.
    -- It turns out regex MATCH is very, very different than regex SEARCH!
    -- Using the "smatch" template (the string implementation of the regex_match template (hence "smatch" for string match), I can collect "capture groups" and access them!

-- int grid[999][999] appears to be breaking the program (?? Memory??) so for now I've reduced it to [99][99]
    --When initializing the value of int grid[99][99], there's a LOT of values that aren't set to zero. I wonder what happens then...



--- Puzzle: ----
Because your neighbors keep defeating you in the holiday house decorating contest year after year, you've decided to deploy one million lights in a 1000x1000 grid.
2
Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction; the lights at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. Each coordinate pair represents opposite corners of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.

For example:

    turn on 0,0 through 999,999 would turn on (or leave on) every light.
    toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
    turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.

After following the instructions, how many lights are lit?

 */