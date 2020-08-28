#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include "day3_funcs.h"

using namespace std;

int main(){
    vector<char> input;
    char inputChar;
    std::pair<int, int> santaCoordPair = {0,0}, roboSantaCoordPair = {0,0};
    map<pair<int, int>, int> coordinateGrid;

    bool bSantasTurn = true; //true = Santa's turn, false = robo-Santa's turn

    //read the file
    std::ifstream file("input.txt");
    while (file >> inputChar)
    {
        input.push_back(inputChar);
    }
    
    //Santa drops his first gift at 0,0., as per problem description.
    bSantasTurn = true;
    dropPresent(bSantasTurn, santaCoordPair, roboSantaCoordPair, coordinateGrid);
    //RoboSanta drop his first gift at 0,0, as per problem description.
    bSantasTurn = false;
    dropPresent(bSantasTurn, santaCoordPair, roboSantaCoordPair, coordinateGrid);
 
    for (int i=0;i<input.size();i++)
    {
        if (i % 2 == 0)
        {
            bSantasTurn = true; //Santa's Turn
        }
        else
        {
            bSantasTurn = false; //RoboSanta's Turn
        }

        //move
        switch(input[i]){
        case '^':
            if(bSantasTurn){
                santaCoordPair.second++;
            }
            else {
                roboSantaCoordPair.second++;
            }
            break;
        case '>':
            if(bSantasTurn){
                santaCoordPair.first++;
            }
            else {
                roboSantaCoordPair.first++;
            }
            break;
        case 'v':
            if(bSantasTurn){
                santaCoordPair.second--;
            }
            else {
                roboSantaCoordPair.second--;
            }
            break;
        case '<':
            if(bSantasTurn){
                santaCoordPair.first--;
            }
            else {
                roboSantaCoordPair.first--;
            }
            break;
        default:
            cerr << "\nError! Unhandled input at " << i << "!";
            break;
        }

        //drop presents
        dropPresent(bSantasTurn, santaCoordPair, roboSantaCoordPair, coordinateGrid);

    }
    std::cout << endl << coordinateGrid.size() << " total houses.";
}


/* --- Day 3: Perfectly Spherical Houses in a Vacuum ---

    What I've learned:
        -- instead of just logging errors, I can actually use "cerr" to print directly into the error stream. This would likely be a lot safer, just in case the program crashes before I can log the error using a std::cout for some reason.
        -- Visual Studio Code: I've learned a lot about manipulating the launch and tasks json files and how to include extra files so that I can now support compiling external classes. I never ended up using the class I made for "houses", however.

        -- I explored a few ideas in researching a way to address this solution, much of which is not used in it. 
            ++Conceptually, I learned that C++ Classes and Structs are the same thing except structs default to their members being public, Classes default to private.
            ++I learned about maps and pairs, and learned that I can use a pair in a map to represent a 2D array with an attached value to each key, rather than using a vector of vectors to create an array.

        -- I wrote the file-reading statements essentially from memory which was great.
        -- I can just put the instructions in the "readme" file instead of a file named "Instructions" and they'll display more elegantly on Github!

        -- Be super careful when copying any line of code. When breaking up the "coordinatepair" variable into "SantaPos" and "RoboSantaPos" to independently store each Santa's position, I copy-pasted and wound up flipping things weirdly. Don't shortcut! Just type.

        -- By creating a function called dropPresent and "Passing Arguments By Reference", I was able to very neatly and cleanly traverse the input and have the santas drop presents correctly, from a single line of code!

        The correct answer to this puzzle was: 2592 houses.
        The correct answer to part two was 2,360 houses.

 */