#include "Header.h"

Pos::Pos()
{
	this->x = -1;
	this->y = -1;
}

Pos::Pos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawTile(int tileNum)
{
	if (tileNum == 0)
		setColor(1);
	else if (tileNum == 1)
		setColor(15);
	else if (tileNum == 2)
		setColor(14);
	else if (tileNum == 3)
		setColor(12);
	else if (tileNum == 4)
		setColor(11);
	else
		setColor(8);

	cout << tileNum << " ";

	setColor(11);
}

void draw(const vector<vector<int>> & map)
{
	int M = map.size();
	int N = map[0].size();

	gotoXY(0, 0);

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
			drawTile(map[i][j]);

		cout << endl;
	}

	cin.get();
}