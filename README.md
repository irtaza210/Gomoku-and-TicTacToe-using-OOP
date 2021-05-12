A program that allows users to play the popular board games Gomoku and Tic-Tac-Toe and is built using Object Oriented Programming concepts such as inheritcance, polymorphism, refactoring and specializing in C++
=======================================================
This is a project I did with my friends Aaron Stein and Rain Chen

Authors: Irtaza Waseem, Aaron Stein, Rain Chen

Overview:

This program allows 2 users to play tic-tac-toe or gomoku with one another. The game starts by printing out the initial board, which includes
a "frame" around it (a border around the playable part of the board that pieces cannot be added to). After each turn, the program
prints an updated version of the board, and then prints all of the valid moves that the player who just went has taken so far. If the
game is a draw, the program prints how many turns were played and tells the user the game is a draw. If the user quits, the program
also prints out how many moves were played and tells the user that the game ended by quitting. If the game is won by either X or O (B or W), then
the program prints out a message indicating the winner (does not print out the number of turns that were played).

Instructions for operating the program are explained in messages output to the user. If an input space is invalid (either out-of-bounds or
not an open space on the board), the program will simply prompt the user again and again until it obtains a valid input or "quit" is entered.

For clarification, a single "turn" here is defined as a single players move, not both players taking a turn. For example, if X makes a move,
then O, then X again, then O again, that counts as a total of 4 turns, not 2. Therefore, for 3x3 Tic tac Toe, the maximum number of turns is 9. For 19x19
gomoku, the maximum number of turns is 361.

X (B in gomoku) always takes the first turn.

There is GameBase class as the base class of tic-tac-toe and gomoku. It has print(), turn(), and draw() as pure virtual functions so tic-tac-toe and 
gomoku can override those functions. 

To make a move, this program accepts inputs of the form: <col>,<row>
For example, to place a piece at column 2, row 3, the input should be: "2,3"
To quit, the input should be (not case sensitive): "quit"
As explained later, this code does tolerate extra whitespace before and after <col>, <row>, and the comma, but other characters are not tolerated.

Throughout this ReadMe and in code, I use the term "shape" to refer to how a gamePiece looks when it is displayed on the board.




*******************************************************
Possible Return Values from main():

0 -- Program completed successfully, either X or O (B or W in gomokuGame) won the game
1 -- User input "quit" and game was ended
2 -- The game ended because no more valid moves could be made
3 -- Improper usage of program (badly formed input command line)
4 -- Indicates that the program ran out of memory


*******************************************************
Enumerations:

In mainHeader.h
-------------------------------------------------------
"programName": enumerated as 0, used to index name of program within argv[]
"whatGame": enumerated as 1, used to index name of game within argv[]
"numExpectedCommandArgs": enumerated as 2, used to check that argc is correct for a given command line input
“expectedArgsWithDimensions”: enumerated as 3, indicates that the user has passed in 3 command line arguments (part of extra credit)
“expectedArgsWithDimensionsAndWinthresh”: enumerated as 4, used to check if user input 2 extra command line arguments, one for dimension and one for winThreshold (part of extra credit)
"success": enumerated as 0, used to check if the method returned successfully
"quitGame": enumerated as 1, used to check whether user quit the game
"draw": enumerated as 2, used to check if the game final output is a draw or not
"improperUsage": enumerated as 3, used to check if the user follow the format of the command line argument
“insufficientMemory”: enumerated as 4, indicates that the program ran out of memory when allocating in the heap

In GameBase.h
-------------------------------------------------------
"firstPlayer": enumerated as 0 to record the first player
"secondPlayer": enumerated as 1 to record the second player


*******************************************************
Structure of Files:

The entry-point to the program is the main() method, which is located in Lab4.cpp. main() checks that the command line itself is valid, and 
then calls the play() method of the TicTacToeGame class or the Gomoku class depending on the command line input.
 
The much of the logic that actually implements the TicTacToe game is found within TicTacToeGame.cpp, which contains all the function definitions
relevant to the TicTacToeGame class. TicTacToeGame.h contains all the relevant declarations for these methods as well as useful enumerations
that are used in TicTacToeGame.cpp. TicTacToeGame.cpp also contains the function definition for the overloaded insertion operator that is used
to display the current state of the board.

The much of the logic that actually implements the Gomoku game is found within Gomoku.cpp, which contains all the function definitions
relevant to the Gomoku class. Gomoku.h contains all the relevant declarations for these methods as well as useful enumerations
that are used in Gomoku.cpp. Gomoku.cpp also contains the function definition for the overloaded insertion operator that is used
to display the current state of the board.

GameBase.cpp contains methods that are common to both TicTacToeGame and GomokuGame. Methods such as done(), prompt(), and play() are inherited as-is into
the derived classes of GameBase.
 
One particular design choice was the creation of the gameSpace struct, which is declared in gameSpace.h and defined in gameSpace.cpp. The declaration
and definition are very simple, but it helps achieve some useful abstraction in the code. Instead of the board being composed of some collection of 
X's, O's, B’s, W’s, and spaces, the gameSpace struct has a "shape" field that represents how the piece appears on the board. Thus, each space has and 
remembers its own "state", which is a useful way of thinking about the board instead of each space simply being a character or string. The gameSpace 
struct also keeps track of if that particular space can lead to win (used for implementing draw() method in GomokuGame()). 
 
mainHeader.h contains all function declarations for utilityFunctions.cpp, as well as enumerations relating to return values from main() and useful enumerations
for checking that a command line is properly formed. 
 
utilityFunctions.cpp is a source file created to contain various functions that are not necessarily essential to the direct functioning of the TicTacToeGame 
and Gomoku class. For example, it contains the lowerCaser() method, that takes a reference to a string and lower cases all of its characters. This method 
is used to allow the program to tolerate input strings with capital letters in any position. This source file also contains method definitions that
are called when the program terminates, either successfully or with an error.




*******************************************************
Structure of Methods:

For the most part, the methods implemented in this program follow the given instructions. However, there were a couple of new methods and modifications that 
will be explained here.
 
The prompt() method is responsible for checking that an input is valid in every way. This includes checking that an input is within the bounds of the 
playable board, that the input is well formed (two comma-separated integers), and that the requested move corresponds to a space that is open on the board. 
See comments next to prompt() method in GameBase.cpp for more details on how these checks are done. A helper method for prompt(), called parseInput(),
was created to reduce the amount of clutter within prompt() itself. parseInput() is called on an input when it has been determined that the user did not input 
"quit." This method takes two references to unsigned integers (column and row indices), a reference to a string that holds the user's input, and a reference 
to a boolean (bool& badInput) that is set to true when the input does not adhere to the given guidelines and is set to false if the input was valid and was 
successfully read by the program. These guidelines for what an input should look like are further discussed in the "Functional Decisions" section of this ReadMe.
 
As mentioned above, lowerCaser() (which was taken from Lab 2) is used in this program so that the program can tolerate capital letters as inputs. This method
is used on the command line (so that any letter in "tictactoe" can be upper or lower case) and also when checking whether or not the user has asked to quit (so
the "quit" command from the user is also not case-sensitive).
 
The only method that is associated with the gameSpace struct is a simple constructor that initializes every gameSpace object's shape on the board to be a 
single space and makes the couldWin field of every gameSpace “true.”
 
The GameBase class has a constructor that takes in two unsigned integers, the first decides the dimensions of the board, and the second decides the
winThreshold (or number in-a-row needed to win the game). The constructors for TicTacToeGame and GomokuGame each call this constructor for the base class 
differently depending on what the desired board is. This constructor is also what initializes whose turn it is when the game starts, which is set to be
X's turn first in TicTacToe and B’s turn first in Gomoku.
 
Within utilityFunctions.cpp, there are two methods called drawOutcome() and quitOutcome(). These are called by GameBase::play() whenever 
appropriate in order to print out the right message to the user with all the information specified in the instructions. These methods were created just to support
some modularization and keep some of the messages to the user out of the way of the logical code. drawOutcome() and quitOutcome() take an integer that represents
the number of moves played in the game so that this information can be printed to the user. For this implementation, doneOutcome() was actually declared as pure
virtual in the base class, and was overridden within each of the derived classes to have a customized message when a player wins in either game.
 
In order to implement the "extensibility" of this program to larger boards, four helper methods were created that help the done() method recognize when the game 
has been won. Together, these 4 methods are capable of checking in all 8 directions around a piece that has just been placed to see if that piece has any bordering 
pieces that are of the same shape. These 4 methods are called verticalWinCheck(), horizontalWinCheck(), downDiagonalWinCheck(), and upDiagonalWinCheck(). Here, 
"up diagonal" and "down diagonal" are used to indicate which of the two diagonals the method is checking. The terminology assumes left-to-right thinking. For example,
down diagonal means the diagonal that starts in the upper left, and moves "down" towards the lower right as we move rightwards across the board. See "Extra Credit"
section below for the rationale behind these helper methods.

Some more methods implemented here that were not specified in the instructions are printXMoves() and printOMoves() for TicTacToe and printBMoves() and 
printWMoves() for Gomoku. These methods are used to print out all the past valid moves made by a player. Again, these methods are just used to abstract
some of the print statements and logic away from the functions that contain large blocks of logic.

The GomokuGame class contains another three methods that serve to maintain the couldWin field within the gameSpace struct. These are potentialToWin(), updateCouldWin(), 
and updateSpacePotential(). As explained in comments in the code, these methods are used to check whether or not a single space could lead to a win, and update the 
couldWin within each struct accordingly.

Technical note: If a piece has been placed on a space, then that space’s couldWin is true if that particular space could lead to a win (it has enough adjacent 
blank spaces or spaces of the same player next to it so that it could reach the winThreshold). The couldWin of a blank space is defined somewhat differently. 
The couldWin of a space is only true if that space has enough blank spaces adjacent to it to lead to a win. The difference is that couldWin of a space takes into
account blank spaces, but the couldWin of a blank space ONLY counts other blank spaces when calculating if it is possible for that space to lead to a win.



*******************************************************
Functional Decisions:

The instructions gave this implementation discretion on exactly how to handle inputs from the user. In this particular implementation, valid board moves must come
in the form <column>,<row>. However, the logic of prompt() and parseInput() intentionally allow some slight variations on this form. This program is implemented
to handle excess whitespace from the user input. For example, the input is "                     1 ,    2  " is still recognized as a valid input because it technically
is a pair of comma-separated integers. The code does not tolerate any other characters, however. For example, while "1,2 " is accepted as input, "1,2 abc" is not 
accepted as input. As long as the input is a pair of comma separated integers that are within the bounds of the playable dimensions and is a free space on the board, 
the input will be regarded as valid regardless of spaces or tabs within the input. The comma must be present.  
The same reasoning above applies to the "quit" command. Extra whitespace is tolerated in the input as long as "quit" is the only string present in the user input.
For example, "quit                  " causes the game to quit, but "quit               extra123" is regarded as invalid input.
 
By using the lowerCaser() method, this program is able to tolerate upper case letters, both in the "quit" command and in the second argument of the command line.
Therefore, if the case of any character within "TicTacToe" and “Gomoku” is wrong, or the case of any character in "quit" is wrong, they are still recognized as their
respective proper inputs.
 
Pressing the "enter" key is regarded as an invalid input and causes the program to ask for another input.

As specified on Piazza (post @319), we do not have to change how TicTacToe detects a draw. Therefore, draw() only returns true for TicTacToe when the
board is full, but the logic implemented in the GomokuGame version of draw allows for a draw to be called before the board has been completely filled.



*******************************************************
Design Decisions:

This section explains the rationale behind some of the design decisions that were used to implement this program.
The GameBase is the base class. 
 
The construction of the game (i.e. initializing the pointer to the GameBase class) and the running of the play() method are all wrapped in a single 
try-catch block that catches bad allocation. Given the size of this program, it seems quite unlikely that this feature will be needed, but it is added
inside main() in Lab4.cppjust in case because we do not want the exception to propagate outside of main(). Instead, it is better to simply notify the
user that the programran out of memory so that they can possibly decrease the size of the board or figure out what could have caused the program to use
too much memory.

While it was not specified, we thought we might as well also print out the past moves for each player in gomoku, very similar to how it was done for tictactoe.
 
The instructions give the option of either using non-zero return values or a thrown exception in order to implement the quit function of the game.
This implementation uses a non-zero return value, which percolates through the methods as soon as the input is received and eventually causes main()
to return with the same non-zero value.
 
The board, which is a protected member variable of the GameBase class, is implemented as a vector of vectors of gameSpace structs (or a 2D vector
of gameSpace structs). This made thinking about positioning on the board much easier because it eliminates the need for a function that maps coordinates
to an index in a 1D vector (as done in Lab 2). This 2D vector of gameSpace structs is initialized in the constructor for the TicTacToeGame class.
 
Another design decision was the use of two vectors of pairs, one vector storing X's moves and the other storing O's moves for TicTacToe and storing B's 
moves and the other storing W's moves for Gomoku. The vectors are of type vector<pair<unsigned int,unsigned int>>. These members are protected in the 
GameBase class. When X or O (TicTacToe) or B or W (Gomoku) makes a valid move, this move is recorded in the proper vector as a pair of unsigned integers. 
The first element in the pair holds the column index of the move, and the second element in the pair holds the row index of the move. This implementation 
is very useful because it holds the pairs in sequential order, so they can be printed out in the same order that the moves were made. Having the moves
in this form also makes counting the total number of valid moves made so far very easy. The total number of moves is always just the sum of the size of 
the two vectors (firstPlayerMoves.size() + secondPlayerMoves.size()). Also, this structure makes implementing the extensibility of the program
simpler since it gives access to the most recent move made.
 
The GameBase class also has a protected member variable of type "whoseTurn" which is an enumerated variable that can either be firstPlayer or secondPlayer. This member
variable keeps track of whose turn it currently is. The play() method switches whose turn it is at the end of every turn.

For the draw() method in Gomoku.h we designed it as a smart draw method which means it will call a draw if there’s no possibility for both B or W to win in
the game even if there are still remaining moves for B or W. We tested it as a 6 by 6 board since it is hard to test the draw case in the 19 by 19 board.
See the extra credit section of this ReadMe for testing examples.

In the prompt() method, the getline() method is used to extract data from the cin input stream. getline() is used here instead of simply extracting from cin 
(i.e. doing cin >> some_string_variable) because this extraction stops when it hits spaces. Therefore, if the user input something like "2 2", the extraction
would only obtain that first "2." The program would properly recognize this input as badly formed, and as a result, prompt the user for another input. The
problem is that the second "2" (the one that was not extracted), is still lingering in the input stream. Clearly, this can cause problems when performing
another extraction. Therefore, getline() is used in order to clear the input stream after an extraction occurs, so that if the extracted input is not valid,
the next extraction occurs from a clean input stream.


*******************************************************
Warnings/Errors Encountered:

No errors were encountered upon building this program.
The only warning encountered was:

Warning	C26812	The enum type 'whoseTurn' is unscoped. Prefer 'enum class' over 'enum'

However, as stated on the course Piazza page (post @83), it is okay to ignore this specific warning.


*******************************************************
Test Cases:

We ran 21 test cases. All 20 test cases passed.
Test 1: Only 1 command line argument 
Test 2: 2 command line arguments but argument 2 is incorrect
Test 3: 3 command line arguments
Test 4: (TicTacToe) input coordinates out of bounds of the board
Test 5: (TicTacToe) input coordinates have already been played
Test 6: (TicTacToe) Correct coordinates are input but then user adds extra characters in their input
Test 7: (TicTacToe) Two correct coordinates are input but they're input in the same turn
Test 8: (TicTacToe) Playing for a vertical win
Test 9: (TicTacToe) Playing for a horizontal win
Test 10: (TicTacToe) Playing for a diagonal win
Test 11: (Gomoku) input coordinates have already been played
Test 12: (Gomoku) input coordinates are not in the correct format
Test 13: (Gomoku) input coordinates are correct but user inputs extra stuff in input string making the input invalid
Test 14:(Gomoku) User inputs two correct coordinates but in the same turn.
Test 15: (Gomoku) User inputs coordinates out of bounds of Gomoku board
Test 16:(Gomoku) Testing for a diagonal win
Test 17: (Gomoku) Testing for a vertical win
Test 18: (Gomoku) Testing for a horizontal win
Test 19: (TicTcaToe) Playing for a draw
Test 20: (Gomoku) Playing for a draw in 6*6 board, since it is really time-consuming to test 19*19 board.
Test 21: Testing quit


Test 1: Only 1 command line argument 

H:\cse332\lab4\Lab4\Debug>Lab4.exe
Error: User must follow format for command line argument given by 'usage' messages below
There are 3 ways to play this game, follow one of the formats below for correct usage
<game> should be 'TicTacToe' to play TicTacToe or 'Gomoku' to play gomoku

To play default games:
usage1: Lab4.exe <game>

To play custom games (<dimension> must be >= 3 and <winThreshold> must be <= <dimension>):
usage2: Lab4.exe Gomoku <dimension>
usage3: Lab4.exe Gomoku <dimension> <winThreshold>

Program gives error because we need 2 command line arguments echo %errorlevel% returned 3. Test 1 passes.

Test 2: 2 command line arguments but argument 2 is incorrect

H:\cse332\lab4\Lab4\Debug>Lab4.exe hahahah
Error: User must follow format for command line argument given by 'usage' messages below
There are 3 ways to play this game, follow one of the formats below for correct usage
<game> should be 'TicTacToe' to play TicTacToe or 'Gomoku' to play gomoku

To play default games:
usage1: Lab4.exe <game>

To play custom games (<dimension> must be >= 3 and <winThreshold> must be <= <dimension>):
usage2: Lab4.exe Gomoku <dimension>
usage3: Lab4.exe Gomoku <dimension> <winThreshold>

Program gives error because we need 2nd command line argument should be TicTacToe or Gomoku. echo %errorlevel% returned 3. Test 2 passes.

Test 3: 3 command line arguments

H:\cse332\lab4\Lab4\Debug>Lab4.exe TicTacToe hahahaha
Error: User must follow format for command line argument given by 'usage' messages below
There are 3 ways to play this game, follow one of the formats below for correct usage
<game> should be 'TicTacToe' to play TicTacToe or 'Gomoku' to play gomoku

To play default games:
usage1: Lab4.exe <game>

To play custom games (<dimension> must be >= 3 and <winThreshold> must be <= <dimension>):
usage2: Lab4.exe Gomoku <dimension>
usage3: Lab4.exe Gomoku <dimension> <winThreshold>

Even though first 2 arguments are correct, program gives error because we can't have more than 2 command line arguments (besides valid
arguments as specified in the Extra Credit section). echo %errorlevel% returned 3. Test 3 passes.

Test 4: TicTacToe input coordinates out of bounds of the board

H:\cse332\lab4\Lab4\Debug>Lab4.exe TicTacToe

4
3
2
1
0
 0 1 2 3 4

It is player X's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 5,5
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here:

Coordinates are rejected and user is prompted for coordinates again, Test 4 passes.

Test 5: TicTacToe input coordinates have already been played

H:\cse332\lab4\Lab4\Debug>Lab4.exe TicTacToe

4
3
2
1
0
 0 1 2 3 4

It is player X's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 2,2

4
3
2    X
1
0
 0 1 2 3 4

Player X: 2,2

It is player O's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 2,2
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here:

Coordinates are rejected and user is prompted for coordinates again, Test 5 passes.

Test 6: Correct coordinates are input but then user adds extra characters in their input
H:\cse332\lab4\Lab4\Debug>Lab4.exe TicTacToe

4
3
2
1
0
 0 1 2 3 4

It is player X's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 2,2 hahaha
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here:

Coordinates are rejected and user is prompted for coordinates again, Test 6 passes.

Test 7: Two correct coordinates are input but they’re input in the same turn
H:\cse332\lab4\Lab4\Debug>Lab4.exe TicTacToe

4
3
2
1
0
 0 1 2 3 4

It is player X's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 1,1 2,2
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here:

Coordinates are rejected and user is prompted for coordinates again, Test 7 passes.


Test 8: Playing for a vertical win

The command line and final board state are shown below.

H:\cse332\lab4\Lab4\Debug>Lab4.exe TicTacToe

It is player X's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 1,3

4
3  X   O
2  X O
1  X
0
 0 1 2 3 4

Player X: 1,1; 1,2; 1,3

X won!

Echo %errorlevel% returned 0. Test 8 passes. 

Test 9 and 10:

The command line is the same as in test 8. We tested both horizontal and diagonal wins. In all cases, the win was
detected and main() returned 0.

Test 11: Gomoku input coordinates have already been played
H:\cse332\lab4\Lab4\Debug>Lab4.exe Gomoku

19
18
17
16
15
14
13
12
11
10
9
8
7
6
5
4
3
2
1
X   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19

It is player B's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 1,1

19
18
17
16
15
14
13
12
11
10
9
8
7
6
5
4
3
2
1   B
X   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19

Player B: 1,1

It is player W's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 1,1
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here:

Coordinates are rejected and user is prompted for coordinates again. Test 11 passes.

Tests 12-15:

These tests are similar to how TicTacToeGame was tested. These tests included incorrect formatting of 
a player's turn input. See the list of tests above for specifics. In all of these cases, the game simply
prompted the user for another input. This is the correct and expected behavior.

Tests 16-18:

These tests were intended to check that the done() method correctly detects wins in the vertical, horizontal,
and diagonal directions. These tests all passed, and echo %errorlevel% indicated that main() returned 0 in all
of these cases.

Test 19: 
Testing for a draw in TicTacToe

Command line was:
H:\332S\Lab 4\lab4-rain_lab4\Lab4\Debug>Lab4.exe tictactoe

The final board state of this test was,

4
3  X X O
2  O O X
1  X O X
0
 0 1 2 3 4

As explained above, TictacToe does not call draw until the board is full (piazza post @319). echo %errorlevel% showed that
main() correctly returned 2, as expected.

Test 20:
Testing for draw in Gomoku. Because the extra credit was implemented, we could test this feature on a smaller board.
The command line was:
H:\332S\Lab 4\lab4-rain_lab4\Lab4\Debug>Lab4.exe gomoku 6

This command line means that the board should be 6x6, but because no second number was provided, the winThreshold is still 5.
The final board state was:

6 B W B
5 W B W B W B
4 B W B W B W
3 B W B W B W
2 B W B W B W
1 B W B W B W
X 1 2 3 4 5 6


The final piece placed that causes the draw was the "B" at space 3,6. This is the correct behavior. If we removed this "B" at 3,6, then
given the constraints of this program, we see that "W" still has a possible "win" across the top row (able to get 5 in-a-row given that a
player could take unlimited consecutive turns). echo %errorlevel% returned 2 as expected.

Test 21:
For the final test, we made sure that we could input "quit" as a move at any time in both tictactoe and gomoku. It worked for both games.
echo %errorlevel% returned 1 for these tests, as expected.


*******************************************************


Updating constructors:
The constructor of GameBase class takes in 2 parameters, the first determines the size of the board, and the second determines the winThreshold. The 
default constructor of the TiTacToeGame class then had to be updated to always construct the GameBase base class with parameters 3x3 and winThreshold
of 3. Then the constructor for the GomokuGame class was split into two: one default constructor that is called if no extra command line arguments are
given that automatically calls the GameBase constructor with parameters 19 and 5, and another constructor that takes in two arguments and constructs the
GameBase instance with those custom parameters if they are passed in the command line.

Updating the done() method:

Consider a 20x20 board that requires 12 consecutive pieces to win. The number of possible winning combinations of spaces quickly becomes intractable.
You can no longer check a single row or a single column to see if its pieces are all X or O since the number required to win is less than the playable 
dimension. Therefore, this idea of "checking every winnning possibility" had to be abandoned in order to make done() extensible to larger square boards 
with a win threshold of less than or equal to the dimensions of the playable part of the board.

Imagine you have just placed a piece on any spot on the board. Because there is a buffer of non-playable gameSpace sructs around the board, every 
single playable space on the board has exactly 8 spaces around it. So, if you are player X, and you placed a piece, it looks something like:

		1	2	3
		4	X	5
		6	7	8

Notice: This diagram does not represent a TicTacToe board. It represents just a single space that is part of an arbitarily sized square board 
with its surrounding spots.
As the board becomes larger, it doesn't make sense to check every winning combination of spaces. Instead, we can always start with the piece that
was just placed and explore the spaces directly bordering that space. There is no need to check every possibility because, by inductive reasoning, if 
the game had reached a position where one of the players had won, then that win would have already been caught and the program would have already 
terminated. This is why we can just focus on the space that just had a piece placed on it.

What the extensible version of done() does is check the pieces above and below it (spaces 2 and 7 in the diagram), check the spaces to the left and
right of it (spaces 4 and 5 in the diagram), check the spaces along its "down diagonal" (spaces 1 and 8 in the diagram), and finally, check the spaces
along its "up diagonal" (spaces 6 and 3 in the diagram above). This is done through a series of 4 "if" statement checks within the done() method. If a
piece that matches the piece that was just placed exists along any of these 4 axes (horizonal, vertical, down diagonal, up diagonal), then the program 
calls the appropriate helper method(s) that are mentioned above in "Structure of Methods" section. Each of these helper methods contains 2 "while" loops
that increment a counter (that is passed in by reference). Each "while" loop in each of the methods "reaches" in 1 of the 8 directions and terminates when
it encounters a space that does not match the orinigal. These 8 directions are grouped together into 4 groups because if one direction in a group needs to
be checked, then so does the other. For instance, say that done() detects another "X" at space 2 in the diagram. If the loop only checks spaces in the 
direction of 2, then it will miss any matching pieces that occur below the piece that was just placed (space 7 in this instance). If direction 3 must be
checked, then direction 6 should be checked, if direction 5 needs to be checked, then direction 4 needs to be checked, and so on. If a counter corresponding
to any of the 4 groups reaches or exceeds the winThreshold, then done() will return true.

In terms of memory, this implementation may not be the most efficient for a 3x3 board since it requires that helper method stack frames be stored, each 
instantiated with their own variables. However, this method of checking for a win makes the code extensible to arbitrarily sized square boards. For a 20x20 
board that needs 12 in a row to win, this method is certainly more efficient than checking every single possibility. Instead of checking every possibility, 
the code checks the 8 spaces around the piece that was just placed (which can be easily obtained through the xMoves or oMoves vector) and counts how many
consecutive pieces there are.


Note: As stated on Piazza post @326, "For any bad command line, you can return the same non-zero value. So, anytime the usage function is called, it is ok
to return the same value." Therefore, there are many cases that can lead to a value of 3 being returned from main(). Some of these cases are covered in the
previous "Test Cases" section. These cases include those stated in the instructions: a zero or negative number is passed in for either extra parameter or the
winThreshold is greater than the dimensions of the board. All of these test cases result in echo %errorlevel% returning 3, which is the correct and expected behavior.

As required in the instructions, here is the command line and output for a run of the game with two additional arguments that specifies a size other than 3x3
and winThreshold other than 3.

H:\332S\Lab 4\lab4-rain_lab4\Lab4\Debug>Lab4.exe gomoku 6 4

6
5
4
3
2
1
X 1 2 3 4 5 6

It is player B's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 3,3

6
5
4
3     B
2
1
X 1 2 3 4 5 6

Player B: 3,3

It is player W's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 6,6

6           W
5
4
3     B
2
1
X 1 2 3 4 5 6

Player W: 6,6

It is player B's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 1,6

6 B         W
5
4
3     B
2
1
X 1 2 3 4 5 6

Player B: 3,3; 1,6

It is player W's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 1,1

6 B         W
5
4
3     B
2
1 W
X 1 2 3 4 5 6

Player W: 6,6; 1,1

It is player B's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 2,5

6 B         W
5   B
4
3     B
2
1 W
X 1 2 3 4 5 6

Player B: 3,3; 1,6; 2,5

It is player W's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 5,3

6 B         W
5   B
4
3     B   W
2
1 W
X 1 2 3 4 5 6

Player W: 6,6; 1,1; 5,3

It is player B's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 4,3

6 B         W
5   B
4
3     B B W
2
1 W
X 1 2 3 4 5 6

Player B: 3,3; 1,6; 2,5; 4,3

It is player W's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 4,1

6 B         W
5   B
4
3     B B W
2
1 W     W
X 1 2 3 4 5 6

Player W: 6,6; 1,1; 5,3; 4,1

It is player B's turn
Please enter comma-separated coordinates to make a move or 'quit' to exit the game
Enter here: 3,4

6 B         W
5   B
4     B
3     B B W
2
1 W     W
X 1 2 3 4 5 6

Player B: 3,3; 1,6; 2,5; 4,3; 3,4

B won!

echo %errorlevel% showed that main() returned 0, which is the correct and expected behavior.



========================================================================
