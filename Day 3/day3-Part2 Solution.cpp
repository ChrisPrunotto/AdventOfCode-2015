#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int main(){
    vector<char> input;
    char inputChar;
    std::pair<int, int> santaCoordPair, roboSantaCoordPair;
    map<pair<int, int>, int> coordinateGrid;

    int xSantaPos = 0, ySantaPos = 0, xRoboSantaPos = 0, yRoboSantaPos = 0;
    santaCoordPair.first = xSantaPos;
    santaCoordPair.second = ySantaPos;

    roboSantaCoordPair.first = xRoboSantaPos;
    roboSantaCoordPair.second = yRoboSantaPos;

    bool bSantasTurn = true; //true = Santa's turn, false = robo-Santa's turn

    //read the file
    std::ifstream file("input.txt");
    while (file >> inputChar)
    {
        input.push_back(inputChar);
    }
    
    //Santa drops his first gift at 0,0.
    coordinateGrid.insert({santaCoordPair,1});
    //RoboSanta drop his first gift at 0,0.
    coordinateGrid[{roboSantaCoordPair}] +=1;
    //std::cout << "Current Coordinates: (" << xPos << ", " << yPos << "). Presents: " << coordinateGrid[{santaCoordPair}] << std::endl;
 
    for (int i=0;i<input.size();i++)
    {
        std::cout << "Turn number: " << i;
        if (i % 2 == 0)
        {
            //set the turn
            bSantasTurn = true;
            std::cout << " is Santa's Turn." <<endl;
        }
        else
        {
            bSantasTurn = false;
            std::cout << " is RoboSanta's Turn." <<endl;
        }

        //move
        switch(input[i]){
        case '^':
            if(bSantasTurn){
                ySantaPos++;
            }
            else {
                yRoboSantaPos++;
            }
            break;
        case '>':
            if(bSantasTurn){
                xSantaPos++;
            }
            else {
                xRoboSantaPos++;
            }
            break;
        case 'v':
            if(bSantasTurn){
                ySantaPos--;
            }
            else {
                yRoboSantaPos--;
            }
            break;
        case '<':
            if(bSantasTurn){
                xSantaPos--;
            }
            else {
                xRoboSantaPos--;
            }
            break;
        default:
            cerr << "\nError! Unhandled input at " << i << "!";
            break;
        }

        //update coordinates
        santaCoordPair.first = xSantaPos;
        santaCoordPair.second = ySantaPos;
        roboSantaCoordPair.first = xRoboSantaPos;
        roboSantaCoordPair.second = yRoboSantaPos;

        //drop presents
        if (bSantasTurn)
        {
            if (coordinateGrid.find({santaCoordPair}) == coordinateGrid.end()){
                coordinateGrid.insert({santaCoordPair,1});
            }
            else{
                coordinateGrid[{santaCoordPair}] +=1;
            }
        }
        else {
            if (coordinateGrid.find({roboSantaCoordPair}) == coordinateGrid.end()){
                coordinateGrid.insert({roboSantaCoordPair,1});
            }
            else{
                coordinateGrid[{roboSantaCoordPair}] +=1;
            }
        } 
        if (bSantasTurn)
        {
            std::cout << "Santa's current Coordinates: (" << xSantaPos << ", " << ySantaPos << "). Presents: " << coordinateGrid[{santaCoordPair}] << std::endl;
        }
        else 
        {
            std::cout << "RoboSanta's current Coordinates: (" << xRoboSantaPos << ", " << yRoboSantaPos << "). Presents: " << coordinateGrid[{roboSantaCoordPair}] << std::endl;
        }
        std::cout << "We have visited " << coordinateGrid.size() << " houses." << endl << endl;
    }
    std::cout << endl << coordinateGrid.size() << " total houses.";
    std::cout << endl << coordinateGrid[{0,0}] << " presents at (0,0)";
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

        The correct answer to this puzzle was: 2592 houses.
        The correct answer to part two was 2,360 houses.

 */