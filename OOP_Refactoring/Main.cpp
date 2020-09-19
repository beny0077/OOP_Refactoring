#include <windows.h>	// SetConsoleCursorPosition(HANDLE,COORD)
#include <conio.h>		// _getch()
#include <iostream>		// std::cout

using namespace std;

//Two-dimensional vector struct
struct GameVector {
	int x;
	int y;
	//Default constructor + initialization
	GameVector() : x(0), y(0) {}
	GameVector(int x, int y) { this->x = x; this->y = y; }

	//This is for WinPosition that returns true if a_x and a_y are equal intance of x or y respectavly
	bool is(int a_x, int a_y) { return a_x == x && a_y == y; }
};

class Player {

public:
	//Parameterized constructor for the player data
	Player(int x, int y, char icon) { Position.x = x; Position.y = y; this->icon = icon; }

	void setX(int x) { this->Position.x = x; }

	int getX() { return this->Position.x; }

	void setY(int y) { this->Position.y = y; }

	int getY() { return this->Position.y; }

	void setIcon(char i) { this->icon = i; }

	char getIcon() { return this->icon; }

private:
	//Replaces x and y
	GameVector Position;
	char icon;
};


enum GameState {
	RUNNING, WIN, LOST, USER_QUIT
};

/**
* moves the console cursor to the given x/y coordinate
* @param x
* @param y
*/
void MoveCursor(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
	int Input;
	// Pass in player data to Player constructor
	Player PO(3, 4, 1);

	// game data
	GameState Status = RUNNING;

	//Replaced heigh = 15; and width = 20; with GameVector object
	GameVector Size(20, 15);

	//Calls bool method in GameVector
	GameVector WinPosition(Size.x / 2, Size.y / 2);

	do
	{
		// Draws the game world
		MoveCursor(0, 0);
		for (int row = 0; row < Size.y; row++)
		{
			for (int col = 0; col < Size.x; col++)
			{
				cout << '.';
			}
			cout << '\n';
		}
		// Draw the player
		MoveCursor(PO.getX(), PO.getY());
		cout << PO.getIcon();

		// Get input from the user (wait for one key press)
		Input = _getch();

		// process input from the user
		switch (Input)
		{
		case 'w':	PO.setY(PO.getY() - 1);	break;	// move up
		case 'a':	PO.setX(PO.getX() - 1);	break;	// move left
		case 's':	PO.setY(PO.getY() + 1);	break;	// move down
		case 'd':	PO.setX(PO.getX() + 1);	break;	// move right
		case 27:	Status = USER_QUIT;	break;	// quit
		}

		// if player reaches win position within the field
		if (WinPosition.is(PO.getX(), PO.getY()))
		{
			Status = WIN;
		}
		// if the player goes outside the play field
		if (PO.getX() >= Size.x || PO.getY() >= Size.y)
		{
			Status = LOST;
		}

		// show the game state message
		MoveCursor(0, Size.y + 1);
		switch (Status)
		{
		case WIN:	cout << "You WON! Congratulations!\n";	break;
		case LOST:	cout << "You lost...\n";				break;
		}
	} while (Status == RUNNING);

	// user must press ESCAPE before closing the program
	cout << "press ESCAPE to quit\n";
	while (_getch() != 27);
	return 0;
}
