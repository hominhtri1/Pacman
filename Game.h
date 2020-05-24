#ifndef _GAME_H_
#define _GAME_H_

#include "Header.h"

class Game
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	int monsterCount;

	void generateMap();

	void levelMenu();

	void level1();
	void level2();
	void level3();
	void level4();

public:
	Game();

	void start();

};

#endif