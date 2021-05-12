/*
*
* Author: Aaron Stein, Rain Chen, Irtaza Waseem
* Last Edited: 4/10/2021
*
* This file contains the function definitions that correspond to messages that are output to the user when the program ends (except for
* in the case of bad_alloc, which is handled within Lab4.cpp). This includes output messages when the command line is improperly formatted,
* when the game is quit, when the game is a draw. The output message when a game is won is handled in GomokuGame.cpp and TicTacToeGame.cpp
* respectively. 
*
*/


#include "mainHeader.h"

using namespace std;

// method to make all letters in a string lower case
void lowerCaser(string& s) {
    for (char& c : s) {                      // for each character in string
        if (c >= 65 && c <= 90) {            // if that character is an upper-case char
            c += 32;                         // add 32 to char value to turn char into its corresponding lower-case
        }
    }
}


// outputs message to user and returns appropriate failure value if command line arguments are badly formed, explains how to use program
int usageMessage(string nameOfProgram, string commandArgExample) {
    cout << "Error: User must follow format for command line argument given by 'usage' messages below" << endl;
    cout << "There are 3 ways to play this game, follow one of the formats below for correct usage" << endl;
    cout << "<game> should be 'TicTacToe' to play TicTacToe or 'Gomoku' to play gomoku" << endl;
    cout << "\nTo play default games: " << endl;
    cout << "usage1: " << nameOfProgram << " " << commandArgExample << endl;
    cout << "\nTo play custom games (<dimension> must be >= 3 and <winThreshold> must be <= <dimension>): " << endl;
    cout << "usage2: " << nameOfProgram << " Gomoku <dimension>" << endl;
    cout << "usage3: " << nameOfProgram << " Gomoku <dimension> <winThreshold>" << endl;

    return improperUsage; 
}


// outputs message to user and returns appropriate failure value when the game is a draw
int drawOutcome(int numTurns) {
    cout << "The game is a draw! No winning moves remain." << endl;
    cout << numTurns << " turns were played." << endl;

    return draw;
}


// outputs message to the user and returns success when game is quit
int quitOutcome(int numTurns) {
    cout << endl << "The user has quit the game." << endl;
    if (numTurns == 1) {
        cout << numTurns << " turn was played." << endl;
    }
    else {
        cout << numTurns << " turns were played." << endl;
    }
    return quitGame;
}