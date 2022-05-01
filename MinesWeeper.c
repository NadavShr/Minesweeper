//ID 208503896.
//This program provides the game MinesWeeper for the user to play. 
// Further description is at every function of the code.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXNUMOFCOLS 22	
#define MAXNUMOFROWS 22
#define INITVALUE 'X'

void printFirstMenu(); // The first menu that the user see when game is opend. He needs to choose the size of the board.
void charBoardStr(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int rows, int cols, int num_of_mines); // The struct of the board.
void printBoard(char board[][MAXNUMOFCOLS], int rows, int cols); // The board printed on screen.
void boardGameOver(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int rows, int cols); // The board that is printed when player hits a mine.
void numbersNearMines(int minesBoard[][MAXNUMOFCOLS], int row_number, int col_number); // Adjusting the numbers on board accordingly to the amount of mines.
void reveal_spaces(int minesBoard[][MAXNUMOFCOLS], char board[][MAXNUMOFCOLS], int rows, int cols, int x, int y, int* pCounter, int first_call);// If the user landed on a space(' '), then all the spaces touching it will be opend.
void revealHiddenSpots(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int revealNumber, int rows, int cols, int* pCounter, int AmountOfMines); // For "-1" test option.
void scanMovesPrint(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* c, int rows, int cols, int* pCounter, int AmountOfMines); // Scanf user moves option.
void playerChooseBoardsOption(int* num_of_rows, int* num_of_cols, int* isGameOver); // Player chooses the board he wishes to play. 1-4 options for sizes and 0 option for exit.
void checkForNotValidInput(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int* num_of_rows, int* num_of_cols, int* countForWin, int num_of_mines);//This function checks if user enterd invalid options.
void gameIsRunningOptions(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int* num_of_rows, int* num_of_cols, int* countForWin, int* isGameOver, int num_of_mines);//This function moves the game from turn to turn with valid options.
void UserPlayingMinesWeeper(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int* num_of_rows, int* num_of_cols, int* countForWin, int* isGameOver, int num_of_mines); // This if the main game functions that runs.


void main() {
	srand(time(NULL)); // Setting the seed to be the internal clock in order to forever change the values for random numbers.
	char board[MAXNUMOFROWS][MAXNUMOFCOLS];
	char inputForO; // User chooses F or O .
	int minesBoard[MAXNUMOFROWS][MAXNUMOFCOLS];
	int num_of_rows = 0, num_of_cols = 0;
	int num_of_mines;
	int isGameRunning = 0; // If game is over, then value is changed.
	int row, col; // the row and col that the player chooses
	int countForWin = 0; // Counter for turns, if user hits max turns then he won the game.
	int alreadyreviles = 0; // For the " -1 " testing option.
	int valid_input = 0; // For the testing 'while' loop below.

	playerChooseBoardsOption(&num_of_rows, &num_of_cols, &isGameRunning);// The function that prints the first menu and the optional sizes for the boards. User chooses 1-4 or to exit game with 0.
	num_of_mines = (int)sqrt(num_of_rows * num_of_cols); // Number of mines on board.
	charBoardStr(board, minesBoard, num_of_rows, num_of_cols, num_of_mines);
	UserPlayingMinesWeeper(board, minesBoard, &row, &col, &inputForO, &num_of_rows, &num_of_cols, &countForWin, &isGameRunning, num_of_mines);
	
}

void printFirstMenu() { // The first menu that is printed on screen at game start.
	printf("Welcome to Minesweeper!\n\n");
	printf("Please choose one of the following options and enter it's number:\n\n");
	printf("1 - for size 8X8\n\n2 - for size 12X12\n\n3 - for size 15X15\n\n4 - for custom size\n\n0 - Exit\n\n");
}
void charBoardStr(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int rows, int cols, int num_of_mines) {
	int i;
	int j;
	int row_number;
	int col_number;

	for (i = 0; i < rows; i++) { // At start, setting the entire board to 'X'.
		for (j = 0; j < cols; j++) {
			board[i][j] = INITVALUE;
			minesBoard[i][j] = 0; // Setting the entire minesBoard to value 0, and  the mines will be valued as 9.
		}
	}
	for (i = 0; i < num_of_mines; i++) { // Setting the mines randomly.
		row_number = rand() % rows;
		col_number = rand() % cols;
		while (minesBoard[row_number][col_number] == 9) // If landed on a mine, then randomize again.
		{
			row_number = rand() % rows;
			col_number = rand() % cols;
		}
		minesBoard[row_number][col_number] = 9; // Setting the mines values not 0 as the rest of the board. (since 9 is never an option for nearby mines)
		numbersNearMines(minesBoard, row_number, col_number);
	}
}
void numbersNearMines(int minesBoard[][MAXNUMOFCOLS], int row_number, int col_number) // Adjusting the numbers on board accordingly to the amount of mines.
{
	if (row_number > 0)
	{
		if (minesBoard[row_number - 1][col_number] != 9) //only if minesboard[][] is not a mine, then change it.
			minesBoard[row_number - 1][col_number] += 1;
		if (col_number > 0)
		{
			if (minesBoard[row_number - 1][col_number - 1] != 9)//only if minesboard[][] is not a mine, then change it.
				minesBoard[row_number - 1][col_number - 1] += 1;
		}
		if (col_number < MAXNUMOFCOLS - 1)
		{
			if (minesBoard[row_number - 1][col_number + 1] != 9)//only if minesboard[][] is not a mine, then change it.
				minesBoard[row_number - 1][col_number + 1] += 1;
		}
	}
	if (row_number < MAXNUMOFROWS - 1)
	{
		if (minesBoard[row_number + 1][col_number] != 9)//only if minesboard[][] is not a mine, then change it.
			minesBoard[row_number + 1][col_number] += 1;
		if (col_number > 0)
		{
			if (minesBoard[row_number + 1][col_number - 1] != 9)//only if minesboard[][] is not a mine, then change it.
				minesBoard[row_number + 1][col_number - 1] += 1;
		}
		if (col_number < MAXNUMOFCOLS - 1)
		{
			if (minesBoard[row_number + 1][col_number + 1] != 9)//only if minesboard[][] is not a mine, then change it.
				minesBoard[row_number + 1][col_number + 1] += 1;
		}
	}
	if (col_number > 0)
	{
		if (minesBoard[row_number][col_number - 1] != 9)//only if minesboard[][] is not a mine, then change it.
			minesBoard[row_number][col_number - 1] += 1;
	}
	if (col_number < MAXNUMOFCOLS - 1)
	{
		if (minesBoard[row_number][col_number + 1] != 9)//only if minesboard[][] is not a mine, then change it.
			minesBoard[row_number][col_number + 1] += 1;
	}
}
void printBoard(char board[][MAXNUMOFCOLS], int rows, int cols)  // The board that is printed on screen.
{
	int i;
	int j;
	printf("       ");
	for (j = 0; j < cols; j++) {
		if (j < 10)
			printf(" ");
		printf("%d  ", j);
	}
	printf("\n");
	printf("  ");
	for (j = 0; j < (cols + 1) * 4; j++) {
		printf("_", j);
	}
	printf("\n");
	for (i = 0; i < rows; i++) {
		printf("  ");
		if (i < 10)
			printf(" ");
		printf(" %d ", i);
		for (j = 0; j < cols; j++) {
			printf("|");
			printf(" %c ", board[i][j]);
		}
		printf("|");
		printf("\n");
	}
	printf("  ");
	for (j = 0; j < (cols + 1) * 4; j++)
		printf("_", j);

	printf("\n");
}
void boardGameOver(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int rows, int cols) // This is the board that's printed when game is over.
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (minesBoard[i][j] == 0) // If the minesBoard is not valued 9, as a mine is, then 'space' is printed to show on board.
			{
				board[i][j] = ' ';
			}
			else if (minesBoard[i][j] == 9) // If the minesBoard is valued 9, as a mine is, then '*' is printed to show on board.
			{
				board[i][j] = '*';
			}
			else
				board[i][j] = (char)(minesBoard[i][j] + 48);
		}
	}
}
void reveal_spaces(int minesBoard[][MAXNUMOFCOLS], char board[][MAXNUMOFCOLS], int rows, int cols, int ROW, int COL, int* pCounter, int first_call)
{
	if (ROW > rows - 1 || ROW < 0 || COL > cols - 1 || COL < 0)
	{
		return;
	}
	if (board[ROW][COL] != 'X')
	{
		if (board[ROW][COL] == 'F' && first_call == 1) {
			board[ROW][COL] = ' ';
		}
		else
			return;
	}
	if (minesBoard[ROW][COL] != 0)
	{
		board[ROW][COL] = (char)(minesBoard[ROW][COL] + 48);
		*pCounter += 1;
		return;
	}

	board[ROW][COL] = ' ';
	*pCounter += 1;

	reveal_spaces(minesBoard, board, rows, cols, ROW + 1, COL, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW - 1, COL, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW, COL + 1, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW, COL - 1, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW + 1, COL + 1, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW - 1, COL - 1, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW + 1, COL - 1, pCounter, 0);
	reveal_spaces(minesBoard, board, rows, cols, ROW - 1, COL + 1, pCounter, 0);
}
void scanMovesPrint(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int rows, int cols, int* pCounter, int AmountOfMines)
{
	system("cls");
	printBoard(board, rows, cols);
	printf("Please enter your move: Insert row, col and O to open or F to flag spot:\n");
	scanf("%d %d", prow, pcol);
	if (*prow == -1)
	{

		if (*pcol > 0)
			revealHiddenSpots(board, minesBoard, *pcol, rows, cols, pCounter, AmountOfMines);
	}
	else
		scanf(" %c", pChar);
}
void revealHiddenSpots(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int revealNumber, int rows, int cols, int* pCounter, int AmountOfMines)
{
	int i, j;
	int counter = revealNumber;
	for (i = 0; i < rows && counter != 0; i++)
	{
		for (j = 0; j < cols && counter != 0; j++)
		{
			if (board[i][j] == 'X')
			{
				if (minesBoard[i][j] == 0)
				{
					board[i][j] = ' ';
					counter--;
					*pCounter += 1;
				}
				else if (minesBoard[i][j] < 9)
				{
					board[i][j] = (char)(minesBoard[i][j] + 48);
					counter--;
					*pCounter += 1;
				}
			}
		}
	}

}
void playerChooseBoardsOption(int* num_of_rows, int* num_of_cols, int* isGameRunning)
{
	int rowsNumber, colsNumber;
	int BoardSizeOption;
	printFirstMenu(); // The first instructions that is printed to the user, which offer several options for the game, and an exit option.
	scanf("%d", &BoardSizeOption); // Player chooses a number between 1-4 \ 0 from options.

	while (BoardSizeOption < 0 || BoardSizeOption > 4) // if the player insert wrong value. 
	{
		printf("\nInvalid option, please input again.\n\n");
		printFirstMenu();
		scanf("%d", &BoardSizeOption);
	}
	if (BoardSizeOption == 1)
	{
		*num_of_rows = 8;
		*num_of_cols = 8;
	}
	else if (BoardSizeOption == 2)
	{
		*num_of_rows = 12;
		*num_of_cols = 12;
	}
	else if (BoardSizeOption == 3)
	{
		*num_of_rows = 15;
		*num_of_cols = 15;
	}
	else if (BoardSizeOption == 4)
	{
		printf("Please enter the size of the board (Lines <= 22 and cols <= 22):\n");
		scanf("%d %d", &rowsNumber, &colsNumber);
		*num_of_rows = rowsNumber;
		*num_of_cols = colsNumber;
		while (*num_of_rows < 1 || *num_of_rows > MAXNUMOFROWS)
		{
			printf("Number of lines is out of range!\n");
			printf("Please enter the size of the board (Lines <= 22 and cols <= 22):\n");
			scanf("%d %d", &rowsNumber, &colsNumber);
			*num_of_rows = rowsNumber;
			*num_of_cols = colsNumber;
		}
		while (*num_of_cols < 1 || *num_of_cols > MAXNUMOFCOLS)
		{
			printf("Number of columns is out of range!\n");
			printf("Please enter the size of the board (Lines <= 22 and cols <= 22):\n");
			scanf("%d %d", &rowsNumber, &colsNumber);
			*num_of_rows = rowsNumber;
			*num_of_cols = colsNumber;
		}

	}
	else if (BoardSizeOption == 0)
		*isGameRunning = 1;
}
void checkForNotValidInput(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int* num_of_rows, int* num_of_cols, int* countForWin, int num_of_mines)
{
	int valid_input = 0;

	while (valid_input == 0) 
	{
		if (*prow == -1)
		{
			valid_input = 1;
		}
		else if (*prow > * num_of_rows || *prow < -2 || *pcol > * num_of_cols || *pcol < 0 && *pChar != 'F' && *pChar != 'f' && *pChar != 'O' && *pChar != 'o')
		{
			printf("Invalid move.\n");
			scanMovesPrint(board, minesBoard, prow, pcol, pChar, *num_of_rows, *num_of_cols, countForWin, num_of_mines);

		}
		else if (board[*prow][*pcol] != 'X' && board[*prow][*pcol] != 'F' && *prow != -1)
		{
			printf("Invalid move. You have already made this move.\n");
			scanMovesPrint(board, minesBoard, prow, pcol, pChar, *num_of_rows, *num_of_cols, countForWin, num_of_mines);

		}
		else if (*pChar == 'F' && board[*prow][*pcol] != 'X')
		{
			printf("Invalid move.\n");
			scanMovesPrint(board, minesBoard, prow, pcol, pChar, *num_of_rows, *num_of_cols, countForWin, num_of_mines);

		}
		else if (board[*prow][*pcol] != 'X' && *pChar == 'F' || board[*prow][*pcol] != 'X' && *pChar == 'f')
		{
			printf("Invalid move.\n");
			scanMovesPrint(board, minesBoard, prow, pcol, pChar, *num_of_rows, *num_of_cols, countForWin, num_of_mines);

		}
		else if (board[*prow][*pcol] != 'X' && board[*prow][*pcol] != 'F' && *pChar == 'O' || board[*prow][*pcol] != 'X' && board[*prow][*pcol] != 'F' && *pChar == 'o')
		{
			printf("Invalid move.\n");
			scanMovesPrint(board, minesBoard, prow, pcol, pChar, *num_of_rows, *num_of_cols, countForWin, num_of_mines);

		}
		else
			valid_input = 1; // To break from the loop if the input was valid.
	}
}
void gameIsRunningOptions(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int* num_of_rows, int* num_of_cols, int* countForWin, int* isGameOver, int num_of_mines)
{

	if (*pChar == 'F' || *pChar == 'f')
	{
		board[*prow][*pcol] = 'F';
	}
	else if (minesBoard[*prow][*pcol] == 9) // if Player hits a mine, then the board is printed and game is over.
	{
		boardGameOver(board, minesBoard, *num_of_rows, *num_of_cols);
		printf("You have hit a bomb! the game is over.\n\n");
		*isGameOver = 1;
		printBoard(board, *num_of_rows, *num_of_cols);
	}
	else if (minesBoard[*prow][*pcol] == 0)
	{
		reveal_spaces(minesBoard, board, *num_of_rows, *num_of_cols, *prow, *pcol, countForWin, 1);
	}
	else if (*prow != -1)
	{

		board[*prow][*pcol] = (char)(minesBoard[*prow][*pcol] + 48);
		countForWin++;
	}
	if (*countForWin >= *num_of_rows * *num_of_cols - num_of_mines) // If the player has done the amount of turns minus number of mines left on board, he has won.
	{
		printf("\n\n||**||**Congratulations, you have won the game.||**||**\n\n");
		*isGameOver = 1;
	}

}
void UserPlayingMinesWeeper(char board[][MAXNUMOFCOLS], int minesBoard[][MAXNUMOFCOLS], int* prow, int* pcol, char* pChar, int* num_of_rows, int* num_of_cols, int* countForWin, int* isGameRunning, int num_of_mines)
{
	
	while (*isGameRunning == 0) // Game runs as long as game is played.
	{
		scanMovesPrint(board, minesBoard, prow, pcol, pChar, *num_of_rows, *num_of_cols, countForWin, num_of_mines);
		checkForNotValidInput(board, minesBoard, prow, pcol, pChar, num_of_rows, num_of_cols, countForWin, num_of_mines);
		gameIsRunningOptions(board, minesBoard, prow, pcol, pChar, num_of_rows, num_of_cols, countForWin, isGameRunning, num_of_mines);
	}
}