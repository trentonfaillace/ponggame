#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int width = 60, height = 15;					//global variables
int xBall, yBall;								//ball location
int paddle1row, paddle1col;						//paddle locations (top position of paddle)
int paddle2row, paddle2col;						//
bool ballUp, ballRight, ballLeft, ballDown;		//flags (for ball movement)
bool top1, bot1, top2, bot2;					//flags (for paddle movement)
int Player1Score = 0, Player2Score = 0;			//scorekeeper

void gotoxy(int column, int line)			//gotoxy function that moves cursor to specified location
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

void DisplayMenu() //main menu
{
	cout << "******************************************************************" << endl;
	cout << "******************************************************************" << endl;
	cout << "**                                                          	**" << endl;
	cout << "**                         	PING                         	**" << endl;
	cout << "**                                                          	**" << endl;
	cout << "**                      	Created By:                 	**" << endl;
	cout << "**	         Trenton Faillace and Giovanni Zambrano         **" << endl;
	cout << "**                                                          	**" << endl;
	cout << "**  Please choose one of the following options:             	**" << endl;
	cout << "**                                                          	**" << endl;
	cout << "**  A) New Game                                             	**" << endl;
	cout << "**  B) How to play                                          	**" << endl;
	cout << "**  Q) Quit                                                 	**" << endl;
	cout << "**                                                          	**" << endl;
	cout << "******************************************************************" << endl;
	cout << "******************************************************************" << endl;

}

char MenuInput()			//gets menu input
{
	char input;
	cout << "Please enter your choice: ";
	cin >> input;
	return input;
}

void DisplayBoard()			//displays outer bounds of the board
{
	system("cls");

	for (int i = 0; i < width; i++) //prints top wall
	{
		cout << "\xB2";
	}
	cout << endl;

	for (int i = 0; i < height; i++) //prints left and right walls
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == 1)
				cout << "\xB2"; //prints left wall
			else if (j == width - 1 || j == width - 2)
				cout << "\xB2"; //prints right wall
			else
				cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) //prints bottom wall
	{
		cout << "\xB2";
	}
	cout << endl;
	cout << "Player 1: " << Player1Score << "\t\t\t\t\t" << "Player 2: " << Player2Score << endl;
}

void DisplayBall()
{
	if (yBall == 1)						//bounce logic
	{
		ballDown = true;
		ballUp = false;
	}
	if (yBall == 15)
	{
		ballDown = false;
		ballUp = true;
	}

	for (int i = 0; i < 5; i++) {
		if (((paddle1row + 1) == xBall) && ((paddle1col + i) == yBall)) {								//paddle bounce logic
			ballRight = true;
			ballLeft = false;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (((paddle2row - 1) == xBall) && ((paddle2col + i) == yBall)) {								//paddle bounce logic
			ballRight = false;
			ballLeft = true;
		}
	}
	
	

	gotoxy(xBall, yBall);
	_putch('o');
	Sleep(175);

	if (ballDown && ballLeft)			//movement logic
	{
		yBall = yBall + 1;
		xBall = xBall - 1;
		int y2ball = yBall - 1;
		int x2ball = xBall + 1;
		gotoxy(x2ball, y2ball);
		_putch(' ');
	}
	else if (ballDown && ballRight)
	{
		yBall = yBall + 1;
		xBall = xBall + 1;
		int y2ball = yBall - 1;
		int x2ball = xBall - 1;
		gotoxy(x2ball, y2ball);
		_putch(' ');
	}
	else if (ballUp && ballRight)
	{
		yBall = yBall - 1;
		xBall = xBall + 1;
		int y2ball = yBall + 1;
		int x2ball = xBall - 1;
		gotoxy(x2ball, y2ball);
		_putch(' ');
	}
	else if (ballUp && ballLeft)
	{
		yBall = yBall - 1;
		xBall = xBall - 1;
		int y2ball = yBall + 1;
		int x2ball = xBall + 1;
		gotoxy(x2ball, y2ball);
		_putch(' ');
	}

}

void P1Paddle()
{
	for (int i = 0; i < 5; i++) {
		gotoxy(paddle1row, paddle1col);
		_putch('x');
		paddle1col++;
	}
	paddle1col = paddle1col - 5;
}

void P2Paddle()
{
	for (int i = 0; i < 5; i++) {
		gotoxy(paddle2row, paddle2col);
		_putch('x');
		paddle2col++;
	}
	paddle2col = paddle2col - 5;
}

void RunGame()
{
	while (Player1Score < 7 && Player2Score < 7) {

		DisplayBoard();
		xBall = 30;
		paddle1row = 5;
		paddle1col = 6;
		paddle2row = 55;
		paddle2col = 6;
		char input = 'p';

		while (xBall != 1 && xBall != 58)
		{
			if (xBall == 2)
			{
				Player1Score++;
			}
			else if (xBall == 57)
			{
				Player2Score++;
			}

			if (_kbhit()) {
				input = _getch();
			}

			if (input == 'w') {
				paddle1col = paddle1col + 4;
				gotoxy(paddle1row, paddle1col);
				_putch(' ');
				paddle1col = paddle1col - 5;
				input = 'p';
			}
			if (input == 's') {
				gotoxy(paddle1row, paddle1col);
				_putch(' ');
				paddle1col = paddle1col + 1;
				input = 'p';
			}
			if (input == 'i') {
				paddle2col = paddle2col + 4;
				gotoxy(paddle2row, paddle2col);
				_putch(' ');
				paddle2col = paddle2col - 5;
				input = 'p';
			}
			if (input == 'k') {
				gotoxy(paddle2row, paddle2col);
				_putch(' ');
				paddle2col = paddle2col + 1;
				input = 'p';
			}

			P1Paddle();
			P2Paddle();
			DisplayBall();
		}
	}
}

void DisplayHowTo()
{
	char in;
	do
	{
		system("cls");
		cout << "******************************************************************" << endl;
		cout << "******************************************************************" << endl;
		cout << "**                                                          	**" << endl;
		cout << "**                         	PING                         	**" << endl;
		cout << "**                                                          	**" << endl;
		cout << "** Ping is a simulation of table tennis with a twist! Your  	**" << endl;
		cout << "** goal is to reach eleven points before your opponent. Points  **" << endl;
		cout << "** are earned when your opponent fails to return the ball. But  **" << endl;
		cout << "** watch out for the walls in the center. If you hit one, it	**" << endl;
		cout << "** will return the ball right back to you!                  	**" << endl;
		cout << "** Player one uses 'w' and 's' keys to move paddle up and down. **" << endl;
		cout << "** Player two used 'i' and 'k' keys to move paddle up and down. **" << endl;
		cout << "**                      	HAVE FUN!                   	**" << endl;
		cout << "**                                                          	**" << endl;
		cout << "******************************************************************" << endl;
		cout << "******************************************************************" << endl;

		cout << "To return to the main menu, press Z and hit enter: ";
		cin >> in;
	} while (in != 'z' && in != 'Z');
	void main();
}



int main()
{
	xBall = 30;
	yBall = 10;
	ballDown = false;
	ballRight = false;
	ballUp = true;
	ballLeft = true;
	char choice;

	do
	{
		system("cls");
		DisplayMenu();
		choice = MenuInput();
		if (choice == 'A' || choice == 'a')
		{
			RunGame();
		}
		else if (choice == 'B' || choice == 'b')
		{
			system("cls");
			DisplayHowTo();
		}
		else
		{
			cout << "Choice is invalid, please pick a valid choice.";
		}

	} while (choice != 'Q');

	system("pause");
	return 0;
}