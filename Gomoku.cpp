/*

Authors: Aaron Stein, Rain Chen, Irtaza Waseem
Last Updated: 4/10/2021


This file contains the function definitions necessary for the GomokuGame class. In particular, it only contains methods that were
implemented differently from TicTacToeGame, including done(), turn(), print(), and draw(). The helper methods specific to draw() 
are also defined here.


*/

#include "Gomoku.h"
#include "mainHeader.h"
#include <iostream>
#include <iomanip>

using namespace std;

// default constructor (constructs GameBase class with standard parameters)
GomokuGame::GomokuGame() : GameBase(19,5) {}

// custom constructor for GomokuGame class (takes in parameters if user supplies extra command line arguments)
GomokuGame::GomokuGame(unsigned int dimensions, unsigned int winThreshold) : GameBase(dimensions, winThreshold) {}


ostream& operator<<(ostream& os, const GomokuGame& game) {
	
	int longestDisplayLength = static_cast<int>(game.longestDisplayLength);
	int displayLengthWithPadding = longestDisplayLength + 1;

	for (int row = game.playableHeight; row > 0; --row) {		// iterate through rows in reverse order
		os << endl;												// new line for each row
		
		os << setw(longestDisplayLength) << left << row;		// left justify the row numbers
		
		os << right;											// right justify everything else

		for (unsigned int col = 1; col <= game.playableWidth; ++col) {
			
		
			os << setw(displayLengthWithPadding) << game.board[col][row].shape;			// print each gameSpace shape on the board with enough space
			
		}
	}

	os << endl << setw(longestDisplayLength) << left << "X" << right;					// for formatting (as shown in instructions)

	for (unsigned int col = 1; col <= game.playableWidth; ++col) {		// print column indices at the bottom
		os << setw(displayLengthWithPadding) << col;
										
	}
	os << endl;

	return os;													// return ostream to allow for chaining insertions
}


void GomokuGame::print() {
	cout << *this;
}


bool GomokuGame::draw() {
	
	if (this->done() == true) {										// if the game has been won, there is no draw
		return false;
	}

	for (unsigned int row = 1; row <= playableHeight; ++row) {		// checks all playable spaces on the board
		for (unsigned int col = 1; col <= playableWidth; ++col) {
			if (board[col][row].couldWin == true) {					// if there is a piece with potential to win
				return false;										// then we keep playing
			}
			
		}
	}

	return true;													// if we find that no gameSpace structs have potential to win, the draw() returns true
}


int GomokuGame::turn() {
	if (this->whoseTurn == firstPlayer) {							// different message based on whose turn it is
		cout << endl << "It is player B's turn" << endl;
	}
	else {
		cout << endl << "It is player W's turn" << endl;
	}


	int promptResult;										// variable to hold return value of prompt()
	unsigned int col;										// col of player's move
	unsigned int row;										// row of player's move


	promptResult = prompt(col, row);						// call prompt() which will return success or quitGame
	if (promptResult == quitGame) {							// if quit, return immediately
		return quitGame;
	}

	// if prompt() return success, then it must have gotten a valid move	
	if (this->whoseTurn == firstPlayer) {															// if it is B's turn
		board[col][row].shape = "B";														// put move on board
		pair<unsigned int, unsigned int> move = make_pair(col, row);						// record the move in BMoves vector
		this->firstPlayerMoves.push_back(move);
	}
	else {
		board[col][row].shape = "W";														// put move on the board
		pair<unsigned int, unsigned int> move = make_pair(col, row);						// record the move in WMoves vector
		this->secondPlayerMoves.push_back(move);
	}


	
	// set couldWin value (will be true if this piece has potential to win)
	board[col][row].couldWin = potentialToWin(col,row,board[col][row].shape);
	// update couldWin of all board pieces around it
	updateCouldWin(col, row);

	

	// print board
	cout << *this;

	// blank line
	cout << endl;

	// printing out past moves
	if (this->whoseTurn == firstPlayer) {
		printBMoves();						// print X moves after B has made its move
	}
	else {
		printWMoves();						// print O moves after W has made its move
	}
	cout << endl;				// for formatting



	// if game was not quit while prompting, then turn() was successful
	return success;
}



// helper method for turn()
void GomokuGame::printBMoves() {
	cout << "Player B: ";
	for (unsigned int moveIndex = 0; moveIndex < firstPlayerMoves.size(); ++moveIndex) {				// iterate through BMoves
		cout << firstPlayerMoves[moveIndex].first << "," << firstPlayerMoves[moveIndex].second;			// print out every move player B has made
		if (moveIndex != firstPlayerMoves.size() - 1) {													// don't print semicolon after last move in vector
			cout << "; ";
		}
	}
}

// helper method for turn()
void GomokuGame::printWMoves() {
	cout << "Player W: ";
	for (unsigned int moveIndex = 0; moveIndex < secondPlayerMoves.size(); ++moveIndex) {				// iterate through WMoves
		cout << secondPlayerMoves[moveIndex].first << "," << secondPlayerMoves[moveIndex].second;		// print out every move player W has made
		if (moveIndex != secondPlayerMoves.size() - 1) {												// don't print semicolon after last move in vector
			cout << "; ";
		}
	}
}

// prints winner of GomokuGame
int GomokuGame::doneOutcome() {
	if (this->whoseTurn == firstPlayer) {
		cout << endl << "B won!" << endl;
	}
	else {
		cout << endl << "W won!" << endl;
	}
	return success;
}


// returns true if there is potential for the piece to win, false otherwise
// "potential" means that if a player had unlimited turns, they could win the game (there are remaining winning combinations of spaces given the current board and winThreshold)
bool GomokuGame::potentialToWin(unsigned int col, unsigned int row, string& shape) {


	string opposingShape;						// string to store shape of opposing shape
	if (shape == "B") {
		opposingShape = "W";
	}
	else if (shape == "W") {
		opposingShape = "B";
	}
	else {							// if we are updating couldWin of a space, then call special method to see if that space has enough spaces in a row around it to lead to a win
		return updateSpacePotential(col,row);
	}



	
	// partialPotential variables hold "part" of a space's potential
	// for example, if we are checking vertically, then one partial holds the up potential, the other partial variable holds the down potential
	unsigned int partialPotential1 = winThreshold;
	unsigned int partialPotential2 = winThreshold;
	
	// check up
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {								// only need to check as far as winThreshold
		if (row + reach > playableHeight || board[col][row + reach].shape == opposingShape) {	// if we hit the edge or an opposing piece,
			partialPotential1 = reach;															// then we have found max potential in that direction
			break;
		}
	}

	// check down
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {								// similar reasoning as above, just downwards
		if (row - reach < 1 || board[col][row - reach].shape == opposingShape) {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {			// if the partials added together minus one are greater than or equal to winThreshold
		return true;															// then the piece does have potential to win
	}

	// reset partials
	partialPotential1 = winThreshold;
	partialPotential2 = winThreshold;

	// check left
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col - reach < 1 || board[col - reach][row].shape == opposingShape) {
			partialPotential1 = reach;
			break;
		}
	}

	// check right
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col + reach > playableWidth || board[col + reach][row].shape == opposingShape) {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}

	// reset partials
	partialPotential1 = winThreshold;
	partialPotential2 = winThreshold;

	// check upleft diagonal
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row + reach > playableHeight || col - reach < 1 || board[col - reach][row + reach].shape == opposingShape) {
			partialPotential1 = reach;
			break;
		}
	}

	// downright diagonal
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row - reach < 1 || col + reach > playableWidth || board[col + reach][row - reach].shape == opposingShape) {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}

	// reset partials
	partialPotential1 = winThreshold;
	partialPotential2 = winThreshold;

	// check upright diagonal
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row + reach > playableHeight || col + reach > playableWidth || board[col + reach][row + reach].shape == opposingShape) {
			partialPotential1 = reach;
			break;
		}
	}

	// downleft diagonal
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row - reach < 1 || col - reach < 1 || board[col - reach][row - reach].shape == opposingShape) {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}

	
	// if we did not find winning potential in any of 4 axes (vertical, horizontal, two diagonals), then this piece does not have win potential
	return false;
}


// returns true if there are enough spaces in a row to win, false otherwise
// this method is very similar to potentialToWin(), it just takes care of special case where we have to check if a space has enough space neighbors in order to lead to win 
// see comments in potentialToWin() for explanation of this logic
bool GomokuGame::updateSpacePotential(unsigned int col, unsigned int row) {

	// similar reasoning as in potentialToWin()
	unsigned int partialPotential1 = winThreshold;
	unsigned int partialPotential2 = winThreshold;

	// check up
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {						// still, only need to check as far as winThreshold
		if (row + reach > playableHeight || board[col][row + reach].shape != " ") {		// if we hit edge of board, or run into ANY piece that is not a space
			partialPotential1 = reach;													// then we've hit potential of a space
			break;
		}
	}

	// check down
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row - reach < 1 || board[col][row - reach].shape != " ") {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}

	partialPotential1 = winThreshold;
	partialPotential2 = winThreshold;

	// check left
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col - reach < 1 || board[col - reach][row].shape != " ") {
			partialPotential1 = reach;
			break;
		}
	}

	// check right
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col + reach > playableWidth || board[col + reach][row].shape != " ") {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}


	partialPotential1 = winThreshold;
	partialPotential2 = winThreshold;

	// check upleft
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row + reach > playableHeight || col - reach < 1 || board[col - reach][row + reach].shape != " ") {
			partialPotential1 = reach;
			break;
		}
	}


	// downright
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row - reach < 1 || col + reach > playableWidth || board[col + reach][row - reach].shape != " ") {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}


	partialPotential1 = winThreshold;
	partialPotential2 = winThreshold;

	// check upright
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row + reach > playableHeight || col + reach > playableWidth || board[col + reach][row + reach].shape != " ") {
			partialPotential1 = reach;
			break;
		}
	}

	// downleft
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row - reach < 1 || col - reach < 1 || board[col - reach][row - reach].shape != " ") {
			partialPotential2 = reach;
			break;
		}
	}

	if (partialPotential1 + partialPotential2 - 1 >= winThreshold) {
		return true;
	}


	return false;
}




//update couldWin of all necessary pieces (call potentialToWin() on all necessary pieces)
void GomokuGame::updateCouldWin(unsigned int& col, unsigned int& row) {

	string shape = board[col][row].shape;
	

	// updates spaces above
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row + reach > playableHeight || board[col][row + reach].shape == shape) {			// if we hit an edge or piece of same shape, then we can stop looking in this direction
			break;
		}
		if (board[col][row + reach].couldWin == true && board[col][row + reach].shape != shape) {		// if we hit piece with different shape and has couldWin of true,
			board[col][row + reach].couldWin = potentialToWin(col, row + reach, board[col][row + reach].shape);		// update it since its couldWin might have changed with new piece on board
		}
	}

	// the other 7 directions are updated very similarly

	// update spaces below
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (row - reach < 1 || board[col][row - reach].shape == shape) {
			break;
		}
		if (board[col][row - reach].couldWin == true && board[col][row - reach].shape != shape) {
			board[col][row - reach].couldWin = potentialToWin(col, row - reach, board[col][row - reach].shape);
		}
	}

	// update spaces to the right
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col + reach > playableWidth || board[col + reach][row].shape == shape) {
			break;
		}
		if (board[col + reach][row].couldWin == true && board[col + reach][row].shape != shape) {
			board[col + reach][row].couldWin = potentialToWin(col + reach, row, board[col + reach][row].shape);
		}
	}
	// update spaces to the left
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col - reach < 1 || board[col - reach][row].shape == shape) {
			break;
		}
		if (board[col - reach][row].couldWin == true && board[col - reach][row].shape != shape) {
			board[col - reach][row].couldWin = potentialToWin(col - reach, row, board[col - reach][row].shape);
		}
	}

	// update spaces to upright
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col + reach > playableWidth || row + reach > playableHeight || board[col + reach][row + reach].shape == shape) {
			break;
		}
		if (board[col + reach][row + reach].couldWin == true && board[col + reach][row + reach].shape != shape) {
			board[col + reach][row + reach].couldWin = potentialToWin(col + reach, row + reach, board[col + reach][row + reach].shape);
		}
	}

	// update spaces to downleft
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col - reach < 1 || row - reach < 1 || board[col - reach][row - reach].shape == shape) {
			break;
		}
		if (board[col - reach][row - reach].couldWin == true && board[col - reach][row - reach].shape != shape) {
			board[col - reach][row - reach].couldWin = potentialToWin(col - reach, row - reach, board[col - reach][row - reach].shape);
		}
	}

	// update spaces to upleft
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col - reach < 1 || row + reach > playableHeight || board[col - reach][row + reach].shape == shape) {
			break;
		}
		if (board[col - reach][row + reach].couldWin == true && board[col - reach][row + reach].shape != shape) {
			board[col - reach][row + reach].couldWin = potentialToWin(col - reach, row + reach, board[col - reach][row + reach].shape);
		}
	}



	// update spaces to downright
	for (unsigned int reach = 1; reach < winThreshold; ++reach) {
		if (col + reach > playableWidth || row - reach < 1 || board[col + reach][row - reach].shape == shape) {
			break;
		}
		if (board[col + reach][row - reach].couldWin == true && board[col + reach][row - reach].shape != shape) {
			board[col + reach][row - reach].couldWin = potentialToWin(col + reach, row - reach, board[col + reach][row - reach].shape);
		}
	}

	
}





