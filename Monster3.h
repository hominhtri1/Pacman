#ifndef _MONSTER3_H_
#define _MONSTER3_H_

#include "Header.h"

class Monster3
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int start_x;
	int start_y;

	int cur_x;
	int cur_y;

	int id;

	const int monsterRange = 1;

public:
	Monster3(vector<vector<int>> map, int Mx, int My, int id);

	Pos interact(vector<Pos> & monsterPos);

	Pos getPos();

};

#endif