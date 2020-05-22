#ifndef _ENVIRONMENT2_H_
#define _ENVIRONMENT2_H_

#include "Header.h"

class Environment2
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

public:
	Environment2(vector<vector<int>> map);

	bool interact(Pos curPos);

};

#endif