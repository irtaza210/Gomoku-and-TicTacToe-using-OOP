/*

Authors: Aaron Stein, Rain Chen, Irtaza Waseem
Last Edited: 4/10/21 

This file is the entry-point of the program, it contains the main() method. This file also contains the necessary "try-catch" block
that prevents any exceptions from propogating outside of main(). 


*/

#include <iostream> 
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "mainHeader.h"
#include <new>				// included for use of "bad_alloc" exception, found here: https://www.cplusplus.com/reference/new/bad_alloc/

using namespace std;

int main(int argc, char* argv[]){


	try {															// wrap code that could throw an exception in try-catch block
		GameBase* game_ptr = GameBase::createGame(argc, argv);		// call static method that returns pointer to a derived class of GameBase base class
		if (game_ptr == 0) {										// if method returns a singular pointer, call usageMessage
			return usageMessage(argv[programName], "<game>");
		}
		else {														// if static method returned a valid game, then play the game
			unsigned int playOutcome = game_ptr->play();
			delete game_ptr;										// deallocate dynamic memory to prevent memory leak
			return playOutcome;										// return the value that play() returns
		}
	}
	catch (bad_alloc& ba) {
		cout << "Error: Program ran out of memory" << endl;
		cout << ba.what() << " caught" << endl;					// outputs "bad allocation caught" in the case of bad_alloc
		return insufficientMemory;								// return appropriate failure value 
	}
}


