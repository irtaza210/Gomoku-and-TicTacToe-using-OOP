/*

Authors: Aaron Stein, Rain Chen, Irtaza Waseem
Last Edited: 4/10/21 

This file contains the declarations for the GameBase class, which is the base class for TicTacToe and Gomoku. The protected member variables
are declared here inherited by the derived classes. This file also contains the enumeration whoseTurn, which is used to keep track of whose
turn it is.


*/

#pragma once

#include "GameSpace.h"
#include <vector>
#include <utility>
#include <iostream>

enum whoseTurn { firstPlayer = 0 , secondPlayer = 1 };


class GameBase {

public:
	GameBase(unsigned int dimensions, unsigned int winThreshold);			// constructor to initialize parts common to both games

	static GameBase* createGame(int argc, char* argv[]);				// method that takes in command line and returns pointer to game object


	bool done();													// not virtual because we implemented the board size extensible version (works for all games)
	int prompt(unsigned int& col, unsigned int& row);				// no need to declare as virtual (same implementation for both derived classes, should inherit as-is)
	int play();														// no need to declare as virtual (same implementation for both derived classes, should inherit as-is)


	virtual void print() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;

	virtual int doneOutcome() = 0;							// prints message to terminal saying who won, overloaded in derived classes to print customized message

	

protected:
	std::vector<std::vector<gameSpace>> board;									// the board itself
	std::vector<std::pair<unsigned int, unsigned int>> firstPlayerMoves;		// vector to keep track of X moves
	std::vector<std::pair<unsigned int, unsigned int>> secondPlayerMoves;		// vector to keep track of O moves
	whoseTurn whoseTurn;														// keeps track of whose turn it is

	unsigned int longestDisplayLength;
	
	unsigned int winThreshold;

	// the dimensions of the game board
	unsigned int totalWidth;				// total dimensions include a "buffer" around the side that cannot be written to
	unsigned int totalHeight;
	unsigned int playableWidth;				// playable dimensions are the part of the board that pieces can actually be added to
	unsigned int playableHeight;


private:

	// private methods that are helpers to the extensible done() method
	void verticalWinCheck(unsigned int& count, std::string shape, unsigned int colIndex, unsigned int rowIndex);		// vertical check
	void horizontalWinCheck(unsigned int& count, std::string shape, unsigned int colIndex, unsigned int rowIndex); // horizonatal check
	void downDiagonalWinCheck(unsigned int& count, std::string shape, unsigned int colIndex, unsigned int rowIndex);// down diagonal (i.e. top left down to bottom right) check
	void upDiagonalWinCheck(unsigned int& count, std::string shape, unsigned int colIndex, unsigned int rowIndex);	// up diagonal (i.e. bottom left to top right) check


	// method called by prompt() to read in inputs from a string if the user did not input "quit"
	void parseInput(unsigned int& col, unsigned int& row, std::string& inputMove, bool& badInput);


};