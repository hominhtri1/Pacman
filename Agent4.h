#ifndef _AGENT4_H_
#define _AGENT4_H_

#include "Header.h"

class Agent4
{

private:
	vector<vector<int>> map;

	int M;
	int N;

	int Px;
	int Py;

	vector<Pos> path;

	int path_i;

	vector<Pos> monsterPos;

	vector<Pos> buildPath(vector<vector<Pos>> & prev, int end_x, int end_y);

	bool adjacentMonster(int x, int y, int relaxedLevel);

	void findPathWithBFS(int relaxedLevel);

	void findSafePath();

	void printPath(ofstream & fout);

public:
	Agent4(vector<vector<int>> map, int monsterCount);

	Pos interact(vector<Pos> inMonsterPos, ofstream & fout);

};

#endif