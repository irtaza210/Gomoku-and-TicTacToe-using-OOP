/*
*
* Author: Aaron Stein, Rain Chen, Irtaza Waseem
* Last Edited: 4/10/2021
*
* This file is the header file for the gameSpace.cpp file. This header declares the gameSpace struct. 
*/

#pragma once

#include <string>

struct gameSpace {
	gameSpace();			// basic constructor
	std::string shape;		// initialized to " ", spaces within playable dimensions can be set to X or O
	bool couldWin;			// boolean that tracks if that space could lead to a winning combination
							// for a space that has had a piece placed on it, couldWin being true means that that particular piece could possibly be part of a winning combination
							// for a blank space, couldWin being true means that that space is part of a group of empty spaces that is large enough to lead to a win



};
