#include <stdio.h>
#include <stdlib.h>
int turn = 0; //counter to alternate turns
//showBoard:	Prints the entire tic-tac-toe-board
//Parameters:	board: A pointer to an array of 9 characters representing the tic-tac-toe board.
//					Legal values for each entry are ' ','X','O'
//Returns:		None				
void showBoard(char *board)
{
	printf("\n"); 
	for(int i = 0; i < 9; i++) //runs through nine positions that will take up array indexs
	{
		printf(" %c ", board[i]);
		if(i % 3 == 2) 
		{
			if(i < 6)
			{
				printf("\n-----------\n"); // places a boundary between each row
			}
			else
			{
				printf("\n");
			}
		}
		else
		{
			printf("|");  //puts a | in between each X/O for format
		}
	}
}

//getMove:		Processes a player move
//Paramters:	board: A pointer to an array of 9 characters representing the tic-tac-toe board.
//					Legal values for each entry are ' ','X','O'
//				player: The symbol for the current player (X for 1,O for 2)
//Returns:		None
//Note:			Only accepts input between 1 and 9 for the move.  Only allows input if current space in board is empty (' ')
void getMove(char *board, char playerSymbol)
{
	printf("\n");
	char buffer[255];
	int position = 0;
	int input = 0;

	while(1) //Runs until all positions of the board are filled with valid input
	{	
		if(turn % 2 == 0) //alternates between players
		{
			printf("Enter a position (1-9) for Player 1 (X): ");
			scanf("%s",buffer);
                	sscanf(buffer,"%d",&input);  //sscanf is just like scanf, but scans a string instead of stdin
                	position = input - 1; //tracks the position of the user input (input - one to keep track of array index)
		}
		else
		{
			printf("Enter a position (1-9) for Player 2 (O): ");
			scanf("%s",buffer);
                	sscanf(buffer,"%d",&input);  //sscanf is just like scanf, but scans a string instead of stdin
                	position = input - 1; //tracks the position of the user input (input - one to keep track of array index)
		}

		if(position < 0 || position > 8)
		{
			 printf("\nNot a valid position!\n"); //checks if the user is enter valid input from one to nine
		}
		else if(board[position] != ' ')
		{
			printf("\nYou already filled this position!\n"); //checks whether a position is full so none are overwritten
		}
		else
		{
			board[position] = playerSymbol;
			turn++; //counts turns
	                return; //breaks once each position is full
		}
		printf("\n");
	}
}

//checkWin: checks the board to see if there is a win for the given player
//Parameters:	board: A pointer to an array of 9 characters representing the tic-tac-toe board.
//					Legal values for each entry are ' ','X','O'
//				playerSymbol: The symbol for the player being checked for a win ('X','O')
//Returns: 		non-zero if a win occurs for playerSymbol, zero otherise
int checkWin(char *board, char playerSymbol)
{
	int xColCount = 0; //counters to track the number of win conditions
	int oColCount = 0;
	int xRowCount = 0;
	int oRowCount = 0;
	int xDiagCount = 0;
	int oDiagCount = 0;

	for(int i = 0; i < 3; i++) //check for column victory
	{
		if ((board[i] == 'X' && board[i + 3] == 'X') && (board[i + 3] == 'X' && board[i + 6] == 'X') && playerSymbol == 'X')
		{
			xColCount++; //x column victory
		}
		if((board[i] == 'O' && board[i + 3] == 'O') && (board[i + 3] == 'O' && board[i + 6] == 'O') && playerSymbol == 'O')
		{
			oColCount++; //o column victory
		}
	}

	for(int i = 0; i < 7; i+=3) //check for row victory
	{
		if((board[i] == 'X' && board[i + 1] == 'X') && (board[i + 1] == 'X' && board[i + 2] == 'X') && playerSymbol == 'X')
		{
			xRowCount++; //x row victory
		}
		if((board[i] == 'O' && board[i + 1] == 'O') && (board[i + 1] == 'O' && board[i + 2] == 'O') && playerSymbol == 'O')
		{
			oRowCount++; //o row victory
		}
	}

	if((board[0] == 'X' && board[4] == 'X') && (board[4] == 'X' && board[8] == 'X') && playerSymbol == 'X') // check for diagnoal victory --> hard-coded due to specificism
	{
		xDiagCount++; //x diag victory condtion 
	} 
	if((board[2] == 'X' && board[4] == 'X') && (board[4] == 'X' && board[6] == 'X') && playerSymbol == 'X')
	{
		xDiagCount++; //other x diag victory condition
	}
	if((board[0] == 'O' && board[4] == 'O') && (board[4] == 'O' && board[8] == 'O') && playerSymbol == 'O')
	{
		oDiagCount++; //o diag victory condition
	}
	if((board[2] == 'O' && board[4] == 'O') && (board[4] == 'O' && board[6] == 'O') && playerSymbol == 'O')
	{
		oDiagCount++; //other o diag victory condition
	}

	if(xColCount > 0 || xRowCount > 0 || xDiagCount > 0) //checks every instance of each playerSymbol victory condition --> any count incrementation represents a player victory
	{
		return 1;
	}
	if(oColCount > 0 || oRowCount > 0 || oDiagCount > 0)
	{
		return 1;
	}

	return 0; //no matches of a win condition
}

//checkBoard: checks the board to see if the game is over
//Parameters:	board: A pointer to an array of 9 characters representing the tic-tac-toe board.
//					Legal values for each entry are ' ','X','O'
//				winner: A pointer to an integer to accept the current winner.  0 indicates no winner, otherwise it is the player number
//Returns:		0 if the game is over, non-zero if the game should continue.  Game is over if a player wins, or there are no more valid moves.
int checkBoard(char *board, int *winner)
{
	if (checkWin(board, 'X'))
	{
		*winner = 1;
		return 0;
	}
	if (checkWin(board, 'O'))
	{
		*winner = 2;
		return 0;
	}
	int spaceCount = 0;
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ')
		{
			spaceCount++;
		}
	}
	return spaceCount;
}

int main(int argc, char **argv)
{
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' '};
    char symbols[3]={' ','X','O'};
    int player = 2;
    int winner = 0;
    int running = 1;
    while (running)
    {
        player = (player++) % 2 + 1;
        showBoard(board);
        getMove(board, symbols[player]);
        running = checkBoard(board, &winner);
    }
    showBoard(board);
    printf("\n");
    if (winner!=0)
    {
        printf("Congratulations player %d!!! You win.\n",player);
    }
    else
    {
        printf("It's a tie!!!\n");
    }
    printf("\n");
    return 0;
}
