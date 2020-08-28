#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int main(){
    vector<char> input;
    char inputChar;
    std::pair<int, int> coordPair;
    map<pair<int, int>, int> coordinateGrid;

    int xPos = 0, yPos = 0;
    coordPair.first = xPos;
    coordPair.second = yPos;

    //read the file
    std::ifstream file("input.txt");
    while (file >> inputChar)
    {
        input.push_back(inputChar);
    }
    
    //Santa drops his first gift at 0,0.
    coordinateGrid.insert({coordPair,1});
    std::cout << "Current Coordinates: (" << xPos << ", " << yPos << "). Presents: " << coordinateGrid[{coordPair}] << std::endl;

    for (int i=0;i<input.size();i++)
    {
        //move
        switch(input[i]){
        case '^':
            yPos++;
            break;
        case '>':
            xPos++;
            break;
        case 'v':
            yPos--;
            break;
        case '<':
            xPos--;
            break;
        default:
            cerr << "\nError! Unhandled input at " << i << "!";
            break;
        }

        coordPair.first = xPos;
        coordPair.second = yPos;
        
        if (coordinateGrid.find({coordPair}) == coordinateGrid.end()){
            coordinateGrid.insert({coordPair,1});
        }
        else {
            coordinateGrid[{coordPair}] +=1;
        }
        std::cout << "Current Coordinates: (" << xPos << ", " << yPos << "). Presents: " << coordinateGrid[{coordPair}] << std::endl;
    }

    std::cout << "\nSanta is now at: (" << xPos << ", " << yPos << ")." << endl;
    std::cout << "Santa has visited: " << coordinateGrid.size() << " houses.";
}


/* --- Day 3: Perfectly Spherical Houses in a Vacuum ---

    What I've learned:
        -- instead of just logging errors, I can actually use "cerr" to print directly into the error stream. This would likely be a lot safer, just in case the program crashes before I can log the error using a std::cout for some reason.
        -- Visual Studio Code: I've learned a lot about manipulating the launch and tasks json files and how to include extra files so that I can now support compiling external classes. I never ended up using the class I made for "houses", however.

        -- I explored a few ideas in researching a way to address this solution, much of which is not used in it. 
            ++Conceptually, I learned that C++ Classes and Structs are the same thing except structs default to their members being public, Classes default to private.
            ++I learned about maps and pairs, and learned that I can use a pair in a map to represent a 2D array with an attached value to each key, rather than using a vector of vectors to create an array.

        -- I wrote the file-reading statements essentially from memory which was great.
        The correct answer to this puzzle was: 2592 houses.
 */