/*
*
* Author: Aaron Stein, Rain Chen, Irtaza Waseem
* Last Edited: 4/10/2021 
*
* This file contains the function declarations for utilityFunctions.cpp. It also contains enumerated variables that are relevant to
* the various possible outcomes of the program, the indices of certain inputs within argv[]. 
*
*/


#pragma once
 
#include <string>
#include <iostream>

enum outcomeVals { success = 0 , quitGame = 1 , draw = 2, improperUsage = 3, insufficientMemory = 4 };

enum commandLineProperties { expectedArgsWithDimensionsAndWinthresh = 4, expectedArgsWithDimensions = 3, numExpectedCommandArgs = 2 , whatGame = 1 , programName = 0 };


void lowerCaser(std::string& s);
int usageMessage(std::string nameOfProgram, std::string commandArgExample);	// tells user how to use command line
int drawOutcome(int numTurns);												// prints message to user if game is a draw
int quitOutcome(int numTurns);												// prints message to user if user quits game