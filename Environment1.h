#ifndef _ENVIRONMENT1_H_
#define _ENVIRONMENT1_H_

#include "Header.h"

class Environment1
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	int score = initialScore;

public:
	Environment1(vector<vector<int>> map);

	bool interact(Pos curPos);

};

#endif