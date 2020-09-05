#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>

using namespace std;


/*to convert integers to sixteen bit binary, divide by 2 over and over and each time you have a remainder, add a 1. 
Then fill in the remaining bits with zero. It was easier to build the string in reverse!*/
std::string Int_To_Bin(int decimalNumber)
{
    std::string output;

    while (decimalNumber > 0){
        if (decimalNumber % 2 == 0)
        {
            output.insert(0, "0");
        }
        else
        {
            output.insert(0, "1");
        }
        decimalNumber >>= 1;    //this is an interesting operator I learned! It's a right-shift operator! It means to 
                                //shift the bits to the right by one. It's almost the same as dividing by two (however, 
                                //crucially, it can mess with the sign that tells if a number is positive or negative, 
                                //so use with care!!)
    }

    while (output.length()<16)
    {
        output.insert(0,"0");
    }

    return output;
}

std::string BitOp_AND(std::string opA, std::string opB)
{
    int index = 0;
    std::string result;
    for (int index=0; index < 16; index++)
    if ((opA[index] == '1') && (opB[index] == '1')) // It feels a bit like cheating to use the && operator here..
    {
        result.append("1");
    }
    else{
        result.append("0");
    }
    return result;
}

std::string BitOp_OR(std::string opA, std::string opB)
{
    int index = 0;
    std::string result;
    for (int index=0; index < 16; index++)
    if ((opA[index] == '1') || (opB[index] == '1')) // Also still feels like cheating to use the ||. I should come back to these.
    {
        result.append("1");
    }
    else{
        result.append("0");
    }
    return result;
}

std::string BitOp_LSHIFT(std::string opA, int shift){
    std::string result;

    result = opA.substr(2,16);
    result = result.append("00");

    return result;
}

std::string BitOp_RSHIFT(std::string opA, int shift){
    std::string result;

    result = opA.substr(0,14);
    result = result.insert(0,"00");

    return result;
}

std::string BitOp_NOT(std::string opA){
    std::string result;

    for(int i = 0; i<opA.length(); ++i){
        if (opA[i] == '1'){
            result.append("0");
        }
        else if (opA[i] == '0')
        {
            result.append("1");
        }
    }
    return result;
}



//to convert to integer from a binary string, move backward along the string and raise each "1" to the 2nd power.
int Bin_To_Int (std::string binNumber)
{
    int output=0, index=0;
    for (int i=binNumber.length();i>0;--i)
    {
        if(binNumber[i-1] == '1')
        {
            output += pow(2, index);
        }
        index = ++index;
    } 
    return output;
}

int main(){

    ifstream file("input.txt");
    std::string fileLine;
    std::vector<std::string> instructions;

    smatch matches;
    std::vector<smatch> matchVector;

    std::string operand1, gateOperator, operand2, destination; //operator seems to be a reserved keyword. I should investigate that later.

    while (getline(file,fileLine)){
        //instructions.push_back(fileLine);
        regex_search(fileLine, matches, std::regex(R"((\w+)? ?(RSHIFT|LSHIFT|OR|AND|NOT) (\w+)(?: -> )(\w+))"));
        matchVector.push_back(matches);
    }
        /*regex outputs by group:
            0) The overall global match
            1) operand 1. In the case of unary operators this will be undefined.
            2) operator
            3) operand 2. In the case of unary operators, this is the only one that will exist.
            4) destination.
        */
    //regex_search(fileLine, matches, std::regex(R"(([a-z]+)? ?(RSHIFT|LSHIFT|OR|AND|NOT) ?(\S+)(?: -> )(\w+));

    for (int i=0; i<instructions.size(); ++i)
    {
        std::cout << instructions[i] << endl;
        std::cout << matchVector[0][0];
    }
        /*
        //What's working:   
            -- The bit operation processor is working. I just have to convert base 10 digits and feed the arguments in.
            -- the digit conversion is working. I just need to get the inputs to it correctly.
            -- Regex processing of individual lines into matches is working well.

        //What's not working:
            -- The data is not necessarily in the input I would have expected.
            -- What I think I have to do is throw all of the lines into an array, and then start with each desitnation, working backwards until I've traced the beginning of the wire. The technique I'm looking for appears to be called "recursion".
            -- adding "matches" to the MatchVector in the while loop seems to be breaking. It could be that the regex is bad? Maybe consider storing that data in a different way?
        */
    //examples
    std::cout << Int_To_Bin(65535) << endl;
    std::cout << Int_To_Bin(4) << endl;
    std::cout << Int_To_Bin(6) << endl;
    std::cout << Int_To_Bin(8) << endl << "-----" << endl;

    std::cout << Bin_To_Int(Int_To_Bin(65535)) << endl;

    std::cout << Bin_To_Int(BitOp_AND(Int_To_Bin(123), Int_To_Bin(456))) << endl;
    std::cout << Bin_To_Int(BitOp_OR(Int_To_Bin(123), Int_To_Bin(456))) << endl;
    std::cout << Bin_To_Int(BitOp_LSHIFT(Int_To_Bin(123),2)) << endl;
    std::cout << Bin_To_Int(BitOp_RSHIFT(Int_To_Bin(456),2)) << endl;
    std::cout << Bin_To_Int(BitOp_NOT(Int_To_Bin(123))) << endl;
    std::cout << Bin_To_Int(BitOp_NOT(Int_To_Bin(456))) << endl;
    //std::cout << Bin_To_Int(Int_To_Bin(4)) << endl;
    //std::cout << Bin_To_Int(Int_To_Bin(6)) << endl;
    //std::cout << Bin_To_Int(Int_To_Bin(8)) << endl;

}

/* --- Day 7: Some Assembly Required ---

    -- I KNOW I CAN USE REGEX AGAIN!!! All of the identifiers are lowercase letters. All of the operations are capital letters. All of the assignments are "->"!!!!!!
    
    -- I used the math include to gain access to the "pow" function. My "int to bin" function was always a bit off until I realized that I needed to start the index at zero, not 1. Raising things to the power of 0 ALWAYS results in 1!

    -- My understanding of how bitwise operations work has massively improved. I feel like this entire project could be redone down the line to ensure that I don't use the "&&" or "||" operators, but I feel like doing so would probably be a lot more than I can chew at the moment. I also learned about what LSHIFT and RSHIFT operations are, and there are others and also that the often amount, more or less, to dividing and multiplying by two, at least in a base2 system. There are also other operations I learned about - and new operators! - that can perform these operations.

    

This year, Santa brought little Bobby Tables a set of wires and bitwise logic gates! Unfortunately, little Bobby is a little under the recommended age range, and he needs help assembling the circuit.

Each wire has an identifier (some lowercase letters) and can carry a 16-bit signal (a number from 0 to 65535). A signal is provided to each wire by a gate, another wire, or some specific value. Each wire can only get a signal from one source, but can provide its signal to multiple destinations. A gate provides no signal until all of its inputs have a signal.

The included instructions booklet describes how to connect the parts together: x AND y -> z means to connect wires x and y to an AND gate, and then connect its output to wire z.

For example:

    123 -> x means that the signal 123 is provided to wire x.
    x AND y -> z means that the bitwise AND of wire x and wire y is provided to wire z.
    p LSHIFT 2 -> q means that the value from wire p is left-shifted by 2 and then provided to wire q.
    NOT e -> f means that the bitwise complement of the value from wire e is provided to wire f.

Other possible gates include OR (bitwise OR) and RSHIFT (right-shift). If, for some reason, you'd like to emulate the circuit instead, almost all programming languages (for example, C, JavaScript, or Python) provide operators for these gates.

For example, here is a simple circuit:
                     
123 -> x             00000000 01111011
456 -> y             00000001 11001000
x AND y -> d         00000000 01001100 AND (if both "1", it's a 1, if they're not, it's a 0)
x OR y -> e          00000001 11111011 OR (if either operand has a "1" present, the result is 1)
x LSHIFT 2 -> f      00000001 11101100 LSHIFT (Move the numbers to the left by that number of bits, insert ZEROS in the remaining bits.)
y RSHIFT 2 -> g      00000000 01110010 RSHIFT (Move the numbers to the right by that number of bits, insert ZEROS in the remaining bits.)
NOT x -> h           11111111 10000100 NOT (invert)
NOT y -> i           11111110 00110111

After it is run, these are the signals on the wires:

d: 72
e: 507
f: 492
g: 114
h: 65412
i: 65079
x: 123
y: 456

In little Bobby's kit's instructions booklet (provided as your puzzle input), what signal is ultimately provided to wire a?
 */