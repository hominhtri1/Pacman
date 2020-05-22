#ifndef _ENVIRONMENT4_H_
#define _ENVIRONMENT4_H_

#include "Header.h"

class Monster4;

class Environment4
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	int foodCount;

	vector<Monster4*> monsters;

public:
	Environment4(vector<vector<int>> map);

	bool interact(Pos curPos, vector<Pos> & outMonsterPos);

	void drawMonsters();

	vector<Pos> curMonsterPos();

	~Environment4();

};

#endif