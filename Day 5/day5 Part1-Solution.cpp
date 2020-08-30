
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int checkForDoubleLetters(string inputString) {
    int doubleLetterFlag = 0;
    string::size_type inputStringSize = inputString.size(); //what is this??

    for(string::size_type i=0;i<(inputStringSize-1);++i) // ++i vs i++?
    {
        char currLetter = inputString[i];
        char nextLetter = inputString[i+1];
        if (currLetter == nextLetter) {
            doubleLetterFlag = 1;
            break;
        }
    }
    return doubleLetterFlag;
}

int countVowels(string inputString){
    int numVowels = 0;
    string::size_type inputStringSize = inputString.size();

    for(string::size_type i = 0; i < inputStringSize; ++i){
        char letter = inputString[i];

        switch(letter){
            case 'a':
                ++numVowels;
                break;
            case 'e':
                ++numVowels;
                break;
            case 'i':
                ++numVowels;
                break;  
            case 'o':
                ++numVowels;
                break;
            case 'u':
                ++numVowels;
                break;
            default:
                break;
        }
    }
    return numVowels;
}

int main(){
    string inputLine;
    ifstream file("input.txt");

    int nice = 0;

    vector<regex> badStrings;
    badStrings.push_back(regex("^(.*)(ab)(.*)$")); //regex rules defined by the problem.
    badStrings.push_back(regex("^(.*)(cd)(.*)$")); //regex rules defined by the problem.
    badStrings.push_back(regex("^(.*)(pq)(.*)$")); //regex rules defined by the problem.
    badStrings.push_back(regex("^(.*)(xy)(.*)$")); //regex rules defined by the problem.

    while (getline(file, inputLine))
    {
        std::cout << "Checking...: " << inputLine;

        //check for bad strings first
        int badStringFlag = 0;
        for (vector<regex>::iterator it = badStrings.begin(); it != badStrings.end(); it++) {
            regex badString = *it;
            if (regex_match(inputLine, badString)) {
                badStringFlag = 1;
                break;
            }
        }

        if ((badStringFlag == 0) && (checkForDoubleLetters(inputLine) == 1) && (countVowels(inputLine) >= 3))
        {
            std::cout << "...Found a nice string!";
            ++nice;
        }
        else{
            std::cout << " ...Found a naughty string.";
        }
        std::cout << endl;
    }
    std::cout << "Total nice strings: " << nice;
}

/* --- Day 5: Doesn't He Have Intern-Elves For This? ---

    What I learned on this challenge:
        -- Unfortunately, Day 4 had proven to be too much for me, so I've moved on to Day 5 with the intention of circling back to Day 4 later when I'm more comfortable with it.
        -- I was also unsuccessful in finding a solution to this problem myself and more or less copied / derived my solution from this one here, on GitHub: https://github.com/WuSage3/AdventOfCode_2015/blob/master/Day5/Day5_Part1.cpp#L36

        -- In this solution, I've learned a good bit about writing regex and found some tools for testing that and coming up with my own solutions.
        -- I also learned about i++ and ++i. The former is "Post-Increment" and the latter is "Pre-Increment." Normally, this will function exactly the same, however if you're using the i++ or ++i on the same line as you're assigning it, you may run into issues.
            in the case of ++i, the value is incremented and THEN returned.
            in the case of i++, the value is returned and then incremented.
            Even though I've learned (and stylistically prefer) i++ (because it makes more sense to me to see the operand and then the operator), it seems that ++i is actually more preferred.

        -- I leraned that I can write functions in the main cpp file. It's not preferred but for short exercises like this, it's not the end of the world.

        -- The strategy of using "Flags" to identify sub-problems and combine their results is something so silly and easy that I can't believe I didn't think of it myself! I'll be sure to use this approach in the future.

        The puzzle solution is 258.

 */