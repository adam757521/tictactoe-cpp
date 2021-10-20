#include <iostream>
#include <time.h> 

bool check_pos_validation(char gameboard[3][3], int pos) {
	// Returns a bool representing if the pos is correct.

	return pos <= 8 && pos >= 0 && gameboard[pos / 3][pos % 3] == ' ';
}

void set_gameboard_symbol(char (*gameboard)[3][3], int pos, char symbol)
{
	(*gameboard)[pos / 3][pos % 3] = symbol;
}

void display_gameboard(char gameboard[3][3]) {
	for (int row = 0; row < 3; row++) 
	{
		for (int column = 0; column < 3; column++) 
		{
			std::cout << gameboard[row][column];

			if (column < 2)
				std::cout << "|";
		}

		if (row < 2)
			std::cout << "\n" << "-+-+-" << "\n";
	}
	
	std::cout << "\n";
}

bool equal3(char a, char b, char c) {
	if (a == ' ') return false;

	return a == b && b == c;
}

bool get_draw(char gameboard[3][3]) {
	bool draw = true;

	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			draw = gameboard[row][column] != ' ';

			if (!draw) return draw;
		}
	}

	return draw;
}

char get_winner(char gameboard[3][3]) {
	// Returns the winner symbol
	
	// Horizantal
	for (int i = 0; i < 3; i++) {
		if (equal3(gameboard[i][0], gameboard[i][1], gameboard[i][2]))
			return gameboard[i][0];
	}

	// Vertical
	for (int i = 0; i < 3; i++) {
		if (equal3(gameboard[0][i], gameboard[1][i], gameboard[2][i]))
			return gameboard[0][i];
	}

	// Diagonal
	if (equal3(gameboard[0][0], gameboard[1][1], gameboard[2][2]) || equal3(gameboard[2][0], gameboard[1][1], gameboard[0][2]))
		return gameboard[1][1];

	return NULL;
}

int main()
{
	char gameboard[][3] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '},
	};	

	srand(time(NULL));

	display_gameboard(gameboard);
	
	char winner = NULL;
	char turn = 'X';  // X - Player, O - Bot

	while (winner == NULL) {
		if (get_draw(gameboard)) break;

		int turn_position = -1;
		
		if (turn == 'X') {
			while (!check_pos_validation(gameboard, turn_position)) {
				std::cout << "Please enter a position 1-9: ";
				std::cin >> turn_position;
				turn_position -= 1;
			}
		} else {
			while (!check_pos_validation(gameboard, turn_position)) {
				turn_position = rand() % 9;
			}
		}
		
		std::cout << turn << " played " << turn_position + 1 << "\n";
		
		set_gameboard_symbol(&gameboard, turn_position, turn);
		display_gameboard(gameboard);
		
		winner = get_winner(gameboard);
		turn = turn == 'X'? 'O' : 'X';
	}

	if (winner) {
		std::cout << "The game has ended, " << winner << " won!" << "\n";
	}
	else {
		std::cout << "Its a draw!" << "\n";
	}

	display_gameboard(gameboard);
}