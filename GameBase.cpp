/*

Authors: Aaron Stein, Rain Chen, Irtaza Waseem
Last Updated: 4/10/2021

This file contains all method definitions relevant to the base class called GameBase.cpp. In particular, prompt(), play(), 
and done() (and all of done()'s 4 helper methods) are defined here, and inherited as-is into the derived classes.


*/

#include "GameBase.h"
#include "mainHeader.h"
#include "TicTacToeGame.h"
#include "Gomoku.h"
#include <sstream>

using namespace std;

// GameBase constructor (first parameter is the dimensions of the board, the second parameter is the winThreshold or number in-a-row needed to win the game)
// totalWidth and totalHeight are 2 larger than playable dimensions in order to always have a "buffer" around the board that cannot be written to
GameBase::GameBase(unsigned int d, unsigned int w) 
	: whoseTurn(firstPlayer), longestDisplayLength(1), winThreshold(w), playableWidth(d), playableHeight(d), totalWidth(d + 2), totalHeight(d + 2)  {
	

	if (d >= 10) {							// if the dimensions are in double digits, adjust longestDisplayLength
		++longestDisplayLength;
	}

	// initializing the board with blank gameSpace structs
	for (unsigned int row = 0; row < totalHeight; ++row) {
		vector<gameSpace> vec;								// pushing back a vector to the vector of vectors of gameSpace structs
		board.push_back(vec);
		for (unsigned int col = 0; col < totalWidth; ++col) {
			gameSpace gs;
			board[row].push_back(gs);						// initalize every spot on board with gameSpace struct
		}
	}
}



int GameBase::prompt(unsigned int& col, unsigned int& row) {

	bool badInput = true;					// boolean to track if input from user is well-formed

	while (badInput) {						// if user has not input a well-formed and valid location, then continue the loop

		cout << "Please enter comma-separated coordinates to make a move or 'quit' to exit the game" << endl;
		cout << "Enter here: ";
		string inputMove = "";				// string to store input from user
		getline(cin, inputMove);			// read whole line into string (see ReadMe.txt for use of getline vs. cin)


		istringstream checkForQuit(inputMove);		// this istringstream is used to check if "quit" was entered
		string maybeQuit;							// string to hold what might be "quit"
		checkForQuit >> maybeQuit;					// extract into maybeQuit


		lowerCaser(maybeQuit);						// takes care of capital inputs
		if (maybeQuit == "quit") {
			return quitGame;						// end program immediately if entered quit
		}

		parseInput(col, row, inputMove, badInput);		// if input was not "quit", call parseInput to see if move on the board is properly formatted/valid


	}

	// if "while" loop makes it here, the both extractions (col and row) were successful and coordinates are in-bounds and space is open
	return success;
}




// helper method for prompt()
// this method sets badInput to true if the input is badly formed or invalid
// this methods set badInput to false if the a valid input was extracted
void GameBase::parseInput(unsigned int& col, unsigned int& row, string& inputMove, bool& badInput) {

	// this block finds where the (first) comma is -- there must be a comma between the coordinates for the input to be valid
	unsigned int whereComma = 0;							// in a valid input, this value will index where the comma is in the input string
	for (char c : inputMove) {								// loop through the input string
		if (isdigit(c) || c == '\t' || c == ' ') {			// if we encounter digit, space, or tab, keep looking for comma
			++whereComma;
		}
		else {												// if we encounter something other than those listed in "if" statement above (including comma), break "for" loop
			break;
		}
	}

	// whereComma now contains location of first comma in inputMove (if there is a comma and there are no other miscellaneous characters in the string)


	if (whereComma == inputMove.length()) {					// if there is no comma at all, whereComma == inputMove.length() will be true
		badInput = true;									// if there is no comma in the input, the input is badly formed, so set badInput to true
		return;												// and return (exit this method)
	}
	string inputMoveWithSpaces;								// string that will be identical to inputMove, except that spaces will be on both sides of the comma
	for (unsigned int i = 0; i < inputMove.length(); ++i) {	// this loop adds spaces on either side of the comma
		if (i == whereComma || i == whereComma + 1) {
			inputMoveWithSpaces += ' ';						// add a space on either side of the comma
		}
		inputMoveWithSpaces += inputMove[i];				// copy inputMove into inputMoveWithSpaces
	}


	istringstream iss(inputMoveWithSpaces);					// initialize input string stream with string that has spaces around the comma

	unsigned int tempCol;										// declare temporary integers to check that input location is valid
	unsigned int tempRow;

	char shouldBeComma;										// we will attempt to extract comma into this char
	string tooMuch;											// if extraction into this string is successful, then there are too many strings on input line, and it is badly formed



	iss >> tempCol;												// read into temporary variable
	if (iss && tempCol >= 1 && tempCol <= playableWidth) {		// checks if move is in-bounds and that extraction was successful
		col = tempCol;											// if in-bounds and successful extraction into int, assign temporary variable to col
	}
	else {
		badInput = true;											// else, set badInput to true so "while" loop in prompt() will ask for another input
		return;
	}


	iss >> shouldBeComma;										// extract into char that should be a comma
	if (iss && shouldBeComma == ',') {							// if char is a comma
		// do nothing
	} 
	else {														// if there is not a comma in this position, then the input is badly formed
		badInput = true;
		return;
	}


	iss >> tempRow;												// same process as for col
	if (iss && tempRow >= 1 && tempRow <= playableHeight) {
		row = tempRow;
	}
	else {
		badInput = true;
		return;
	}

	iss >> tooMuch;												// if there is anything else left to extract
	if (iss) {
		badInput = true;										// then it is badly formed input, so set badInput to true and return to continue "while" loop in prompt()
		return;
	}


	// if code has reached here AND the space is open, then we have extracted a valid input
	if (this->board[col][row].shape == " ") {
		badInput = false;								// set boolean to false to stop the loop since we have extracted valid inputs
		return;
	}
	else {
		badInput = true;								// if space is occupied, input is invalid, so badInput should remain true, and we will ask for another input from user
		return;
	}
}


// generalized done() method, works for any size square board, any size win threshold
// board size extensible version of done() method -- see ReadMe.txt for full description
bool GameBase::done() {

	unsigned int colIndex;											// column index of most recent move
	unsigned int rowIndex;											// row index of most recent move
	if (this->whoseTurn == firstPlayer) {
		colIndex = firstPlayerMoves.back().first;								// if X's turn, get last element in xMoves vector and take its first value of column index
		rowIndex = firstPlayerMoves.back().second;							// same for row index
	}																// the .back() method was obtained from vector's documentation here: https://www.cplusplus.com/reference/vector/vector/back/
	else {
		colIndex = secondPlayerMoves.back().first;								// if O's turn, get last element in oMoves vector and take its first value of column index
		rowIndex = secondPlayerMoves.back().second;							// same for row index
	}

	string shape = board[colIndex][rowIndex].shape;					// get shape (either "X" or "O") of most recent move


	// see ReadMe.txt for explanation of this extensible version of done()
	unsigned int verticalStraight = 1;	  // counts how many consecutive vertical pieces
	if (shape == board[colIndex][rowIndex + 1].shape || shape == board[colIndex][rowIndex - 1].shape) {		// if there is a matching piece above or below most recently placed piece
		verticalWinCheck(verticalStraight, shape, colIndex, rowIndex);										// check for vertical win
	}
	unsigned int horizontalStraight = 1;  // counts how many consecutive horizonal pieces
	if (shape == board[colIndex + 1][rowIndex].shape || shape == board[colIndex - 1][rowIndex].shape) {		// if there is a matching piece right or left of most recently placed piece
		horizontalWinCheck(horizontalStraight, shape, colIndex, rowIndex);									// check for horizontal win
	}
	unsigned int downDiagonalStraight = 1;		// counts how many consecutive pieces along diagonal from top left to bottom right
	if (shape == board[colIndex + 1][rowIndex - 1].shape || shape == board[colIndex - 1][rowIndex + 1].shape) {		// checks for matching piece along "down diagonal"
		downDiagonalWinCheck(downDiagonalStraight, shape, colIndex, rowIndex);										// check for down diagonal win
	}
	unsigned int upDiagonalStraight = 1;		// counts how many consecutive pieces along diagonal from bottom left to top right
	if (shape == board[colIndex + 1][rowIndex + 1].shape || shape == board[colIndex - 1][rowIndex - 1].shape) {		// checks for matching piece along "up diagonal"
		upDiagonalWinCheck(upDiagonalStraight, shape, colIndex, rowIndex);											// check for up diagonal win
	}

	// if there are enough consecutive pieces in a row of same shape in any direction, then game has been won, else no winner
	if (verticalStraight >= winThreshold || horizontalStraight >= winThreshold || downDiagonalStraight >= winThreshold || upDiagonalStraight >= winThreshold) {
		return true;
	}
	else {
		return false;
	}
}




// these next four methods function in the same way -- see ReadMe.txt "Exensibility" section for full explanation
void GameBase::verticalWinCheck(unsigned int& count, string shape, unsigned int colIndex, unsigned int rowIndex) {
	unsigned int reach = 1;												// variable to "reach" further out in board
	while (shape == board[colIndex][rowIndex + reach].shape) {			// check above
		++count;
		++reach;
	}
	reach = 1;															// reset reach
	while (shape == board[colIndex][rowIndex - reach].shape) {			// check below
		++count;
		++reach;
	}
}

void GameBase::horizontalWinCheck(unsigned int& count, string shape, unsigned int colIndex, unsigned int rowIndex) {
	unsigned int reach = 1;
	while (shape == board[colIndex + reach][rowIndex].shape) {			// check to the right
		++count;
		++reach;
	}
	reach = 1;															// reset reach
	while (shape == board[colIndex - reach][rowIndex].shape) {			// check to the left
		++count;
		++reach;
	}
}

void GameBase::downDiagonalWinCheck(unsigned int& count, string shape, unsigned int colIndex, unsigned int rowIndex) {
	unsigned int reach = 1;
	while (shape == board[colIndex + reach][rowIndex - reach].shape) {		// check lower right bordering piece
		++count;
		++reach;
	}
	reach = 1;																// reset reach
	while (shape == board[colIndex - reach][rowIndex + reach].shape) {		// check upper left bordering piece
		++count;
		++reach;
	}
}

void GameBase::upDiagonalWinCheck(unsigned int& count, string shape, unsigned int colIndex, unsigned int rowIndex) {
	unsigned int reach = 1;
	while (shape == board[colIndex + reach][rowIndex + reach].shape) {		// check upper right bordering piece
		++count;
		++reach;
	}
	reach = 1;																// reset reach
	while (shape == board[colIndex - reach][rowIndex - reach].shape) {		// check lower left bordering piece
		++count;
		++reach;
	}
}




int GameBase::play() {

	// printing initial board
	print();

	int turnOutcome;							// variable to store outcome of calling turn() -- either success or quit


	while (true) {								// no stop condition needed, the "return" statements inside "while" loop will terminate loop when needed
		turnOutcome = turn();
		if (turnOutcome == quitGame) {							// if user asked to quit
			return quitOutcome(firstPlayerMoves.size() + secondPlayerMoves.size());	// firstPlayerMoves.size() + secondPlayerMoves.size() gives total number of turns played
		}														// call method to tell user "quit" has been input and return appropriate failure code


		if (done()) {							// if game has been won
			return this->doneOutcome();			// call appropriate doneOutcome() implementation (defined within each derived class)
		}

		if (draw()) {											// if game is a draw
			return drawOutcome(firstPlayerMoves.size() + secondPlayerMoves.size());	// firstPlayerMoves.size() + seconPlayerMoves.size() gives total number of turns played
		}														// output message saying game is a tie and return appropriate failure code



		//switch whose turn it is
		if (this->whoseTurn == firstPlayer) {
			this->whoseTurn = secondPlayer;
		}
		else {
			this->whoseTurn = firstPlayer;
		}
	}

	// this will never actually be reached since "return" must come from inside "while" loop above
	return success;
}


GameBase* GameBase::createGame(int argc, char* argv[]) {
	
	if (argc == numExpectedCommandArgs) {					// if user calls default Gomoku or TicTacToe

		// get the name of the game from command line and lowercase it
		string game = argv[whatGame];
		lowerCaser(game);

		if (game == "tictactoe") {
			return new TicTacToeGame();		// default constructs TicTacToeGame with proper dimensions and 
		}
		else if (game == "gomoku") {
			return new GomokuGame();		// call GomokuGame default constructor ("default" parameters of 19x19 board, winThreshold of 5)
		} 
	}
	else if (argc == expectedArgsWithDimensions) {	// else, if user passes in 3 command line arguments (to specify dimensions)
		string game = argv[whatGame];
		lowerCaser(game);

		if (game != "gomoku") {						// must be a custom GomokuGame
			return 0;
		}
		
		
		string input;
		for (int i = 0; i < argc; ++i) {			// putting command line args into a single string so that they can be extracted into proper data types
			input += static_cast<string>(argv[i]);
			input += " ";
		}
		istringstream iss(input);					// initialize input string stream with command line arguments
		
		// these two are dummy variables, the program name and name of game must have already been correct to get here
		string program;
		iss >> program;							
		string gameName;
		iss >> gameName;

		

		unsigned int dimensions;				// unsigned int to store custom dimensions
		iss >> dimensions;						// read into unsigned int
		if (!iss || dimensions > 99) {			// if extraction failed or board is too big
			return 0;							// return singular pointer
		}

	

		if (dimensions < 5 && dimensions >= 3) {		// if dimensions are 3 or 4, then construct GomokuGame with dimensions and dimensions as winThreshold
			return new GomokuGame(dimensions, dimensions);
		}
		else if (dimensions >= 5) {							// extra credit: if dimensions are greater than or equal to 5 and only 1 extra argument passed, then
			return new GomokuGame(dimensions, 5);			// automatically set winThreshold to 5
		}
		else {
			return 0;
		}
	}
	else if (argc == expectedArgsWithDimensionsAndWinthresh) {		// if user passed in 2 extra command line args
		string game = argv[whatGame];
		lowerCaser(game);

		if (game != "gomoku") {					// must be a GomokuGame
			return 0;	
		}

		string input;				
		for (int i = 0; i < argc; ++i) {
			input += static_cast<string>(argv[i]);		// copy command line into string
			input += " ";
		}
		istringstream iss(input);						// initialize input string stream with command line

		// these two are dummy variables, the program name and name of game must have already been correct to get here
		string program;
		iss >> program;
		string gameName;
		iss >> gameName;


		unsigned int dimensions;
		iss >> dimensions;
		if (!iss || dimensions < 3 || dimensions > 99) {		// if extraction was unsuccessful, or dimensions are too small or too big
			return 0;											// return singular pointer
		}
		

		unsigned int winThreshold;								
		iss >> winThreshold;									// extract winThreshold from command line
		if (!iss) {												// if extraction was unsuccessful
			return 0;											// return singular pointer
		}
		

		if (dimensions >= winThreshold) {						// make sure that dimensions are greater than or equal to winThreshold
			return new GomokuGame(dimensions, winThreshold);	// return pointer to specified GomokuGame after constructing it with custom constructor
		}
		else {													// else, return a singular pointer
			return 0;
		}
	}

							// the code will reach here if number of command line arguments is not 2, 3, or 4
	return 0;				// return singular pointer (0 is NOT a success value in this situation)
	
}



