// SnakeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdio.h>
using namespace std;

static int height=20, width=20;							//BOUNDARIES OF THE GAME SQUARE
bool GameOver;
int x, y,fruitX,fruitY,score=0,a,b,sleep_interval=70,nTail=0,tailX[50],tailY[50];
/*
x , y 		: POSITION OF SNAKE HEAD
fruitX, fruitY  : POSITION OF FRUIT
score 		: SCORE OF PLAYER
nTail		: TAIL COUNT
tailX[],tailY[] : ARRAYS FOR STORING TALE POSITIONS 		
*/

enum Edirection{STOP=0,LEFT,RIGHT,UP,DOWN};
Edirection dir;


void Setup()									//RUNS INITIALLY EVERYTIME THE GAME STARTS
{
	GameOver = false;
	dir = STOP;
	x = width % 2;								
	y = height % 2;
	fruitX = rand() % width;
	fruitY = rand() % height;						//FOR RANDOMLY PRINTING FRUIT INSIDE THE GAME SQUARE

}


void Logic()
{
	int prevX, prevY, prev2X, prev2Y;					//LOGIC FOR PRINTING TAIL OF SNAKE
	prevX = tailX[0];
	prevY = tailY[0];
	tailX[0] = x, tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)								//FOR CHANGING THE DIRECTION ACCORDING TO INPUT 
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	default :
		break;
	}

	/*if (x > width || x< 0 || y > height || y < 0)
	{									//IN ORDER TO LOCK BOUNDARIES FOR SNAKE REMOVE THESE AS COMMENT
		GameOver = true;
	}*/
	
	if (x > width) x = 0; if (x < 0) x = width - 1;				//PUT THESE TO LINES AS COMMENT TO LOCK BOUNDRIES FOR SNAKE
	if (y > height) y = 0; if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)						//GAME OVERS IF SNAKE TOUCHES IT'S TAIL
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			GameOver = true;
		}
	}
	
	if (x == fruitX && y == fruitY)						//IF SNAKE EATS FRUIT SCORE & TAIL SIZE IS INCREASED BUT sleep_interval is DECREASED
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;

		nTail += 1;


		if (sleep_interval > 1)
		sleep_interval -= 5;
		
	}
	cout << "Score: " << score << endl;
}

void Input()									//FUNCTION DETECTS WHICH INPUT IS BEING GIVEN AND SETS VALUE OF dir ACCORDING TO IT 
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;

		case 'x':
			GameOver = true;
			break;
		}

	}

}
 
void Draw()									//DRAW FUNCTION IS USED TO PRINT ALL COMPONENTS IN SNAKE GAME
{
	
	system("cls");
	for ( a = 0; a < width + 2; a++)					//PRINTS THE UPPER HORIZONTAL GAME BOUNDARY
	{
		cout << "* ";
	}
	cout << "\n";
	for (a = 0; a < height; a++)
	{
		for (b = 0; b < width; b++)
		{


			if (b == 0)						//PRINTS THE VERTICAL GAME BOUNDARY ON THE LEFT SIDE
			{
				cout << "* ";
			}


			if (a == y && b == x)					//PRINTS SNAKE HEAD
			{
				cout << "O ";
			}

			else if (a == fruitY && b == fruitX)			//PRINTS THE FRUIT
			{
				cout << "F ";
			}

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)			//PRINTS THE SNAKE TALE 
					{
						if (tailX[k] == b && tailY[k] == a)
							{
								cout << "o ";
								print = true;
							}
					}

				if (!print)
				cout << "  ";
			}
		

		if( b == width - 1)						//PRINTS THE VERTICAL GAME BOUNDARY ON THE RIGHT SIDE
			{
			cout << "* ";
			}

	}
	cout << endl;

}
for (a = 0; a <width + 2; a++)							//PRINTS THE LOWER HORIZONTAL GAME BOUNDARY
{
	cout << "* ";
}
cout << endl;
}



int main()
{
	Setup();								//GAME IS INITIALIZED AND FUNCTIONS ARE CALLED
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		if (sleep_interval == 1)
		cout << "Full Speed!" << endl;					//IS DISPLAYED WHEN SNAKE IS IN FULL SPEED
		Sleep(sleep_interval);
	}
	
    return 0;
	
}

