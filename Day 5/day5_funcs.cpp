#include <vector>
#include <string>
#include <regex>

using namespace std;

int checkForDoubleLetters(string inputString) {
    int doubleLetterFlag = 0;

    for(string::size_type i=0;i<(inputString.size()-1);++i)
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

    for(string::size_type i = 0; i < inputString.length(); ++i){
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

int checkforDoublePairs(string inputString){
    int doublePairsFlag = 0;

    for (int i=0;i < inputString.length() - 3; ++i){
        char currentLetter = inputString[i];
        char nextLetter = inputString[i+1];

        for (int j=i+2; j <  inputString.length()-1; ++j){
            char secondLetter = inputString[j];
            char nextSecondLetter = inputString[j+1];

            if ((currentLetter == secondLetter) && (nextLetter == nextSecondLetter))
            {
                doublePairsFlag = 1;
            }
        }
    }
    return doublePairsFlag;
}

int checkForXyXFlag(string inputString){
    int XyXFlag = 0;

    //2. Contains at least one letter that repeats with EXACTLY one letter between them xyx (xyx), abcdefeghi (efe), aaa (aaa).
    for (int i=0; i < inputString.size()-2; ++i)
    {
        char currentLetter = inputString[i];
        char thirdLetter = inputString[i+2];
        if (currentLetter == thirdLetter)
        {
            XyXFlag = 1;
        }
    }
    return XyXFlag;
}

int checkForNaughtyPairs(string inputString, vector<regex> badStrings)
{
    int badStringFlag = 0;

    for (vector<regex>::iterator it = badStrings.begin(); it != badStrings.end(); it++) 
    {
        regex badString = *it;
        if (regex_match(inputString, badString)) {
            badStringFlag = 1;
            break;
        }
    }
    return badStringFlag;
}