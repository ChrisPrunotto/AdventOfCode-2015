#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector> 

using namespace std;

int main(){
    ifstream file("input.txt");
    string textLine, delimiter = "x", token;
    int length = 0, width = 0, height = 0, lwSide, whSide, hlSide, smallestSide;
    int delimiterPos, firstXPos, secondXPos;

    int thisBoxWrappingPaper, wrappingPaperTotal = 0, thisBoxRibbon = 0, ribbonTotal = 0;
    int iterator = 0;

    while (getline(file, textLine))
    {
        //debug iterator to count the lines
        iterator++;

        //find the first occurence of the delimiter and tokenize the length
        delimiterPos = textLine.find(delimiter,0);
        token = textLine.substr(0, delimiterPos);
        firstXPos = delimiterPos;
        length = stoi(token,nullptr);
        cout << iterator << ": " << textLine << " first x:" << delimiterPos;

        //find the second occurence and tokenize the width 
        delimiterPos = textLine.find(delimiter,delimiterPos+1);
        secondXPos = delimiterPos;
        token = textLine.substr(firstXPos+1,delimiterPos-firstXPos-1);
        width = stoi(token,nullptr);
        cout << " second x:" << delimiterPos << endl;

        //get the rest of the line and tokenize height
        token = textLine.substr(secondXPos+1);
        height = stoi(token,nullptr);


        cout << "Length: " << length << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;

        //Area Math: 2*l*w + 2*w*h + 2*h*l. + whichever is the smallest of those 3
        lwSide = length*width;
        whSide = width*height;
        hlSide = height*length;
        smallestSide = min({lwSide, whSide, hlSide});
        thisBoxWrappingPaper = ((2*length*width) + (2*width*height) + (2*height*length)) + smallestSide;
        wrappingPaperTotal += thisBoxWrappingPaper;

        cout << "This Box: " << thisBoxWrappingPaper << endl;

        //sort out the sides so that we can work with them in the ribbon math.
        vector<int> sideArray = {length, width, height};
        sort(sideArray.begin(),sideArray.end());
        cout << sideArray[0] << ", " << sideArray[1] << ", " << sideArray[2];

        //Ribbon Math (perimeter) example: 2x3x4 -> 2+2+3+3 = 10 feet for a specific box + the bow, which is the area - 2*3*4
        thisBoxRibbon = sideArray[0] + sideArray[0] + sideArray[1] + sideArray[1];
        thisBoxRibbon += sideArray[0]*sideArray[1]*sideArray[2];

        cout << "This Box's ribbon: " << thisBoxRibbon;
        ribbonTotal += thisBoxRibbon;


    }
    cout << "Total Wrapping Paper Needed: " << wrappingPaperTotal << endl;
    cout << "Total Ribbon Needed: " << ribbonTotal;
}

/*
    What I learned:
        -- Had some practice with getline!
        -- Tokenizing a string is an invaluable skill. I feel like there's a way to simplify what I've done here, without having to create all these extra variables to hold positions I only need once. I should come back to this.
        -- This is the first time I've touched the "algorithm" include - I'm starting to understand that there's a huge pool of stuff out there that I can pull from in the standard libraries. I should be investigating ways of learning more about them.

        -- Avoid shortcutting things. I think this is where the value in refactoring comes. I tried to shortcut the "smallest side" min and didn't realize I was finding the a value twice as large as I should have needed (ie: 2*width*height instead of width*height). Be as verbose as you need to be, then refactor later. You'll create less bugs.

        -- Not code-related, but I've learned that I can create sub-projects within my git repository and Visual Studio deals with that just fine. I don't need a separate repo for every single one of these challenges!

        -- I learned how to quickly sort numbers using std::sort().
        -- Of note, this is one of the first times I haven't had to look up anything more than syntax and functions - I feel like I was able to grok exactly WHAT I needed to do even if I didn't know HOW I needed to do it. I didn't feel the need to try and look up solutions to work out how they could fit into what I was doing.

    The first part of the puzzle's solution is: 1586300
    The second part of the puzzle's solution is: 3737498

 */