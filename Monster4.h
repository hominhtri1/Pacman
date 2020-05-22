#ifndef _MONSTER4_H_
#define _MONSTER4_H_

#include "Header.h"

class Monster4
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int x;
	int y;

	int Px;
	int Py;

	vector<int> distanceTypeWeight{ 9, 3, 1 };

	int distanceToAgent(int x, int y);

	vector<int> posWeightDist(vector<Pos> & possiblePos);

	int weightedChoice(vector<int> & posWeight);

public:
	Monster4(vector<vector<int>> map, int Mx, int My);

	Pos interact(int cur_Px, int cur_Py);

	Pos getPos();

};

#endif