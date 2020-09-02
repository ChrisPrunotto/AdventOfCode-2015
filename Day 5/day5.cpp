
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Day5_funcs.h"

using namespace std;

int main(){
    string inputLine;
    ifstream file("input.txt");

    int nice1 = 0; //Part 1 counter
    int nice2 = 0; //Part 2 counter

    vector<regex> badStrings;
    badStrings.push_back(regex("^(.*)(ab)(.*)$")); //regex rules defined by the problem.
    badStrings.push_back(regex("^(.*)(cd)(.*)$")); //regex rules defined by the problem.
    badStrings.push_back(regex("^(.*)(pq)(.*)$")); //regex rules defined by the problem.
    badStrings.push_back(regex("^(.*)(xy)(.*)$")); //regex rules defined by the problem.

    while (getline(file, inputLine))
    {
        std::cout << "Checking...: " << inputLine;

        if ((checkForNaughtyPairs(inputLine, badStrings) == 0) && (checkForDoubleLetters(inputLine) == 1) && (countVowels(inputLine) >= 3) && (checkforDoublePairs(inputLine) == 1) && (checkForXyXFlag(inputLine) == 1))
        {
            ++nice1;
            ++nice2;
            std::cout << " ...Found a VERY Nice string.";
        }
        else if ((checkForNaughtyPairs(inputLine, badStrings) == 0) && (checkForDoubleLetters(inputLine) == 1) && (countVowels(inputLine) >= 3))
        {
            ++nice1;
            std::cout << " ...Found a nice string.";
        }
        else if ((checkforDoublePairs(inputLine) == 1) && (checkForXyXFlag(inputLine) == 1))
        {
            ++nice2;
            std::cout << " ...Found a nice string.";
        }
        else{
            std::cout << " ...Found a naughty string.";
        }
        std::cout << endl;
    }
    std::cout << "\nTotal nice1 strings: " << nice1 << "\nTotal nice2 strings: " << nice2;
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

        -- I used a branch on git to shelve in-progress work for the first time!

        -- While I would have preferred to solve the second half of the problem using regex, because it's a lot more efficient than looping through each individual character, at some point I realized the investment to learn an entirely new way of parsing strings for a single problem was pretty great. The end user does not care what technology use to get there, so long as the final output is correct. That said, I want to learn the fundamentals of regex and will absolutely be coming back to this problem to implement my own solution, and clean this whole problem up.

        -- "std::string_size" and "std::string_length" are the same thing. I didn't know that there were synonym functions in C++! Stylistically, it appears conventional to use size when operating on on containers such as Vectors, Map, etc., especially when working with Template classes and functions. Length is most often used when working upon objects that operate upon strings. Probably best to refer to whatever style guide is being used.

        The puzzle solution to part 1 is 258.
        The puzzle solution to part 2 is 53.

 */