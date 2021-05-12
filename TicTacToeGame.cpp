/*
*
* Author: Aaron Stein, Rain Chen, Irtaza Waseem
* Last Edited: 4/10/2021
*
* This file contains the majority of the code and logic that implements TicTacToe. This file defines the methods that are
* declared in TicTacToeGame.h, including the insertion operator overloading function (even though it is not within
* TicTacToeGame class). 
*/


#include "TicTacToeGame.h"
#include "mainHeader.h"
#include <iostream>
#include <iomanip>

using namespace std;

// constructor for TicTacToeGame class, initializes default game (3x3 with 3 in a row needed to win)
TicTacToeGame::TicTacToeGame() : GameBase(3,3) {}

 
ostream& operator<<(ostream& os, const TicTacToeGame& game) {
	for (int row = game.totalHeight - 1; row >= 0; --row) {		// iterate through rows in reverse order
		os << endl;												// new line for each row
		os << row;												// prints row number
		for (unsigned int col = 0; col < game.totalWidth; ++col) {
			os << setw(game.longestDisplayLength) << game.board[col][row].shape << " ";			// print each gameSpace shape on the board
		}
	}

	os << endl << " ";											// for formatting


	for (unsigned int col = 0; col < game.totalWidth; ++col) {
		os << setw(game.longestDisplayLength) << col << " ";										// print column indices at the bottom
	}

	os << endl;

	return os;													// return ostream to allow for chaining insertions
}


// instruction #11 says "insert into an ostream", so should this be more general? 
//Rain: It should be ok and instruction said that "define it as simply inserting *this into an ostream (so that it uses the insertion operator described above)"
//      As long as we use the insertion operator. 
void TicTacToeGame::print() {
	cout << *this;
}







bool TicTacToeGame::draw() {

	if (this->done() == true) {										// if the game has been won, there is no draw
		return false;
	}

	for (unsigned int row = 1; row <= playableHeight; ++row) {		// checks if there are moves remaining in the game
		for (unsigned int col = 1; col <= playableWidth; ++col) {
			if (board[col][row].shape == " ") {						// if there are any empty spaces
				return false;										// then moves remain
			}
		}
	}


	// code will only reach here if the game has not been won AND there are no open spaces on the playable board
	return true;
}




int TicTacToeGame::turn() {
	if (this->whoseTurn == firstPlayer) {							// different message based on whose turn it is
		cout << endl << "It is player X's turn" << endl;
	}
	else {
		cout << endl << "It is player O's turn" << endl;
	}


	int promptResult;										// variable to hold return value of prompt()
	unsigned int col;										// col of player's move
	unsigned int row;										// row of player's move


	promptResult = prompt(col, row);						// call prompt() which will return success or quitGame
	if (promptResult == quitGame) {							// if quit, return immediately
		return quitGame;
	}

	// if prompt() return success, then it must have gotten a valid move	
	if (this->whoseTurn == firstPlayer) {															// if it is X's turn
		board[col][row].shape = "X";														// put move on board
		pair<unsigned int, unsigned int> move = make_pair(col, row);						// record the move in xMoves vector
		this->firstPlayerMoves.push_back(move);
	}
	else {
		board[col][row].shape = "O";														// put move on the board
		pair<unsigned int, unsigned int> move = make_pair(col, row);						// record the move in oMoves vector
		this->secondPlayerMoves.push_back(move);
	}

	// print board
	cout << *this;

	// blank line
	cout << endl;

	// printing out past moves
	if (this->whoseTurn == firstPlayer) {
		printXMoves();						// print X moves after X has made its move
	}
	else {
		printOMoves();						// print O moves after O has made its move
	}
	cout << endl;				// for formatting

	// if game was not quit while prompting, then turn() was successful
	return success;
}



// helper method for turn()
void TicTacToeGame::printXMoves() {
	cout << "Player X: ";
	for (unsigned int moveIndex = 0; moveIndex < firstPlayerMoves.size(); ++moveIndex) {				// iterate through xMoves
		cout << firstPlayerMoves[moveIndex].first << "," << firstPlayerMoves[moveIndex].second;					// print out every move player X has made
		if (moveIndex != firstPlayerMoves.size() - 1) {												// don't print semicolon after last move in vector
			cout << "; ";
		}
	}
}

// helper method for turn()
void TicTacToeGame::printOMoves() {
	cout << "Player O: ";
	for (unsigned int moveIndex = 0; moveIndex < secondPlayerMoves.size(); ++moveIndex) {				// iterate through oMoves
		cout << secondPlayerMoves[moveIndex].first << "," << secondPlayerMoves[moveIndex].second;					// print out every move player O has made
		if (moveIndex != secondPlayerMoves.size() - 1) {												// don't print semicolon after last move in vector
			cout << "; ";
		}
	}
}


// prints winner of TicTacToeGame
int TicTacToeGame::doneOutcome() {
	if (this->whoseTurn == firstPlayer) {
		cout << endl << "X won!" << endl;
	}
	else {
		cout << endl << "O won!" << endl;
	}
	return success;
}