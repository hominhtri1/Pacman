#ifndef _ENVIRONMENT3_H_
#define _ENVIRONMENT3_H_

#include "Header.h"

class Monster3;

class Environment3
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	int score = initialScore;

	int foodCount;

	vector<Monster3*> monsters;

public:
	Environment3(vector<vector<int>> map);

	bool interact(Pos curPos, vector<vector<int>> & outVision, vector<Pos> & outMonsterPos);

	void drawVision(vector<vector<int>> & vision);

	vector<vector<int>> curVision();
	vector<Pos> curMonsterPos();

	~Environment3();

};

#endif