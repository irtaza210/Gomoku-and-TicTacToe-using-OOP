/*

Authors: Aaron Stein, Rain Chen, Irtaza Waseem
Last Updated: 4/10/2021

This file contains all declarations and necessary member variables for the GomokuGame class, which is derived from the GameBase
class. In order to implement the extra credit, this class has two constructors, the defaul one that sets the board to be 19x19
with 5 in-a-row needed to win, and another constructor that takes two unsigned integers and constructs the board with custom  
dimensions and win threshold.

*/


#pragma once

#include "GameBase.h"
#include <string>


class GomokuGame : public GameBase {

	friend std::ostream& operator<<(std::ostream& os, const GomokuGame& game);	// giving operator overloading function access to private class members

public:

	GomokuGame();															// default constructor
	GomokuGame(unsigned int dimensions, unsigned int winThreshold);			// custom GomokuGame constructor


	virtual bool draw() override;											// checks if there are possible moves remaining
	virtual int turn() override;											// calls prompt(), puts move on board, and prints current board and past moves


private:

	// can be private since should only be able to be called by pointer to GomokuGame (statically typed as GameBase*)
	virtual void print() override;

	// private methods that print out all of B's and W's valid moves made
	void printBMoves();
	void printWMoves();

	// prints winner of Gomoku game
	virtual int doneOutcome() override;


	// helper methods for draw() method for GomokuGame
	bool potentialToWin(unsigned int col, unsigned int row, std::string& shape);
	void updateCouldWin(unsigned int& col, unsigned int& row);
	bool updateSpacePotential(unsigned int col, unsigned int row);


};

// overloaded insertion operator for GomokuGame
std::ostream& operator<<(std::ostream& os, const GomokuGame& game);
