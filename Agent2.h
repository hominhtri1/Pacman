#ifndef _AGENT2_H_
#define _AGENT2_H_

#include "Header.h"

class Agent2
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	vector<Pos> path;

	int path_i;

	vector<Pos> buildPath(vector<vector<Pos>> & prev, int end_x, int end_y);

	void findPathWithBFS();

public:
	Agent2(vector<vector<int>> map);

	Pos interact();

};

#endif