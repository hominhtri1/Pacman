#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

const int visionSize = 3;

const int initialScore = 100;

class Pos
{

public:
	int x;
	int y;

	Pos();
	Pos(int x, int y);

};

void setColor(int color);
void showConsoleCursor(bool showFlag);
void gotoXY(int x, int y);

void drawTile(int tileNum);
void draw(const vector<vector<int>> & map, int score = initialScore);

#endif