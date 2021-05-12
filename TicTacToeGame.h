/*
*
* Author: Aaron Stein, Rain Chen, Irtaza Waseem
* Last Edited: 4/10/2021
*
* This file contains all declarations for the TicTacToeGame class and a declaration for the overloaded insertion operator.
* This implementation is nearly identical to Lab3. The code was just refactored to be a derived class of the more generic 
* GameBase class.
*/


#pragma once
 
#include "GameBase.h"

class TicTacToeGame : public GameBase {

	friend std::ostream& operator<<(std::ostream& os, const TicTacToeGame& game);	// giving operator overloading function access to private class members

public:

	TicTacToeGame();											// default constructor (3x3 board with winThreshold of 3)
	
	virtual bool draw() override;										// checks if there are possible moves remaining
	virtual int turn() override;											// calls prompt(), puts move on board, and prints current board and past moves

private:

	// can be private since should only be able to be called by pointer to TicTacToeGame (statically typed as GameBase*)
	virtual void print() override;

	// private methods that print out all of X's and O's valid moves made
	void printXMoves();
	void printOMoves();

	// method that prints winner of TicTacToeGame
	virtual int doneOutcome() override;
	
};

// overloaded insertion operator for TicTacToeGame
std::ostream& operator<<(std::ostream& os, const TicTacToeGame& game);
