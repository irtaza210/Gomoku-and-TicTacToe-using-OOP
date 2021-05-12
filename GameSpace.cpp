/*
*
* Author: Aaron Stein, Rain Chen, Irtaza Waseem
* Last Edited: 4/10/2021 
* 
* This file contains the constructor for a gameSpace struct. The constructor initializes the representation of the gameSpace
* on the board to be a single space.
*
*/

#include "gameSpace.h"
#include "GameBase.h"


// constructor initializes a space to be represented by a single space and couldWin to be true (couldWin of a piece is updated right after being placed)
gameSpace::gameSpace() : shape(" "), couldWin(true) {}